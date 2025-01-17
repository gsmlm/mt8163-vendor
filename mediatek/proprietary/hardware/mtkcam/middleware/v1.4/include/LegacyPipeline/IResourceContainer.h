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

#ifndef _MTK_HARDWARE_INCLUDE_MTKCAM_LEGACYPIPELINE_IRESOURCECONTAINER_H_
#define _MTK_HARDWARE_INCLUDE_MTKCAM_LEGACYPIPELINE_IRESOURCECONTAINER_H_
//
#include <utils/RefBase.h>
#include <utils/Vector.h>

#include <v3/stream/IStreamInfo.h>
#include <LegacyPipeline/buffer/StreamBufferProvider.h>

#include <LegacyPipeline/ILegacyPipeline.h>


using namespace android;
using namespace NSCam::v1;
using namespace NSCam::v1::NSLegacyPipeline;


namespace NSCam {

/******************************************************************************
 *
 ******************************************************************************/
class IFrameInfo
    : public virtual android::RefBase
    , public ResultProcessor::IListener
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Interface.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:

    virtual                     ~IFrameInfo() {};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Implementations.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
    virtual void                getFrameMetadata(IMetadata &rResultMeta) = 0;
};

/******************************************************************************
 *
 ******************************************************************************/
class FrameInfo
    : public virtual android::RefBase
    , public IFrameInfo
{
public:
                                 FrameInfo();
                                 ~FrameInfo();
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //  IListener Interface.
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
    virtual void                onResultReceived(
                                    MUINT32         const requestNo,
                                    StreamId_T      const streamId,
                                    MBOOL           const errorResult,
                                    IMetadata       const result
                                );

    virtual void                onFrameEnd(
                                    MUINT32         const requestNo
                                ) {};

    virtual String8             getUserName();


    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //  Public Interface.
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
    virtual void                getFrameMetadata(IMetadata &rResultMeta);

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //  Implementations.
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:
    IMetadata                    mResultMeta;
    mutable Mutex                mResultSetLock;

};

/******************************************************************************
 *
 ******************************************************************************/
class IResourceContainer
    : public android::RefBase
{
public:
    static sp<IResourceContainer>      getInstance(MINT32 openId) ;

    virtual                            ~IResourceContainer() {}

    virtual MVOID                      setFeatureFlowControl( sp<IFeatureFlowControl> pControl ) = 0;

    virtual MVOID                      setConsumer( StreamId_T id, sp<StreamBufferProvider> pProvider ) = 0;

    virtual sp<StreamBufferProvider>   queryConsumer(StreamId_T id ) = 0;

    virtual sp<IFeatureFlowControl>    queryFeatureFlowControl() = 0;

    virtual MVOID                      setLatestFrameInfo( sp<IFrameInfo> frameInfo ) = 0;

    virtual sp<IFrameInfo>             queryLatestFrameInfo() = 0;
};

};


#endif  //_MTK_HARDWARE_INCLUDE_MTKCAM_LEGACYPIPELINE_IRESOURCECONTAINER_H_

