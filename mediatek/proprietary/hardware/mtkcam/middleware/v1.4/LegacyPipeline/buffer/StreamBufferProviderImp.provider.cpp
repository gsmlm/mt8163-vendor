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

#define LOG_TAG "MtkCam/BufferProvider_P"
//
#include "MyUtils.h"
//
#include <v3/utils/streaminfo/MetaStreamInfo.h>
#include <v3/utils/streaminfo/ImageStreamInfo.h>
#include <v3/utils/streambuf/StreamBuffers.h>
//
#include "StreamBufferProviderImp.h"
#include "PairMetadataImp.h"

using namespace android;
using namespace NSCam;
using namespace NSCam::v1;
using NSCam::v3::Utils::HalImageStreamBufferProvider;

/******************************************************************************
 *
 ******************************************************************************/
#define MY_LOGV(fmt, arg...)        CAM_LOGV("[%s][%s] " fmt, __FUNCTION__, mName, ##arg)
#define MY_LOGD(fmt, arg...)        CAM_LOGD("[%s][%s] " fmt, __FUNCTION__, mName, ##arg)
#define MY_LOGI(fmt, arg...)        CAM_LOGI("[%s][%s] " fmt, __FUNCTION__, mName, ##arg)
#define MY_LOGW(fmt, arg...)        CAM_LOGW("[%s][%s] " fmt, __FUNCTION__, mName, ##arg)
#define MY_LOGE(fmt, arg...)        CAM_LOGE("[%s][%s] " fmt, __FUNCTION__, mName, ##arg)
#define MY_LOGA(fmt, arg...)        CAM_LOGA("[%s][%s] " fmt, __FUNCTION__, mName, ##arg)
#define MY_LOGF(fmt, arg...)        CAM_LOGF("[%s][%s] " fmt, __FUNCTION__, mName, ##arg)
//
#define MY_LOGV_IF(cond, ...)       do { if ( (cond) ) { MY_LOGV(__VA_ARGS__); } }while(0)
#define MY_LOGD_IF(cond, ...)       do { if ( (cond) ) { MY_LOGD(__VA_ARGS__); } }while(0)
#define MY_LOGI_IF(cond, ...)       do { if ( (cond) ) { MY_LOGI(__VA_ARGS__); } }while(0)
#define MY_LOGW_IF(cond, ...)       do { if ( (cond) ) { MY_LOGW(__VA_ARGS__); } }while(0)
#define MY_LOGE_IF(cond, ...)       do { if ( (cond) ) { MY_LOGE(__VA_ARGS__); } }while(0)
#define MY_LOGA_IF(cond, ...)       do { if ( (cond) ) { MY_LOGA(__VA_ARGS__); } }while(0)
#define MY_LOGF_IF(cond, ...)       do { if ( (cond) ) { MY_LOGF(__VA_ARGS__); } }while(0)
//
#define MY_LOGD1(...)               MY_LOGD_IF((mLogLevel>=1),__VA_ARGS__)
#define MY_LOGD2(...)               MY_LOGD_IF((mLogLevel>=2),__VA_ARGS__)
#define MY_LOGD3(...)               MY_LOGD_IF((mLogLevel>=3),__VA_ARGS__)
//
#define FUNC_START                  MY_LOGD1("+")
#define FUNC_END                    MY_LOGD1("-")
#define FUNC_NAME                   MY_LOGD1("");
//
#define THREAD_NAME       ("Cam@BufferProvider_P")
#define THREAD_POLICY     (SCHED_OTHER)
#define THREAD_PRIORITY   (0)
/******************************************************************************
 *
 ******************************************************************************/
template <typename T>
inline MBOOL
tryGetMetadata(
    IMetadata* pMetadata,
    MUINT32 const tag,
    T & rVal
)
{
    if( pMetadata == NULL ) {
        //MY_LOGW("pMetadata == NULL");
        return MFALSE;
    }

    IMetadata::IEntry entry = pMetadata->entryFor(tag);
    if( !entry.isEmpty() ) {
        rVal = entry.itemAt(0, Type2Type<T>());
        return MTRUE;
    }
    return MFALSE;
}

/******************************************************************************
 *
 ******************************************************************************/
PStreamBufferProviderImp::
PStreamBufferProviderImp()
    : mName(LOG_TAG)
{
    //FUNC_NAME;
    mLogLevel = ::property_get_int32("debug.camera.log", 0);
    if ( mLogLevel == 0 ) {
        mLogLevel = ::property_get_int32("debug.camera.log.LegacyPipeline", 1);
    }
}

PStreamBufferProviderImp::
~PStreamBufferProviderImp()
{
    FUNC_NAME;
}

/******************************************************************************
 *
 ******************************************************************************/
MERROR
PStreamBufferProviderImp::
dequeStreamBuffer(
    MUINT32 const                       iRequestNo,
    android::sp<IImageStreamInfo> const rpStreamInfo,
    android::sp<HalImageStreamBuffer>&  rpStreamBuffer
)
{
    //FUNC_START;

    MUINT32 transform = 0;
    sp<IImageBufferHeap> pHeap;
    {
        Mutex::Autolock _l(mPoolLock);

        if ( mpBufferPool == 0 ) {
            MY_LOGE("Buffer pool does not exist.");
            return UNKNOWN_ERROR;
        }
        //
        if ( mpBufferPool->acquireFromPool(LOG_TAG, iRequestNo, pHeap, transform) != OK ) {
            MY_LOGV("Cannot acquire from pool. Something wrong... SOS");
            return NO_MEMORY;
        }
    }

    rpStreamInfo->setTransform(transform);
    rpStreamBuffer = new HalImageStreamBufferProvider(mpImageStreamInfo, pHeap, static_cast< wp<IStreamBufferProvider> >(this));

    if ( rpStreamBuffer == 0) {
        MY_LOGE("Cannot new HalImageStreamBuffer. Something wrong...");
        return NO_MEMORY;
    }

    {
        MY_LOGD("[%d] buffer:%p pHeap:%p", iRequestNo, rpStreamBuffer.get(), pHeap.get());
        Mutex::Autolock _l(mBufferLock);
        mBufferMap.add(rpStreamBuffer.get(), Buffer_T{iRequestNo, pHeap});
    }

    //FUNC_END;

    return OK;
}

/******************************************************************************
 *
 ******************************************************************************/
MERROR
PStreamBufferProviderImp::
enqueStreamBuffer(
    android::sp<IImageStreamInfo> const rpStreamInfo,
    android::sp<HalImageStreamBuffer>   rpStreamBuffer,
    MUINT32                             bBufStatus
)
{
    //FUNC_START;

    if ( mpBufferPool == 0 ) {
        MY_LOGE("Buffer pool does not exist.");
        return UNKNOWN_ERROR;
    }
    //
    if ( rpStreamBuffer == 0 ) {
        MY_LOGE("return NULL buffer");
        return UNKNOWN_ERROR;
    }
    //
    sp<IImageBufferHeap> rpHeap;
    MUINT32              requestNo;
    {
        Mutex::Autolock _l(mBufferLock);
        Buffer_T buf = mBufferMap.editValueFor( rpStreamBuffer.get() );
        //
        requestNo   = buf.requestNo;
        rpHeap      = buf.heap;
        //
        mBufferMap.removeItem(rpStreamBuffer.get());
    }

    MY_LOGD("[%d] bBufStatus:%d pHeap:%p", requestNo, bBufStatus, rpHeap.get());
    {
        Vector<ResultSet_T> tempSetMap;
        tempSetMap.push_back(
            ResultSet_T{
                .requestNo = requestNo,
                .heap      = rpHeap,
                .error     = bBufStatus & STREAM_BUFFER_STATUS::ERROR,
                .timestamp = -1
            }
        );
        handleResult(tempSetMap);
    }

    //FUNC_END;

    return OK;
}


/******************************************************************************
 *
 ******************************************************************************/
MVOID
PStreamBufferProviderImp::
handleResult(
    Vector<ResultSet_T> const& rvResult
)
{
    Mutex::Autolock _l(mResultSetLock);
    //
    for ( size_t i = 0; i < rvResult.size(); ++i )
    {
        ssize_t const index = mResultSetMap.indexOfKey(rvResult[i].requestNo);
        if ( index < 0 )
        {
            MY_LOGD2("ADD:i(%d/%d), reqNo(%d)",
                    i, rvResult.size(),
                    rvResult[i].requestNo);
            mResultSetMap.add(rvResult[i].requestNo, rvResult[i]);
        }
        else
        {
            MY_LOGD2("EDIT:i(%d/%d), reqNo(%d)",
                    i, rvResult.size(),
                    rvResult[i].requestNo);
            //
            ResultSet_T* result = &mResultSetMap.editValueAt(index);
            result->heap        = ( rvResult[i].heap == NULL ) ? result->heap : rvResult[i].heap;
            result->error      |= rvResult[i].error;
            result->timestamp   = ( rvResult[i].timestamp >= 0 ) ? rvResult[i].timestamp : result->timestamp;
        }
    }

    handleReturn();
}

/******************************************************************************
 *
 ******************************************************************************/
status_t
PStreamBufferProviderImp::
handleReturn()
{
    size_t i = 0;
    while ( i < mResultSetMap.size() ) {
        ResultSet_T* r = &mResultSetMap.editValueAt(i);
        //
        if( r->heap != NULL && r->timestamp >= 0) {
            // buffer & timestamp callback
            if ( mpConsumer != 0 ) {
                mpConsumer->getResultBufferFromProvider(r->requestNo, r->heap, r->timestamp, r->error);
                Mutex::Autolock _l(mConsumerLock);
                mConsumerMap.add(r->requestNo, mResultSetMap.editValueAt(i));
                //
                mResultSetMap.removeItemsAt(i);
                continue;
            }
            //
            MY_LOGW_IF( r->timestamp == 0, "No timestamp information in result metadata.");
            {
                MY_LOGD1("i(%d/%d) release reqNo(%d) buf:%p TS:%lld err:%d",
                        i,
                        mResultSetMap.size()-1,
                        r->requestNo,
                        r->heap.get(),
                        r->timestamp,
                        r->error);
                Mutex::Autolock _l(mPoolLock);
                mpBufferPool->releaseToPool(mName, r->requestNo, r->heap, r->timestamp, r->error);
            }
            //
            mResultSetMap.removeItemsAt(i);
            continue;
        }
        ++i;
    }
    //
    // remove invalid result set.
    Vector< MUINT32 > rvFrameEnd;
    {
        Mutex::Autolock _l(mLock);
        rvFrameEnd = mvFrameEnd;
        mvFrameEnd.clear();
    }
    for ( size_t j = 0; j < rvFrameEnd.size(); ++j) {
        mResultSetMap.removeItem(rvFrameEnd[j]);
    }

    return OK;
}

/******************************************************************************
 *
 ******************************************************************************/
status_t
PStreamBufferProviderImp::
returnBuffer(
    sp<IImageBufferHeap>    rpHeap
)
{
    MY_LOGD("return to provider rpHeap:%p", rpHeap.get());
    Mutex::Autolock _l(mConsumerLock);
    bool bFind = false;
    for ( size_t i = 0; i < mConsumerMap.size(); ++i )
    {
        if ( mConsumerMap[i].heap.get() == rpHeap.get() )
        {
            Mutex::Autolock _l(mPoolLock);
            MY_LOGD("i(%d/%d) release ReqNo(%d) buf:%p TS:%lld err:%d",
                    i,
                    mConsumerMap.size()-1,
                    mConsumerMap[i].requestNo,
                    rpHeap.get(),
                    mConsumerMap[i].timestamp,
                    mConsumerMap[i].error);
            mpBufferPool->releaseToPool(mName, mConsumerMap[i].requestNo, rpHeap, mConsumerMap[i].timestamp, mConsumerMap[i].error);
            mConsumerMap.removeItemsAt(i);
            bFind = true;
            break;
        }
    }
    if(!bFind)
    {
        MY_LOGW("returnBuffer not found in mConsumerMap!");
    }
    return OK;
}

/******************************************************************************
 *
 ******************************************************************************/
status_t
PStreamBufferProviderImp::
setImageStreamInfo(
    android::sp<IImageStreamInfo> pStreamInfo
)
{
    mpImageStreamInfo = pStreamInfo;
    mName = mpImageStreamInfo->getStreamName();
    return OK;
}

/******************************************************************************
 *
 ******************************************************************************/
sp<IImageStreamInfo>
PStreamBufferProviderImp::
queryImageStreamInfo()
{
    return mpImageStreamInfo;
}


/******************************************************************************
 *
 ******************************************************************************/
status_t
PStreamBufferProviderImp::
setBufferPool(
    android::sp< IBufferPool >    pBufProvider
)
{
    Mutex::Autolock _l(mPoolLock);
    mpBufferPool = pBufProvider;
    return OK;
}

/******************************************************************************
 *
 ******************************************************************************/
status_t
PStreamBufferProviderImp::
setSelector(
    android::sp< ISelector > pRule
)
{
    pRule->setPool(this);

    return ( mpConsumer == 0) ? UNKNOWN_ERROR : mpConsumer->setSelector(pRule);
}

/******************************************************************************
 *
 ******************************************************************************/
status_t
PStreamBufferProviderImp::
setPairRule(
    android::sp< PairMetadata > pConsumer
)
{
    MY_LOGD("pConsumer(%p)",pConsumer.get());
    mpConsumer = pConsumer;
    return OK;
}

/******************************************************************************
 *
 ******************************************************************************/
android::sp< ISelector >
PStreamBufferProviderImp::
querySelector()
{
    return ( mpConsumer == 0) ? NULL : mpConsumer->querySelector();
}

/******************************************************************************
 *
 ******************************************************************************/
void
PStreamBufferProviderImp::
onLastStrongRef(const void* /*id*/)
{
    FUNC_START;

    if( mpConsumer != NULL )
    {
        MY_LOGD("flush mpConsumer");
        mpConsumer->flush();
    }
    //
    struct Log
    {
        static  MVOID
        dump(KeyedVector<MUINT32, ResultSet_T>& rMap, String8 str) {
            for (size_t i = 0; i < rMap.size(); i++) {
                CAM_LOGW("%s [%d] buffer:%p timeStamp:%lld error:%d",
                    str.string(),
                    rMap[i].requestNo,
                    rMap[i].heap.get(),
                    rMap[i].timestamp,
                    rMap[i].error
                );
            }
        }
    };

    Log::dump(mConsumerMap , String8::format("[%s] %s" , mName, "selector not return."));
    Log::dump(mResultSetMap, String8::format("[%s] %s" , mName, "not return to pool."));

    FUNC_END;
}

/******************************************************************************
 *
 ******************************************************************************/
void
PStreamBufferProviderImp::
flush()
{
    if( mpConsumer != NULL )
    {
        MY_LOGD("flush mpConsumer");
        mpConsumer->flush();
    }
}

/******************************************************************************
 *
 ******************************************************************************/
void
PStreamBufferProviderImp::
doTimestampCallback(
    MUINT32     const requestNo,
    MBOOL       const errorResult,
    MINT64      const timestamp
)
{
    MY_LOGD("reqNo(%d),err(%d),TS(%lld)", requestNo, errorResult, timestamp);
    //
    Vector<ResultSet_T> tempSetMap;
    tempSetMap.push_back(
        ResultSet_T{
            .requestNo = requestNo,
            .heap      = NULL,
            .error     = errorResult,
            .timestamp = timestamp
        }
    );
    handleResult(tempSetMap);
}

/******************************************************************************
 *
 ******************************************************************************/
void
PStreamBufferProviderImp::
onFrameEnd(
    MUINT32     const requestNo
)
{
    Mutex::Autolock _l(mLock);
    mvFrameEnd.push_back(requestNo);
}
