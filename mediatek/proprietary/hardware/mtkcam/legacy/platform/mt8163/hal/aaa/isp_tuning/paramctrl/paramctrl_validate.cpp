/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

/********************************************************************************************
 *     LEGAL DISCLAIMER
 *
 *     (Header of MediaTek Software/Firmware Release or Documentation)
 *
 *     BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 *     THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED
 *     FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS
 *     ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED,
 *     INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR
 *     A PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY
 *     WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 *     INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK
 *     ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *     NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION
 *     OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *
 *     BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE LIABILITY WITH
 *     RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION,
TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE
 *     FEES OR SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 *     THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH THE LAWS
 *     OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LAWS PRINCIPLES.
 ************************************************************************************************/
#define LOG_TAG "paramctrl_validate"

#ifndef ENABLE_MY_LOG
    #define ENABLE_MY_LOG       (1)
#endif

#include <aaa_types.h>
#include <aaa_log.h>
//#include <mtkcam/v3/hal/aaa_hal_common.h>
#include <camera_custom_nvram.h>
#include <isp_tuning.h>
#include <awb_param.h>
#include <ae_param.h>
#include <af_param.h>
#include <flash_param.h>
#include <isp_tuning_cam_info.h>
#include <isp_tuning_idx.h>
#include <isp_tuning_custom.h>
#include <lsc_mgr2.h>
#include <mtkcam/featureio/tuning_mgr.h>
#include "paramctrl_if.h"
#include "paramctrl.h"

using namespace android;
using namespace NSIspTuning;
using namespace NSIspTuningv3;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MERROR_ENUM
Paramctrl::
validate(MINT32 const i4FrameID, MBOOL const fgForce)
{
    MERROR_ENUM err = MERR_UNKNOWN;

    MY_LOG_IF(m_bDebugEnable,"%s(): i4FrameID = %d\n", __FUNCTION__, i4FrameID);

    // flush turning setting
    TuningMgr::getInstance().flushSetting(m_eSoftwareScenario);

    MBOOL const fgRet = ( MERR_OK == (err = validateFrameless()) )
                    &&  ( MERR_OK == (err = validatePerFrame(i4FrameID, fgForce)) )
                        ;

    // apply default setting to for 1 ~ 6,
    // 1, 2, 3 are dummy buffers, will be P1 and AAO output
    // 4, 5, 6 are protection buffers
    for (MINT32 i = 1; i <= 6; i++)
    {
        applyToHw_PerFrame_All(i);
    }

    return  err;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MERROR_ENUM
Paramctrl::
validateFrameless()
{
    MERROR_ENUM err = MERR_UNKNOWN;

    MY_LOG("[+validateFrameless]");

    Mutex::Autolock lock(m_Lock);

#if 0 // TODO: check if necessary
    //  (1) reinit isp driver manager
    if  ( IspDrvMgr::MERR_OK != IspDrvMgr::getInstance().reinit() )
    {
        err = MERR_BAD_ISP_DRV;
        goto lbExit;
    }
#endif

    //  (2)
    if  ( ! prepareHw_Frameless_All() )
    {
        err = MERR_PREPARE_HW;
        goto lbExit;
    }

    //  (3)
    if  ( ! applyToHw_Frameless_All() )
    {
        err = MERR_APPLY_TO_HW;
        goto lbExit;
    }

    //  (4) Force validatePerFrame() to run.
    m_u4ParamChangeCount++;

    err = MERR_OK;

lbExit:
#if ENABLE_MY_ERR
    if  ( MERR_OK != err )
    {
        MY_ERR("[-validateFrameless]err(%X)", err);
    }
#endif

    return  err;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MERROR_ENUM
Paramctrl::
validatePerFrame(MINT32 const i4FrameID, MBOOL const fgForce)
{
    MERROR_ENUM err = MERR_UNKNOWN;

    MY_LOG_IF(m_bDebugEnable, "[validatePerFrame] i4FrameID = %d", i4FrameID);

    Mutex::Autolock lock(m_Lock);

    m_rIspCamInfo.u4Id = i4FrameID;
#if 0
    if(getOperMode() == EOperMode_Meta) {
        err = MERR_OK;
        MY_LOG("[validatePerFrame] Meta Mode\n");
        goto lbExit;
    }
#endif

    if (m_bDebugEnable) {
        MY_LOG("%s()\n", __FUNCTION__);
        IspDebug::getInstance().dumpIspDebugMessage();
    }

    //  (0) Make sure it's really needed to apply.
    if  ( 0 == getParamChangeCount()  //  no params change
           && !fgForce)                //  not force to apply
    {
        err = MERR_OK;
        TuningMgr::getInstance().byPassSetting(m_eSoftwareScenario, i4FrameID);
        goto lbExit;
    }

    MY_LOG_IF(m_bDebugEnable, "[validatePerFrame](ParamChangeCount, fgForce)=(%d, %d)", getParamChangeCount(), fgForce);

    //  (1) reset to 0 since all params have been applied.
    resetParamChangeCount();

    //  (2) Do something.
    err = do_validatePerFrame(i4FrameID);
    if  (MERR_OK != err)
    {
        MY_ERR("[validatePerFrame]do_validatePerFrame returns err(%d)", err);
        goto lbExit;
    }

    err = MERR_OK;

lbExit:

    return  err;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MERROR_ENUM
Paramctrl::
validatePerFrameP2(MINT32 flowType, const RAWIspCamInfo& rIspCamInfo, void* pRegBuf)
{
    MERROR_ENUM err = MERR_UNKNOWN;

    MY_LOG_IF(m_bDebugEnable, "[validatePerFrameP2] i4FrameID = %d", rIspCamInfo.u4Id);

    //Mutex::Autolock lock(m_Lock);

#if 0
    if(getOperMode() == EOperMode_Meta) {
        err = MERR_OK;
        MY_LOG("[validatePerFrame] Meta Mode\n");
        goto lbExit;
    }
#endif

    //  (2) Do something.
    err = do_validatePerFrameP2(flowType, rIspCamInfo, pRegBuf);
    if  (MERR_OK != err)
    {
        MY_ERR("[validatePerFrameP2]do_validatePerFrame returns err(%d)", err);
        goto lbExit;
    }

    err = MERR_OK;

lbExit:

    return  err;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MERROR_ENUM
Paramctrl::
do_validatePerFrame(MINT32 const i4FrameID)
{
    MERROR_ENUM err = MERR_OK;
    MBOOL prepare_rdy;

    MY_LOG_IF(m_bDebugEnable, "[do_validatePerFrame]");

    CPTLog(Event_Pipe_3A_ISP_VALIDATE_PERFRAME_DYNAMIC_TUNING, CPTFlagStart); // Profiling Start.

    //  (1) dynamic tuning
    if (isDynamicTuning())
    {

        IndexMgr idxmgr;

        // CAM3 TODO: profile mapping
        if (m_i4IspProfile == EIspProfile_NormalPreview) {
            switch (m_rIspCamInfo.eSensorMode) {
            case ESensorMode_Preview:
                m_rIspCamInfo.eIspProfile = EIspProfile_NormalPreview;
                break;
            case ESensorMode_Video:
                m_rIspCamInfo.eIspProfile = EIspProfile_VideoPreview;
                break;
            case ESensorMode_Capture:
                m_rIspCamInfo.eIspProfile = EIspProfile_ZsdPreview_CC;
                break;
            default:
                m_rIspCamInfo.eIspProfile = EIspProfile_NormalPreview;
            }
        }
        else if (m_i4IspProfile == EIspProfile_NormalCapture) {
            switch (m_rIspCamInfo.eSensorMode) {
            case ESensorMode_Preview:
            case ESensorMode_Video:
                m_rIspCamInfo.eIspProfile = EIspProfile_VideoCapture;
                break;
            case ESensorMode_Capture:
                m_rIspCamInfo.eIspProfile = EIspProfile_NormalCapture;
                break;
            default:
                m_rIspCamInfo.eIspProfile = EIspProfile_NormalCapture;
            }
        }
        else {
            MY_ERR("[do_validatePerFrame]incorrect ISP profile = %d", m_i4IspProfile);
        }



        //  a) Get default index setting.
        INDEX_T const*const pDefaultIndex = m_pIspTuningCustom->getDefaultIndex(
            m_rIspCamInfo.eIspProfile, m_rIspCamInfo.eSensorMode, m_rIspCamInfo.eIdx_Scene, m_rIspCamInfo.eIdx_ISO
        );
        if  ( ! pDefaultIndex )
        {
            MY_ERR("[ERROR][validatePerFrame]pDefaultIndex==NULL");
            err = MERR_CUSTOM_DEFAULT_INDEX_NOT_FOUND;
            goto lbExit;
        }
        idxmgr = *pDefaultIndex;

        MY_LOG_IF(m_bDebugEnable, "[BEFORE][evaluate_nvram_index]");

        if (m_bDebugEnable) {
            idxmgr.dump();
        }

        //  b) Customize the index setting.
        m_pIspTuningCustom->evaluate_nvram_index(m_rIspCamInfo, idxmgr);

        MY_LOG_IF(m_bDebugEnable, "[AFTER][evaluate_nvram_index]");

        if (m_bDebugEnable) {
            idxmgr.dump();
        }

        //  c) Restore customized index set to member.
        //m_IspNvramMgr = idxmgr; //Yosen mark out
        if (!isDynamicBypass()) m_IspNvramMgr = idxmgr; //Yosen
        MY_LOG_IF(m_bDebugEnable, "m_IspNvramMgr::getIdx = [OBC(%d),BPC(%d),NR1(%d),CFA(%d),GGM(%d),ANR(%d),CCR(%d),EE(%d)]\n"
                ,m_IspNvramMgr.getIdx_OBC()
                ,m_IspNvramMgr.getIdx_BPC()
                ,m_IspNvramMgr.getIdx_NR1()
                ,m_IspNvramMgr.getIdx_CFA()
                ,m_IspNvramMgr.getIdx_GGM()
                ,m_IspNvramMgr.getIdx_ANR()
                ,m_IspNvramMgr.getIdx_CCR()
                ,m_IspNvramMgr.getIdx_EE());

    }

    CPTLog(Event_Pipe_3A_ISP_VALIDATE_PERFRAME_DYNAMIC_TUNING, CPTFlagEnd); // Profiling End.


    //  (2) Apply Per-Frame Parameters.
    MY_LOG_IF(m_bDebugEnable, "[do_validatePerFrame()] isDynamicBypass() = %d\n", isDynamicBypass());
    (isDynamicBypass() == MTRUE) ? (prepare_rdy = prepareHw_PerFrame_Partial())
                                 : (prepare_rdy = prepareHw_PerFrame_All());

    if(!prepare_rdy || ! applyToHw_PerFrame_All(i4FrameID))  //  Apply the ispmgr's buffer to H/W.
    {
        err = MERR_SET_ISP_REG;
        goto lbExit;
    }

#if 0
    if  (
            ! prepareHw_PerFrame_All()          //  Prepare param members to the ispmgr's buffer.
        ||  ! applyToHw_PerFrame_All()          //  Apply the ispmgr's buffer to H/W.
        )
    {
        err = MERR_SET_ISP_REG;
        goto lbExit;
    }
#endif

    //  (3) Save Exif debug info if necessary.
    err = saveDebugInfo();
    if  ( MERR_OK != err )
    {
        goto lbExit;
    }

lbExit:
    if  ( MERR_OK != err )
    {
        MY_ERR("[-do_validatePerFrame]err(%X)", err);
    }

    return  err;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MERROR_ENUM
Paramctrl::
do_validatePerFrameP2(MINT32 flowType, const RAWIspCamInfo& rIspCamInfo, void* pRegBuf)
{
    MERROR_ENUM err = MERR_OK;
    MBOOL prepare_rdy = MTRUE;

    MY_LOG_IF(m_bDebugEnable, "[do_validatePerFrameP2]");

    CPTLog(Event_Pipe_3A_ISP_VALIDATE_PERFRAME_DYNAMIC_TUNING, CPTFlagStart); // Profiling Start.

    //  (1) dynamic tuning
    if (isDynamicTuning())
    {
        IndexMgr idxmgr;

        //  a) Get default index setting.
        INDEX_T const*const pDefaultIndex = m_pIspTuningCustom->getDefaultIndex(
            rIspCamInfo.eIspProfile, rIspCamInfo.eSensorMode, rIspCamInfo.eIdx_Scene, rIspCamInfo.eIdx_ISO
        );
        if  ( ! pDefaultIndex )
        {
            MY_ERR("[ERROR][validatePerFrame]pDefaultIndex==NULL");
            err = MERR_CUSTOM_DEFAULT_INDEX_NOT_FOUND;
            goto lbExit;
        }
        idxmgr = *pDefaultIndex;

        MY_LOG_IF(m_bDebugEnable, "[BEFORE][evaluate_nvram_index]");

        if (m_bDebugEnable) {
            idxmgr.dump();
        }

        //  b) Customize the index setting.
        m_pIspTuningCustom->evaluate_nvram_index(rIspCamInfo, idxmgr);

        MY_LOG_IF(m_bDebugEnable, "[AFTER][evaluate_nvram_index]");

        if (m_bDebugEnable) {
            idxmgr.dump();
        }

        MY_LOG_IF(m_bDebugEnable, "IndexMgr::getIdx = [OBC(%d),BPC(%d),NR1(%d),CFA(%d),GGM(%d),ANR(%d),CCR(%d),EE(%d)]\n"
                ,idxmgr.getIdx_OBC()
                ,idxmgr.getIdx_BPC()
                ,idxmgr.getIdx_NR1()
                ,idxmgr.getIdx_CFA()
                ,idxmgr.getIdx_GGM()
                ,idxmgr.getIdx_ANR()
                ,idxmgr.getIdx_CCR()
                ,idxmgr.getIdx_EE());

        //  (2) Apply Per-Frame Parameters.
        MY_LOG_IF(m_bDebugEnable, "[do_validatePerFrame()] isDynamicBypass() = %d\n", isDynamicBypass());
        (isDynamicBypass() == MTRUE) ? (prepare_rdy = prepareHw_PerFrame_Partial(rIspCamInfo, idxmgr))
                                     : (prepare_rdy = prepareHw_PerFrame_All(rIspCamInfo, idxmgr));
    }

    CPTLog(Event_Pipe_3A_ISP_VALIDATE_PERFRAME_DYNAMIC_TUNING, CPTFlagEnd); // Profiling End.

    if(!prepare_rdy || ! applyToHw_PerFrame_P2(flowType, rIspCamInfo, pRegBuf))  //  Apply the ispmgr's buffer to H/W.
    {
        err = MERR_SET_ISP_REG;
        goto lbExit;
    }

#if 0
    if  (
            ! prepareHw_PerFrame_All()          //  Prepare param members to the ispmgr's buffer.
        ||  ! applyToHw_PerFrame_All()          //  Apply the ispmgr's buffer to H/W.
        )
    {
        err = MERR_SET_ISP_REG;
        goto lbExit;
    }
#endif

    //  (3) Save Exif debug info if necessary.
    err = saveDebugInfo();
    if  ( MERR_OK != err )
    {
        goto lbExit;
    }

lbExit:
    if  ( MERR_OK != err )
    {
        MY_ERR("[-do_validatePerFrame]err(%X)", err);
    }

    return  err;
}

#if 0

MERROR_ENUM
ParamctrlComm::
setEnable_Meta_Gamma(MBOOL const fgForceEnable)
{
    MY_LOG(
        "[+setEnable_Meta_Gamma] (fgForceEnable, m_fgForceEnable_Meta_Gamma)=(%d, %d)"
        , fgForceEnable, m_fgForceEnable_Meta_Gamma
    );

    Mutex::Autolock lock(m_Lock);

    checkParamChange(m_fgForceEnable_Meta_Gamma, fgForceEnable);

    m_fgForceEnable_Meta_Gamma = fgForceEnable;

    return  MERR_OK;
}

#endif

