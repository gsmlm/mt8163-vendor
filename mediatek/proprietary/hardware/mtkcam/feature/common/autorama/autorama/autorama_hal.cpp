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
#define LOG_TAG "autorama_hal"

#include <Log.h>
#include "AppAutorama.h"
#include "autorama_hal.h"
#include <autorama_hal_base.h>
#include <IHalSensor.h>
#include <math.h>

/*******************************************************************************
*
********************************************************************************/
#define MHAL_LOGD(fmt, arg...)    CAM_LOGD(fmt,##arg)
#define MHAL_LOGI(fmt, arg...)    CAM_LOGI(fmt,##arg)
#define MHAL_LOGE(fmt, arg...)    CAM_LOGE(fmt,##arg)

static halAUTORAMABase *pHalAUTORAMA = NULL;
/*******************************************************************************
*
********************************************************************************/
halAUTORAMABase*
halAUTORAMA::
getInstance()
{
    MHAL_LOGD("[halAUTORAMA] getInstance \n");
    if (pHalAUTORAMA == NULL) {
        pHalAUTORAMA = new halAUTORAMA();
    }
    return pHalAUTORAMA;
}

/*******************************************************************************
*
********************************************************************************/
void
halAUTORAMA::
destroyInstance()
{
    if (pHalAUTORAMA) {
        delete pHalAUTORAMA;
    }
    pHalAUTORAMA = NULL;
}

/*******************************************************************************
*
********************************************************************************/
halAUTORAMA::halAUTORAMA()
{
    m_pMTKAutoramaObj = NULL;
    m_pMTKMotionObj = NULL;
    mpHal3A = NULL;
    mAEValue = 0;

    /*  Create MTKPano Interface  */
    if (m_pMTKAutoramaObj)
    {
        MHAL_LOGI("[mHalAutoramaInit] m_pMTKAutoramaObj Init has been called \n");
    }
    else
    {
        m_pMTKAutoramaObj = MTKAutorama::createInstance(DRV_AUTORAMA_OBJ_SW);
    }

    if (!m_pMTKAutoramaObj)
    {
        MHAL_LOGE("[mHalAutoramaInit] m_pMTKAutoramaObj Init failed\n");
    }

    if (m_pMTKMotionObj)
    {
        MHAL_LOGI("[mHalAutoramaInit] m_pMTKMotionObj Init has been called \n");
    }
    else
    {
        m_pMTKMotionObj = MTKMotion::createInstance(DRV_MOTION_OBJ_PANO);
    }

    if (!m_pMTKMotionObj)
    {
        MHAL_LOGE("[mHalAutoramaInit] m_pMTKMotionObj Init failed \n");
    }
}

/*******************************************************************************
*
********************************************************************************/
halAUTORAMA::~halAUTORAMA()
{
}

/*******************************************************************************
*
********************************************************************************/
MINT32
halAUTORAMA::mHalAutoramaInit(MTKPipeAutoramaEnvInfo AutoramaInitInData, MTKPipeMotionEnvInfo MotionInitInfo
)
{
    MTKAutoramaEnvInfo AutoramaEnvInfo;
    MTKMotionEnvInfo MyMotionEnvInfo;
    MTKMotionTuningPara MyMotionTuningPara;
    MRESULT Retcode = S_AUTORAMA_OK;
    MHAL_LOGD("[mHalAutoramaInit] \n");

    if(sizeof(MotionInitInfo)!=sizeof(MyMotionEnvInfo))
    {
        MHAL_LOGE("[mHalAutoramaInit] MotionInitInfo not match\n");
    }

    if(sizeof(AutoramaInitInData)!=sizeof(AutoramaEnvInfo))
    {
        MHAL_LOGE("[AutoramaInitInData] AutoramaEnvInfo not match\n");
    }

    if (!m_pMTKAutoramaObj) {
        Retcode = E_AUTORAMA_ERR;
        MHAL_LOGE("[mHalAutoramaInit] Err, Init has been called \n");
        return Retcode;
    }

    if (!m_pMTKMotionObj) {
        Retcode = E_AUTORAMA_ERR;
        MHAL_LOGE("[mHalAutoramaInit] Err, Init has been called \n");
        return Retcode;
    }
    int sensorDevIdx = 0;
    int iFOV_horizontal = 50;
    int iFOV_vertical = 50;
    MUINT sensorIdx = 0;
    IHalSensorList* sensorlsit;
    sensorlsit=IHalSensorList::get();
    if(sensorlsit) {
        sensorDevIdx=sensorlsit->querySensorDevIdx(sensorIdx);
        SensorStaticInfo pSensorStaticInfo;

        sensorlsit->querySensorStaticInfo(sensorDevIdx,&pSensorStaticInfo);
        iFOV_horizontal=pSensorStaticInfo.horizontalViewAngle;
        iFOV_vertical=pSensorStaticInfo.verticalViewAngle;
    }
    else
    {
        Retcode = E_AUTORAMA_ERR;
        MHAL_LOGE("[mHalAutoramaInit] Err, sensorlsit NULL \n");
        return Retcode;
    }

    mpHal3A = IHal3A::createInstance(IHal3A::E_Camera_3, sensorIdx, "MTKPanorama");

    if (!mpHal3A)
    {
        MHAL_LOGE("[mHalAutoramaInit] mpHal3A Init failed\n");
    }
    else
    {
        mpHal3A->attachCb(IHal3ACb::eID_NOTIFY_AE_RT_PARAMS, this);
    }

    MUINT32 focalLengthInPixel = AutoramaInitInData.SrcImgWidth
                                / (2.0 * tan(iFOV_horizontal/2.0/180.0*M_PI));

    MHAL_LOGI("[mHalAutoramaInit] sensorIdx %d sensorDevIdx %d", sensorIdx, sensorDevIdx);
    MHAL_LOGI("[mHalAutoramaInit] viewnalge (h,v)=(%d,%d) focalLengthInPixel=%d", iFOV_horizontal, iFOV_vertical,focalLengthInPixel);

    /*  Pano Driver Init  */
    /*  Set Pano Driver Environment Parameters */
    AutoramaEnvInfo.SrcImgWidth = AutoramaInitInData.SrcImgWidth;
    AutoramaEnvInfo.SrcImgHeight = AutoramaInitInData.SrcImgHeight;
    AutoramaEnvInfo.MaxPanoImgWidth = AutoramaInitInData.MaxPanoImgWidth;
    AutoramaEnvInfo.WorkingBufAddr = reinterpret_cast<MUINT8*>(AutoramaInitInData.WorkingBufAddr);
    AutoramaEnvInfo.WorkingBufSize = AutoramaInitInData.WorkingBufSize;
    AutoramaEnvInfo.MaxSnapshotNumber = AutoramaInitInData.MaxSnapshotNumber;
    AutoramaEnvInfo.FixAE = AutoramaInitInData.FixAE;
    AutoramaEnvInfo.FocalLength = focalLengthInPixel;
    AutoramaEnvInfo.GPUWarp = AutoramaInitInData.GPUWarp;
    AutoramaEnvInfo.SrcImgFormat = MTKAUTORAMA_IMAGE_NV21;
    Retcode = m_pMTKAutoramaObj->AutoramaInit(&AutoramaEnvInfo, 0);

    MyMotionEnvInfo.WorkingBuffAddr = reinterpret_cast<MUINT8*>(MotionInitInfo.WorkingBuffAddr);
    MyMotionEnvInfo.pTuningPara = &MyMotionTuningPara;
    MyMotionEnvInfo.SrcImgWidth = MotionInitInfo.SrcImgWidth;
    MyMotionEnvInfo.SrcImgHeight = MotionInitInfo.SrcImgHeight;
    MyMotionEnvInfo.WorkingBuffSize = MotionInitInfo.WorkingBuffSize;
    MyMotionEnvInfo.pTuningPara->OverlapRatio = MotionInitInfo.pTuningPara->OverlapRatio;
    m_pMTKMotionObj->MotionInit(&MyMotionEnvInfo, NULL);

    return Retcode;
}

/*******************************************************************************
*
********************************************************************************/
MINT32
halAUTORAMA::mHalAutoramaUninit(
)
{
    MHAL_LOGD("[mHalAutoramaUninit] \n");

    if (mpHal3A)
    {
        mpHal3A->send3ACtrl(E3ACtrl_SetAELimiterMode, false, 0);
        mpHal3A->detachCb(IHal3ACb::eID_NOTIFY_AE_RT_PARAMS, this);
        mpHal3A->destroyInstance("MTKPanorama");
        mpHal3A = NULL;
    }

    if (m_pMTKMotionObj) {
        m_pMTKMotionObj->MotionExit();
        m_pMTKMotionObj->destroyInstance();
    }
    m_pMTKMotionObj = NULL;

    if (m_pMTKAutoramaObj) {
        m_pMTKAutoramaObj->AutoramaExit();
        m_pMTKAutoramaObj->destroyInstance();
    }
    m_pMTKAutoramaObj = NULL;

    return S_AUTORAMA_OK;
}
/*******************************************************************************
*
********************************************************************************/
MINT32 halAUTORAMA::mHalAutoramaCalcStitch(void* SrcImg,MINT32 gEv,MTKPIPEAUTORAMA_DIRECTION_ENUM DIRECTION
)
{
    MINT32 Retcode = S_AUTORAMA_OK;

    MHAL_LOGD("[mHalAutoramaCalcStitch] \n");

    MTKAutoramaProcInfo AutoramaProcInfo;
    //For first capture

    if(gEv==0 && mpHal3A)
        mpHal3A->send3ACtrl(E3ACtrl_SetAELimiterMode, true, 0);

    MHAL_LOGI("[mHalAutoramaCalcStitch] Panorama EV %d",mAEValue);
    gImgEV[gEv] = mAEValue;

    AutoramaProcInfo.AutoramaCtrlEnum = MTKAUTORAMA_CTRL_ADD_IMAGE;
    AutoramaProcInfo.SrcImgAddr = SrcImg;
    AutoramaProcInfo.EV = gImgEV[gEv];
    AutoramaProcInfo.StitchDirection=(MTKAUTORAMA_DIRECTION_ENUM)DIRECTION;
    Retcode = m_pMTKAutoramaObj->AutoramaFeatureCtrl(MTKAUTORAMA_FEATURE_SET_PROC_INFO, &AutoramaProcInfo, 0);
    if(Retcode!=S_AUTORAMA_OK)
    {
          MHAL_LOGE("[mHalAutoramaCalcStitch] MTKAUTORAMA_FEATURE_SET_PROC_INFO Fail \n");
          return Retcode;
    }
    Retcode = m_pMTKAutoramaObj->AutoramaMain();
    if(Retcode!=S_AUTORAMA_OK)
    {
          MHAL_LOGE("[mHalAutoramaCalcStitch] AutoramaMain Fail\n");
    }
    return Retcode;
}

/*******************************************************************************
*
********************************************************************************/
MINT32 halAUTORAMA::mHalAutoramaDoStitch(
)
{
    MINT32 Retcode = S_AUTORAMA_OK;
    MTKAutoramaProcInfo AutoramaProcInfo;

    MHAL_LOGD("[mHalAutoramaDoStitch] \n");

    AutoramaProcInfo.AutoramaCtrlEnum = MTKAUTORAMA_CTRL_STITCH;
    Retcode = m_pMTKAutoramaObj->AutoramaFeatureCtrl(MTKAUTORAMA_FEATURE_SET_PROC_INFO, &AutoramaProcInfo, 0);
    if(Retcode!=S_AUTORAMA_OK)
    {
        MHAL_LOGD("[mHalAutoramaDoStitch] MTKAUTORAMA_FEATURE_SET_PROC_INFO Fail \n");
        return Retcode;
    }
     /* Stitching the images stored in Pano Driver */
    Retcode = m_pMTKAutoramaObj->AutoramaMain();
    if(Retcode!=S_AUTORAMA_OK)
    {
        MHAL_LOGD("[mHalAutoramaDoStitch] AutoramaMain Fail\n");
    }
    return Retcode;
}

/*******************************************************************************
*
********************************************************************************/
MINT32 halAUTORAMA::mHalAutoramaGetResult(
MTKPipeAutoramaResultInfo* ResultInfo
)
{
    MINT32 Retcode = S_AUTORAMA_OK;
    MTKAutoramaResultInfo AutoramaResultInfo;
    Retcode = m_pMTKAutoramaObj->AutoramaFeatureCtrl(MTKAUTORAMA_FEATURE_GET_RESULT, 0, &AutoramaResultInfo);
    if(Retcode!=S_AUTORAMA_OK)
    {
        MHAL_LOGD("[mHalAutoramaGetResult] MTKAUTORAMA_FEATURE_GET_RESULT Fail\n");
    }
    MHAL_LOGD("[mHalAutoramaGetResult] ImgWidth %d ImgHeight %d ImgBufferAddr 0x%x\n",AutoramaResultInfo.ImgWidth,AutoramaResultInfo.ImgHeight,AutoramaResultInfo.ImgBufferAddr);
    ResultInfo->ImgWidth=AutoramaResultInfo.ImgWidth;
    ResultInfo->ImgHeight=AutoramaResultInfo.ImgHeight;
    ResultInfo->ImgBufferAddr=reinterpret_cast<uintptr_t>(AutoramaResultInfo.ImgBufferAddr);
    return Retcode;
}

/*******************************************************************************
*
********************************************************************************/
MINT32
halAUTORAMA::mHalAutoramaDoMotion(MUINT32* ImgSrc,MUINT32* MotionResult
)
{
      MINT32 err = S_AUTORAMA_OK;
      MTKMotionProcInfo MotionInfo;

    if (!m_pMTKMotionObj) {
        err = E_AUTORAMA_ERR;
        MHAL_LOGE("[mHalAutoramaDoMotion] Err, Init has been called \n");

        return err;
    }
    MotionInfo.ImgAddr = (void *)ImgSrc;
    MHAL_LOGD("[mHalAutoramaDoMotion] ImgAddr 0x%x\n",MotionInfo.ImgAddr);
    m_pMTKMotionObj->MotionFeatureCtrl(MTKMOTION_FEATURE_SET_PROC_INFO, &MotionInfo, NULL);
    m_pMTKMotionObj->MotionMain();
    m_pMTKMotionObj->MotionFeatureCtrl(MTKMOTION_FEATURE_GET_RESULT, NULL, MotionResult);

    MBOOL shot = ((AutoramaMotionResult*)MotionResult)->ReadyToShot > 0 ? true : false;

    if(shot && mpHal3A)
        mpHal3A->send3ACtrl(E3ACtrl_SetAELimiterMode, true, 0);

    return err;
}

MINT32
halAUTORAMA::mHalAutoramaGetWokSize(int SrcWidth, int SrcHeight, int ShotNum, int &WorkingSize)
{
    MTKAutoramaGetEnvInfo AutoramaGetEnvInfo;
    MINT32 Retcode = S_AUTORAMA_OK;

    AutoramaGetEnvInfo.ImgWidth          = SrcWidth;
    AutoramaGetEnvInfo.ImgHeight         = SrcHeight;
    AutoramaGetEnvInfo.MaxSnapshotNumber = ShotNum;
    Retcode = m_pMTKAutoramaObj->AutoramaFeatureCtrl(MTKAUTORAMA_FEATURE_GET_ENV_INFO, 0, &AutoramaGetEnvInfo);
    if(Retcode!=S_AUTORAMA_OK)
    {
        MHAL_LOGD("[mHalAutoramaGetResult] MTKAUTORAMA_FEATURE_GET_RESULT Fail\n");
    }

    WorkingSize = AutoramaGetEnvInfo.WorkingBuffSize;
    return Retcode;
}

/******************************************************************************
 *
 ******************************************************************************/
void
halAUTORAMA::
doNotifyCb(
    MINT32  _msgType,
    MINTPTR _ext1,
    MINTPTR _ext2,
    MINTPTR /*_ext3*/
)
{
    MHAL_LOGD("halAUTORAMA doNotifyCb(%d) %x %x", _msgType, _ext1, _ext2);

    switch(_msgType)
    {
        case IHal3ACb::eID_NOTIFY_AE_RT_PARAMS:
        {
            FrameOutputParam_T* pOutputParam = (FrameOutputParam_T*)_ext2;
            MHAL_LOGD("[doNotifyCb] Panorama EV %d", pOutputParam->i4ExposureValue_x10);
            mAEValue = pOutputParam->i4ExposureValue_x10;

            break;
        }

        default:
            break;
    }
}
