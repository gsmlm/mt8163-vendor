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
#define LOG_TAG "aaa_state_precapture"

#ifndef ENABLE_MY_LOG
    #define ENABLE_MY_LOG       (1)
#endif

#include <aaa_types.h>
#include <aaa_error_code.h>
#include <aaa_log.h>
#include <dbg_aaa_param.h>
#include <aaa_hal.h>
#include "aaa_state.h"
#include <camera_custom_nvram.h>
#include <awb_param.h>
#include <flash_awb_param.h>
#include <flash_awb_tuning_custom.h>
#include <isp_tuning.h>
#include <awb_mgr_if.h>
#include <kd_camera_feature.h>
#include <buf_mgr.h>
#include <mtkcam/common.h>
using namespace NSCam;
#include <camera_custom_AEPlinetable.h>
#include <ae_param.h>
#include <ae_mgr.h>
#include <flash_mgr.h>
//#include <mtkcam/hal/sensor_hal.h>
#include <af_param.h>
#include <mcu_drv.h>
#include <af_mgr_if.h>
#include <flash_param.h>
#include <mtkcam/hwutils/CameraProfile.h>  // For CPTLog*()/AutoCPTLog class.
#include <cutils/properties.h>
#include <isp_tuning.h>
#include <dbg_isp_param.h>
#include <isp_tuning_mgr.h>
#include <lsc_mgr2.h>
#include <flash_tuning_custom.h>
#include <mtkcam/featureio/flicker_hal_base.h>

using namespace NS3A;
using namespace NSIspTuning;

static int g_bCheckAF=1;

extern EState_T g_nextState;
int g_isPostPrecapAF=0;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  StatePrecapture
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
StatePrecapture::
StatePrecapture()
    : IState("StatePrecapture")
{
    g_bCheckAF=1;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  eIntent_PrecaptureStart
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MRESULT
StatePrecapture::
sendIntent(intent2type<eIntent_PrecaptureStart>)
{
    MY_LOG("sendIntent(intent2type<eIntent_PrecaptureStart>) line=%d",__LINE__);
    return  S_3A_OK;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  eIntent_PrecaptureEnd
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MRESULT
StatePrecapture::
sendIntent(intent2type<eIntent_PrecaptureEnd>)
{
    MY_LOG("sendIntent(intent2type<eIntent_PrecaptureEnd>) line=%d",__LINE__);

    m_pHal3A->resetReadyToCapture();
    //FlashMgr::getInstance().turnOffPrecapFlash();
    FlashMgr::getInstance().endPrecapture(m_pHal3A->getSensorDev());
    g_bCheckAF=1;
    g_isPostPrecapAF=0;


    return  S_3A_OK;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  eIntent_VsyncUpdate
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MRESULT
StatePrecapture::
sendIntent(intent2type<eIntent_VsyncUpdate>)
{
    MY_LOG("sendIntent(intent2type<eIntent_VsyncUpdate>) line=%d frameCnt=%d",__LINE__,getFrameCount());

#define PRE_PREAF_STATE -1
#define PRE_AE_STATE 0
#define PRE_FLASH_STATE 1
#define PRE_POSTAF_STATE 2
#define PRE_READY_STATE 3

    if(m_pHal3A->isReadyToCapture())
    {
        MY_LOG("VsyncUpdate ReadyToCapture=1, skip");
        return S_3A_OK;
    }

    static int preSyncState = PRE_PREAF_STATE;
    MRESULT err = S_3A_OK;
    BufInfo_T rBufInfo;
    MBOOL bIsStrobeFired = MFALSE;
    MINT32 iSensorDev = m_pHal3A->getSensorDev();

    if(preSyncState==PRE_PREAF_STATE)
    {
        MY_LOG("PRE_PREAF_STATE");
        int paf_mode;
        paf_mode = cust_getPrecapAfMode();
        if(paf_mode==e_PrecapAf_BeforePreflash)
        {
            MY_LOG("e_PrecapAf_BeforePreflash");
            int isDoAF;
            isDoAF = cust_isNeedDoPrecapAF_v2(
                    1,
                    IAfMgr::getInstance().isFocused(m_pHal3A->getSensorDev()),
                    FlashMgr::getInstance().getFlashMode(m_pHal3A->getSensorDev()),
                    FlashMgr::getInstance().getAfLampMode(m_pHal3A->getSensorDev()),
                    IAeMgr::getInstance().IsStrobeBVTrigger(m_pHal3A->getSensorDev()));
            if(isDoAF==1)
        {
                ALOGD("isDoAF=1 line=%d",__LINE__);
            IAfMgr::getInstance().setAFMode(m_pHal3A->getSensorDev(),AF_MODE_AFS);
            if(IAeMgr::getInstance().IsDoAEInPreAF(m_pHal3A->getSensorDev()) == MTRUE)
            {
                transitAFState(eAFState_PreAF);
            }
            else
            {
                IAfMgr::getInstance().triggerAF(m_pHal3A->getSensorDev());
                transitAFState(eAFState_AF);
            }
            g_nextState = eState_Precapture;
            transitState(eState_Precapture, eState_AF);
                FlashMgr::getInstance().notifyAfEnter(m_pHal3A->getSensorDev());
                g_nextState = eState_Precapture;
            IAfMgr::getInstance().autoFocus(m_pHal3A->getSensorDev());
                preSyncState=PRE_AE_STATE;
            return S_3A_OK;
        }
            else
            {
                ALOGD("isDoAF=0");
            }
    }
        else
    {
            MY_LOG("not e_PrecapAf_BeforePreflash");
        }
        preSyncState=PRE_AE_STATE;
    }


    // Dequeue AAO DMA buffer
    BufMgr::getInstance().dequeueHwBuf(ECamDMA_AAO, rBufInfo);

    if(preSyncState==PRE_AE_STATE)
    {
        MY_LOG("preSyncState==PRE_AE_STATE  line=%d",__LINE__);
        // One-shot AE or strobe AE
        //-------------------------------------------------------
        CPTLog(Event_Pipe_3A_AE, CPTFlagStart);    // Profiling Start.
        IAeMgr::getInstance().doPreCapAE(m_pHal3A->getSensorDev(), getFrameCount(), bIsStrobeFired, reinterpret_cast<MVOID *>(rBufInfo.virtAddr),
            0, 1, 0);
        if (IAeMgr::getInstance().IsNeedUpdateSensor(m_pHal3A->getSensorDev()))
        {
            MY_LOG_IF(1, "updateSensorbyI2C start\n");
            IAeMgr::getInstance().updateSensorbyI2C(m_pHal3A->getSensorDev());
            MY_LOG_IF(1, "updateSensorbyI2C end\n");
        }
        CPTLog(Event_Pipe_3A_AE, CPTFlagEnd);     // Profiling End.

        if(IAeMgr::getInstance().IsAEStable(m_pHal3A->getSensorDev()) == MTRUE) {    // AE is stable
            // One-shot AWB without strobe
            MINT32 i4SceneLV = IAeMgr::getInstance().getLVvalue(m_pHal3A->getSensorDev(), MFALSE);

            IAwbMgr::getInstance().setStrobeMode(iSensorDev, AWB_STROBE_MODE_OFF);
            IAwbMgr::getInstance().doPreCapAWB(iSensorDev, i4SceneLV, reinterpret_cast<MVOID *>(rBufInfo.virtAddr));
        }
        if(IAeMgr::getInstance().IsAEStable(m_pHal3A->getSensorDev()) == MTRUE) {    // AE is stable
        // FIXME: call notifyReadyToCapture() if both one-shot AE and one-shot AWB are done
        MY_LOG("AE ready  line=%d",__LINE__);
        //m_pHal3A->notifyReadyToCapture();
        preSyncState = PRE_FLASH_STATE;
        }


    }

    //Note: not "else if ..." because after AE end frame, flash should start to make faster.
    if(preSyncState==PRE_FLASH_STATE)
    {
        MY_LOG("preSyncState==PRE_FLASH_STATE  line=%d",__LINE__);
        //-------------------------------------
        // flash
        CPTLog(Event_Pipe_3A_Strobe, CPTFlagStart);     // Profiling start.
        FlashExePara para;
        FlashExeRep rep;
        FLASH_AWB_PASS_FLASH_INFO_T passFlashAwbData;

        //-------
        // para assign
        para.staBuf =reinterpret_cast<MVOID *>(rBufInfo.virtAddr);
        int flickerMode;
        FlickerHalBase::getInstance().getFlickerResult(flickerMode);
        if(flickerMode==HAL_FLICKER_AUTO_50HZ)
            para.flickerMode = FlashMgr::e_Flicker50;
        else if(flickerMode==HAL_FLICKER_AUTO_60HZ)
            para.flickerMode = FlashMgr::e_Flicker60;
        else
            para.flickerMode = FlashMgr::e_FlickerUnknown;
        para.staX = 120;
        para.staY = 90;
        FlashMgr::getInstance().doPfOneFrame(m_pHal3A->getSensorDev(), &para, &rep);
        if(rep.isEnd==1)
        {
            MY_LOG("change to postAF state");
            preSyncState = PRE_POSTAF_STATE;

            if (isFlashAWBv2Enabled()) {
                passFlashAwbData.flashDuty = rep.nextDuty;
                passFlashAwbData.flashStep = rep.nextStep;
                passFlashAwbData.flashAwbWeight = rep.flashAwbWeight;
                IAwbMgr::getInstance().setFlashAWBData(iSensorDev, passFlashAwbData);
            }
            //end

        }
        CPTLog(Event_Pipe_3A_Strobe, CPTFlagEnd);     // Profiling End.

        //FIXME @@ YawbANU}(precaptureUAWB)

        MINT32 i4SceneLV = IAeMgr::getInstance().getLVvalue(m_pHal3A->getSensorDev(), MFALSE);
        if(rep.isCurFlashOn==0)
            IAwbMgr::getInstance().setStrobeMode(iSensorDev, AWB_STROBE_MODE_OFF);
        else
            IAwbMgr::getInstance().setStrobeMode(iSensorDev, AWB_STROBE_MODE_ON);

        IAwbMgr::getInstance().doPreCapAWB(iSensorDev, i4SceneLV, reinterpret_cast<MVOID *>(rBufInfo.virtAddr));

        // disable TSF
        //if(FlashMgr::getInstance().isFlashOnCapture(m_pHal3A->getSensorDev()))
        //    LscMgr::getInstance()->notifyPreflash(MTRUE);

    }

    //MTK_SWIP_PROJECT_START
    // F858
    AWB_OUTPUT_T rAWBOutput;
    IAwbMgr::getInstance().getAWBOutput(iSensorDev, rAWBOutput);
    LscMgr2::TSF_AWB_INFO rAwbInfo;
    rAwbInfo.m_i4LV     = IAeMgr::getInstance().getLVvalue(iSensorDev,MTRUE);
    rAwbInfo.m_u4CCT    = IAwbMgr::getInstance().getAWBCCT(iSensorDev);
    rAwbInfo.m_RGAIN    = rAWBOutput.rAWBInfo.rCurrentAWBGain.i4R;
    rAwbInfo.m_GGAIN    = rAWBOutput.rAWBInfo.rCurrentAWBGain.i4G;
    rAwbInfo.m_BGAIN    = rAWBOutput.rAWBInfo.rCurrentAWBGain.i4B;
    rAwbInfo.m_FLUO_IDX = rAWBOutput.rAWBInfo.i4FluorescentIndex;
    rAwbInfo.m_DAY_FLUO_IDX = rAWBOutput.rAWBInfo.i4DaylightFluorescentIndex;
    LscMgr2::getInstance(static_cast<ESensorDev_T>(iSensorDev))->updateTsf(
        LscMgr2::E_TSF_CMD_RUN, &rAwbInfo, reinterpret_cast<MVOID *>(rBufInfo.virtAddr));


    MY_LOG("lv %d, cct %d, rgain %d, bgain %d, ggain %d, fluo idx %d, day flou idx %d\n",
            rAwbInfo.m_i4LV,
            rAwbInfo.m_u4CCT,
            rAwbInfo.m_RGAIN,
            rAwbInfo.m_GGAIN,
            rAwbInfo.m_BGAIN,
            rAwbInfo.m_FLUO_IDX,
            rAwbInfo.m_DAY_FLUO_IDX
            );
    //MTK_SWIP_PROJECT_END

    //-------------------------------------------------------
    // Enqueue AAO DMA buffer
    BufMgr::getInstance().enqueueHwBuf(ECamDMA_AAO, rBufInfo);
    // Update AAO DMA address
    BufMgr::getInstance().updateDMABaseAddr(camdma2type<ECamDMA_AAO>(), BufMgr::getInstance().getNextHwBuf(ECamDMA_AAO));




    if(preSyncState==PRE_POSTAF_STATE)
    {
        MY_LOG("PRE_POSTAF_STATE");
        int paf_mode;
        paf_mode = cust_getPrecapAfMode();
        if(paf_mode==e_PrecapAf_AfterPreflash)
        {
            MY_LOG("e_PrecapAf_AfterPreflash");
            int isDoAF2;
            isDoAF2 = cust_isNeedDoPrecapAF_v2(
                                    0,
                        IAfMgr::getInstance().isFocused(m_pHal3A->getSensorDev()),
                        FlashMgr::getInstance().getFlashMode(m_pHal3A->getSensorDev()),
                        FlashMgr::getInstance().getAfLampMode(m_pHal3A->getSensorDev()),
                        IAeMgr::getInstance().IsStrobeBVTrigger(m_pHal3A->getSensorDev()));



            if(isDoAF2==1)
            {
                MY_LOG("isDoPostAF=1");
                if(FlashMgr::getInstance().isFlashOnCapture(m_pHal3A->getSensorDev()))
                FlashMgr::getInstance().setPfParaToAe(m_pHal3A->getSensorDev());
                g_isPostPrecapAF=1;
                IAfMgr::getInstance().setAFMode(m_pHal3A->getSensorDev(),AF_MODE_AFS);
                if(IAeMgr::getInstance().IsDoAEInPreAF(m_pHal3A->getSensorDev()) == MTRUE)
                {
                    transitAFState(eAFState_PreAF);
                }
                else
                {
                    IAfMgr::getInstance().triggerAF(m_pHal3A->getSensorDev());
                    transitAFState(eAFState_AF);
                }
                g_nextState = eState_Precapture;
                transitState(eState_Precapture, eState_AF);
                FlashMgr::getInstance().notifyAfEnter(m_pHal3A->getSensorDev());
                g_nextState = eState_Precapture;
                IAfMgr::getInstance().autoFocus(m_pHal3A->getSensorDev());
                preSyncState=PRE_READY_STATE;
                return S_3A_OK;
            }
            else
            {
                MY_LOG("isDoPostAF=0");
            }
        }
        else
        {
            MY_LOG("not e_PrecapAf_AfterPreflash");
        }
        preSyncState=PRE_READY_STATE;
    }
    if(preSyncState==PRE_READY_STATE)
    {
        MY_LOG("PRE_READY_STATE");
        if(FlashMgr::getInstance().isFlashOnCapture(m_pHal3A->getSensorDev()))
            FlashMgr::getInstance().setCapPara(m_pHal3A->getSensorDev());
        m_pHal3A->notifyReadyToCapture();
        preSyncState = PRE_PREAF_STATE;
    }
    return  err;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  eIntent_AFUpdate
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MRESULT
StatePrecapture::
sendIntent(intent2type<eIntent_AFUpdate>)
{
    MY_LOG("sendIntent(intent2type<eIntent_AFUpdate>) line=%d",__LINE__);

    return  S_3A_OK;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  eIntent_CaptureStart
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MRESULT
StatePrecapture::
sendIntent(intent2type<eIntent_CaptureStart>)
{
    MY_LOG("sendIntent(intent2type<eIntent_CaptureStart>) line =%d",__LINE__);
    MINT32 i4AEEnable, i4AWBEnable;
    MUINT32 u4Length;


    //move to Hal3A::onFireCapFlashIfNeeded()
    //CPTLogStr(Event_SShot_createSensorRawImg, CPTFlagSeparator, "FlhChkFire_S");
    //FlashMgr::getInstance().capCheckAndFireFlash_Start();
    // Init

    // AWB: update AWB statistics config
    if (FlashMgr::getInstance().isFlashOnCapture(m_pHal3A->getSensorDev())) {
        IAwbMgr::getInstance().setStrobeMode(m_pHal3A->getSensorDev(), AWB_STROBE_MODE_ON);
      //  AeMgr::getInstance().setStrobeMode(MTRUE);
    }
    else {
        IAwbMgr::getInstance().setStrobeMode(m_pHal3A->getSensorDev(), AWB_STROBE_MODE_OFF);
        IAeMgr::getInstance().setStrobeMode(m_pHal3A->getSensorDev(), MFALSE);
    }

    //CPTLogStr(Event_SShot_createSensorRawImg, CPTFlagSeparator, "AEDoCapAE");
    // AE: update capture parameter
    IAeMgr::getInstance().doCapAE(m_pHal3A->getSensorDev());

    //CPTLogStr(Event_SShot_createSensorRawImg, CPTFlagSeparator, "AWBCapInit");
    IAwbMgr::getInstance().cameraCaptureInit(m_pHal3A->getSensorDev());

    // if the ae/awb don't enable, don't need to enable the AAO
    IAeMgr::getInstance().CCTOPAEGetEnableInfo(m_pHal3A->getSensorDev(), &i4AEEnable, &u4Length);
    IAwbMgr::getInstance().CCTOPAWBGetEnableInfo(m_pHal3A->getSensorDev(), &i4AWBEnable, &u4Length);
    if((i4AWBEnable != MFALSE) && (i4AEEnable != MFALSE)) {
    // Get operation mode and sensor mode for CCT and EM
    /*if ((IspTuningMgr::getInstance().getOperMode() == EOperMode_Normal) ||
        (IspTuningMgr::getInstance().getSensorMode() == ESensorMode_Capture))*/ {

        //CPTLogStr(Event_SShot_createSensorRawImg, CPTFlagSeparator, "BufMgrAAInit");
        // AAO DMA / state enable again
        MRESULT err = BufMgr::getInstance().DMAInit(camdma2type<ECamDMA_AAO>());
        if (FAILED(err)) {
            MY_ERR("BufMgr::getInstance().DMAInit(ECamDMA_AAO) fail\n");
            return err;
        }

        err = BufMgr::getInstance().AAStatEnable(MTRUE);
        if (FAILED(err)) {
            MY_ERR("BufMgr::getInstance().AAStatEnable(MTRUE) fail\n");
            return err;
        }

        //CPTLogStr(Event_SShot_createSensorRawImg, CPTFlagSeparator, "AFBestShotConf");
        IAfMgr::getInstance().setBestShotConfig(m_pHal3A->getSensorDev());

        //CPTLogStr(Event_SShot_createSensorRawImg, CPTFlagSeparator, "BufMgrAFInit");
        // AFO DMA / state enable again
        err = BufMgr::getInstance().DMAInit(camdma2type<ECamDMA_AFO>());
        if (FAILED(err)) {
            MY_ERR("BufMgr::getInstance().DMAInit(ECamDMA_AFO) fail\n");
            return err;
        }

        err = BufMgr::getInstance().AFStatEnable(MTRUE);
        if (FAILED(err)) {
            MY_ERR("BufMgr::getInstance().AFStatEnable(MTRUE) fail\n");
            return err;
        }
    }
    }
    IspTuningMgr::getInstance().validate(m_pHal3A->getSensorDev(), MTRUE);

    // State transition: eState_Precapture --> eState_Capture
    transitState(eState_Precapture, eState_Capture);

    return  S_3A_OK;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  eIntent_CameraPreviewEnd
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MRESULT
StatePrecapture::
sendIntent(intent2type<eIntent_CameraPreviewEnd>)
{
    MY_LOG("sendIntent(intent2type<eIntent_CameraPreviewEnd>) line=%d",__LINE__);

    FlickerHalBase::getInstance().close(m_pHal3A->getSensorDev());
    return  S_3A_OK;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  eIntent_CamcorderPreviewEnd
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MRESULT
StatePrecapture::
sendIntent(intent2type<eIntent_CamcorderPreviewEnd>)
{
    MY_LOG("sendIntent(intent2type<eIntent_CamcorderPreviewEnd>) line=%d",__LINE__);

    FlickerHalBase::getInstance().close(m_pHal3A->getSensorDev());
    return  S_3A_OK;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  eIntent_AFEnd
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MRESULT
StatePrecapture::
sendIntent(intent2type<eIntent_AFEnd>)
{
    MY_LOG("sendIntent(intent2type<eIntent_AFEnd>) line=%d",__LINE__);

    return  S_3A_OK;
}



