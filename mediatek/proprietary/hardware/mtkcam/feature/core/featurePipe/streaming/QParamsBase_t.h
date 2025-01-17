/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein is
 * confidential and proprietary to MediaTek Inc. and/or its licensors. Without
 * the prior written permission of MediaTek inc. and/or its licensors, any
 * reproduction, modification, use or disclosure of MediaTek Software, and
 * information contained herein, in whole or in part, shall be strictly
 * prohibited.
 *
 * MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER
 * ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 * NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH
 * RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 * INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES
 * TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.
 * RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO
 * OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES CONTAINED IN MEDIATEK
 * SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE
 * RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S
 * ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE
 * RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE
 * MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE
 * CHARGE PAID BY RECEIVER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek
 * Software") have been modified by MediaTek Inc. All revisions are subject to
 * any receiver's applicable license agreements with MediaTek Inc.
 */

#ifndef _MTK_CAMERA_STREAMING_FEATURE_PIPE_QPARAMS_BASE_T_H_
#define _MTK_CAMERA_STREAMING_FEATURE_PIPE_QPARAMS_BASE_T_H_

#include "MtkHeader.h"
//#include <mtkcam/iopipe/PostProc/IHalPostProcPipe.h>

#include <utils/RefBase.h>
#include <utils/Mutex.h>

#include <queue>

namespace NSCam {
namespace NSCamFeature {
namespace NSFeaturePipe {

template <typename T>
class QParamsBase : public virtual android::RefBase
{
public:
    class BACKUP_DATA_TYPE
    {
    public:
        BACKUP_DATA_TYPE()
        {
        }

        BACKUP_DATA_TYPE(NSCam::NSIoPipe::NSPostProc::QParams qparams, const T &data)
            : mQParamsCookie(qparams.mpCookie)
            , mQParamsCB(qparams.mpfnEnQFailCallback)
            , mQParamsFailCB(qparams.mpfnEnQFailCallback)
            , mQParamsBlockCB(qparams.mpfnEnQBlockCallback)
            , mData(data)
        {
        }

        void restore(NSCam::NSIoPipe::NSPostProc::QParams &qparams)
        {
            qparams.mpCookie = mQParamsCookie;
            qparams.mpfnCallback = mQParamsCB;
            qparams.mpfnEnQFailCallback = mQParamsFailCB;
            qparams.mpfnEnQBlockCallback = mQParamsBlockCB;
        }

        void *mQParamsCookie;
        NSCam::NSIoPipe::NSPostProc::QParams::PFN_CALLBACK_T mQParamsCB;
        NSCam::NSIoPipe::NSPostProc::QParams::PFN_CALLBACK_T mQParamsFailCB;
        NSCam::NSIoPipe::NSPostProc::QParams::PFN_CALLBACK_T mQParamsBlockCB;
        T mData;
    };

    QParamsBase();
    virtual ~QParamsBase();

protected:
    virtual MBOOL onQParamsCB(const NSCam::NSIoPipe::NSPostProc::QParams &param, const T &data) = 0;
    virtual MBOOL onQParamsFailCB(const NSCam::NSIoPipe::NSPostProc::QParams &param, const T &data);
    virtual MBOOL onQParamsBlockCB(const NSCam::NSIoPipe::NSPostProc::QParams &param, const T &data);

    enum CB_TYPE { CB_DONE, CB_FAIL, CB_BLOCK };
    static void processCB(NSCam::NSIoPipe::NSPostProc::QParams param, CB_TYPE type);

public:
    static void staticQParamsCB(NSCam::NSIoPipe::NSPostProc::QParams &param);
    static void staticQParamsFailCB(NSCam::NSIoPipe::NSPostProc::QParams &param);
    static void staticQParamsBlockCB(NSCam::NSIoPipe::NSPostProc::QParams &param);

protected:
    MBOOL enqueQParams(NSCam::NSIoPipe::NSPostProc::INormalStream *stream, NSCam::NSIoPipe::NSPostProc::QParams param, const T &data);
    MVOID waitEnqueQParamsDone();
    MVOID signalDone();

private:
    MBOOL retrieveQParamsData(BACKUP_DATA_TYPE &data);

private:
    android::Mutex mMutex;
    android::Condition mCondition;
    std::queue<BACKUP_DATA_TYPE> mQueue;
    unsigned mCount;
};

} // namespace NSFeaturePipe
} // namespace NSCamFeature
} // namespace NSCam

#endif // _MTK_CAMERA_STREAMING_FEATURE_PIPE_QPARAMS_BASE_T_H_
