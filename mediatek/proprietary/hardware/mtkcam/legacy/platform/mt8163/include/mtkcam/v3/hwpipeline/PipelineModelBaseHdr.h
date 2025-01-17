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

#ifndef _MTK_PLATFORM_HARDWARE_INCLUDE_MTKCAM_V3_HWPIPELINE_PIPELINEMODELBASEHDR_H_
#define _MTK_PLATFORM_HARDWARE_INCLUDE_MTKCAM_V3_HWPIPELINE_PIPELINEMODELBASEHDR_H_
//
#include <mtkcam/v3/pipeline/IPipelineModel.h>
#include <mtkcam/v3/hwpipeline/HdrStrategy.h>
#include <mtkcam/v3/pipeline/IPipelineBufferSetFrameControl.h>



/******************************************************************************
 *
 ******************************************************************************/
namespace NSCam {
namespace v3 {


/******************************************************************************
 *
 ******************************************************************************/
class PipelineModelBaseHdr
    : public virtual IPipelineModel
    , public IPipelineStreamBufferProvider
    , protected Pipeline::HdrStrategy::IEvaluator
    , public IPipelineNodeCallback
    //, public IPipelineBufferSetFrameControl::IPipelineCallback
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Definitions.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:     ////                    Definitions.
    typedef Pipeline_NodeId_T       NodeId_T;

    typedef NSCam::v3::Utils::      IStreamInfoSetControl
                                    IStreamInfoSetControl;

    typedef NSCam::v3::Utils::      HalMetaStreamBuffer
                                    HalMetaStreamBuffer;

    typedef NSCam::v3::Utils::      HalImageStreamBuffer
                                    HalImageStreamBuffer;

    typedef HalMetaStreamBuffer::   Allocator
                                    HalMetaStreamBufferAllocatorT;

    typedef HalImageStreamBuffer::  Allocator
                                    HalImageStreamBufferAllocatorT;

    typedef HalMetaStreamBufferAllocatorT::StreamBufferPoolT
                                    HalMetaStreamBufferPoolT;

    typedef HalImageStreamBufferAllocatorT::StreamBufferPoolT
                                    HalImageStreamBufferPoolT;

    typedef android::DefaultKeyedVector <StreamId_T, android::sp<HalMetaStreamBufferPoolT> >
                                    HalMetaStreamBufferPoolMapT;

    typedef android::DefaultKeyedVector<StreamId_T, android::sp<HalImageStreamBufferPoolT> >
                                    HalImageStreamBufferPoolMapT;

    typedef NSCam::v3::Utils::IStreamBufferPool<IImageStreamBuffer>
                                    IImageStreamBufferPoolT;

public:     ////                                Definitions.
    typedef Pipeline::HdrStrategy::         RequestAppStreamsInfo
                                                RequestAppStreamsInfo;

    typedef Pipeline::HdrStrategy::         evaluate_request_pipeline
                                                evaluate_request_pipeline;

    typedef Pipeline::HdrStrategy::         refine_meta_stream_buffer_params
                                                refine_meta_stream_buffer_params;

    typedef Pipeline::HdrStrategy::         evaluate_node_io_streams_params
                                                evaluate_node_io_streams_params;

public:     ////                                Definitions.
    typedef IPipelineFrame::ImageInfoIOMap      ImageInfoIOMap;
    typedef IPipelineFrame::MetaInfoIOMap       MetaInfoIOMap;
    typedef IPipelineFrame::ImageInfoIOMapSet   ImageInfoIOMapSet;
    typedef IPipelineFrame::MetaInfoIOMapSet    MetaInfoIOMapSet;
    typedef IPipelineFrame::InfoIOMapSet        InfoIOMapSet;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Definitions.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:     ////                    Definitions.

    struct  Context
    {
        android::sp<IStreamInfoSetControl>      mpStreamInfoSet;
        android::sp<IPipelineDAG>               mpPipelineDAG;
        android::sp<IPipelineNodeMapControl>    mpPipelineNodeMap;
    };

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Implementations.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:  ////                    Operations.

    struct  refine_request_app_params_based_on_face_detect_params
    {
        /**
         * @param[in] input App metadata.
         *  The caller must promise its content.
         *  The callee should not modify it.
         */
        IMetadata const*            pIAppMetaData;

        /**
         * @param[in,out] App stream info.
         *  The caller must promise its initial value.
         *  The callee has an authority to update it based on its initial value.
         */
        RequestAppStreamsInfo*      pAppStreams;
    };

    virtual MERROR                  refineRequestAppParamsLocked(
                                        refine_request_app_params_based_on_face_detect_params& rParams
                                    )   const;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Implementations.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:  ////                    Operations.

    struct  evaluate_app_request_params
    {
        /**
         * @param[in,out] A pointer to the App request.
         *  The caller must promise its initial value.
         *  The callee has an authority to update it based on its initial value.
         */
        AppRequest*                 pAppRequest;

        /**
         * @param[out] output App meta stream buffers.
         *  By default, this field is empty. The callee must be in charge of
         *  adding buffers and update each buffer's users.
         *  Note that the number of output meta streams equals to the number of
         *  partial meta result callbacks.
         */
        android::KeyedVector<
            StreamId_T,
            android::sp<IMetaStreamBuffer>
                            >       vOMetaBuffers;

        /**
         * @param[out] A pointer to the pipeline frame.
         *  By default, this field is NULL. The callee is responsible for
         *  filling it.
         */
        android::sp<IPipelineFrame> pFrame;

        /**
      * @param[out] A vector of pointer to the frame.
         * By default, this field is NULL. The callee is responsible for
         *  filling it.
         */
        android::Vector<
            android::sp<IPipelineFrame>
                            >         vFrame;

    };

public:     ////                    Operations.
    virtual MERROR                  evaluateAppRequest(
                                        evaluate_app_request_params& rParams
                                    );

    virtual MERROR                  submitRequestFrame(
                                        android::sp<IPipelineFrame> pFrame
                                    );

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Implementations.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:  ////                    Data Members.
    mutable android::RWLock         mRWLock;
    MINT32 const                    mOpenId;
    android::String8 const          mName;
    //android::wp<IPipelineModel::IPipelineHdrCallback> mpCB;

protected:  ////                    Data Members.
    Context                         mConfigContext;

protected:  ////                    Data Members.
    HalImageStreamBufferPoolMapT    mHalImageStreamBufferPoolMap;

protected:  ////                    Data Members.
    mutable android::RWLock         mflushLock;
    MBOOL                           mInFlush;

private:    ////                    Data Members.
    MINT                            mLogLevel;          //  log level.
    MINT                            mDebugFdMode;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Implementations.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:  ////                    Operations.
    android::sp<HalImageStreamBufferPoolT>
                                    addHalStreamBufferPoolLocked(
                                        android::sp<IImageStreamInfo> pStreamInfo
                                    );

    android::sp<HalImageStreamBufferPoolT>
                                    replaceHalStreamBufferPoolLocked(
                                        android::sp<IImageStreamInfo> pStreamInfo,
                                        android::sp<HalImageStreamBufferPoolT> pPool
                                    );
protected:  ////                    Operations.

    virtual MVOID                   onDestroyLocked();

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Implementations.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:  ////                    Attributes.
    virtual android::sp<IMetaStreamInfo>
                                    getMetaStreamInfoLocked_FaceDetectResult() const;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Interfaces.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:     ////                    Instantiation.
                                    PipelineModelBaseHdr(
                                        MINT32 const openId,
                                        android::String8 const& name
                                    );

public:     ////                    Attributes.
    virtual Context const&          getConfigContext() const;

    virtual IPipelineStreamBufferProvider const*
                                    getStreamBufferProvider() const;

//    virtual MVOID                    setCallback(
//                                        android::wp<IPipelineHdrCallback> pCB
//                                    );

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  IPipelineBufferSetFrameControl::IAppCallback Interfaces.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    virtual MVOID            updateSubFrame(
                                MUINT32 const frameNo,
                                MINTPTR const userId,
                                ssize_t const /*nOutMetaLeft*/,
                                android::Vector<android::sp<IMetaStreamBuffer> > /*vOutMeta*/
                            );

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Pipeline::HdrtStrategy::IEvaluator
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:     ////                    Attributes.
    virtual IPipelineNodeMapControl*getConfigPipelineNodeMap() const;
    virtual IPipelineDAG*           getConfigPipelineDAG() const;
    virtual IPipelineNodeCallback*  getPipelineNodeCallback() const;

public:     ////                    Operations.
    virtual MERROR                  refineRequestAppParams(
                                        evaluate_request_pipeline::Params& rParams
                                    )   const;
// FIX ME:
    virtual MUINT                   queryMinimalUsage(
                                        NodeId_T const nodeId,
                                        IImageStreamInfo const*const pStreamInfo
                                    )   const;

public:     ////                    Attributes.
    virtual MERROR                  acquireHalStreamBuffer(
                                        android::sp<IImageStreamInfo> const pStreamInfo,
                                        android::sp<HalImageStreamBuffer>& rpStreamBuffer
                                    )   const;

public:     ////                    Operations.
    virtual MVOID                   dump(android::Vector<android::String8>& rLogs, InfoIOMapSet const& rIOMapSet) const;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  IPipelineModel Interfaces.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:     ////                    Attributes.
    virtual char const*             getName() const     { return mName.string(); }
    virtual MINT32                  getOpenId() const   { return mOpenId; }

public:     ////                    Operations.
    virtual MERROR                  submitRequest(AppRequest& request);

    virtual MERROR                  beginFlush();

    virtual MVOID                   endFlush();

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  IPipelineNodeCallback Interfaces.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:     ////                    Operations.
    virtual MVOID                   onDispatchFrame(
                                        android::sp<IPipelineFrame> const& pFrame,
                                        NodeId_T nodeId
                                    ) = 0;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  RefBase Interfaces.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
protected:  ////                    Operations.
    virtual void                    onLastStrongRef(const void* id);

};


/******************************************************************************
 *
 ******************************************************************************/
};  //namespace v3
};  //namespace NSCam
#endif  //_MTK_PLATFORM_HARDWARE_INCLUDE_MTKCAM_V3_HWPIPELINE_PIPELINEMODELBASEHDR_H_

