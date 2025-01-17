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
#ifndef _MTK_CAMERA_FEATURE_PIPE_BOKEH_PIPE_NODE_H_
#define _MTK_CAMERA_FEATURE_PIPE_BOKEH_PIPE_NODE_H_
//
#include <core/include/CamThreadNode.h>
#include <core/include/ImageBufferPool.h>
#include <mmsdk/EffectRequest.h>
//
#include "bokeh_common.h"
//
#define UNUSED(expr) do { (void)(expr); } while (0)
//
#define FUNC_START  MY_LOGD("+")
#define FUNC_END    MY_LOGD("-")
//
namespace NSCam {
namespace NSCamFeature {
namespace NSFeaturePipe {
//
typedef android::sp<EffectRequest> EffectRequestPtr;
typedef android::sp<EffectFrameInfo> FrameInfoPtr;
//
class BokehPipeDataHandler
{
public:
    typedef BokehPipeDataID DataID;
public:
    virtual ~BokehPipeDataHandler();
    virtual MBOOL onData(DataID id, EffectRequestPtr &data)
    {
        UNUSED(id);
        UNUSED(data);
        return MFALSE;
    }
    virtual MBOOL onData(DataID id, FrameInfoPtr &data)
    {
        UNUSED(id);
        UNUSED(data);
        return MFALSE;
    }
    virtual MBOOL onData(DataID id, SmartImageBuffer &data)
    {
        UNUSED(id);
        UNUSED(data);
        return MFALSE;
    }
    static const char* ID2Name(DataID id);
};
//************************************************************************
class BokehPipeNode :
            public BokehPipeDataHandler,
            public CamThreadNode<BokehPipeDataHandler>
{
public:
    typedef CamGraph<BokehPipeNode> Graph_T;
    typedef BokehPipeDataHandler Handler_T;
//
public:
    BokehPipeNode(
            const char *name,
            Graph_T *graph);
    virtual ~BokehPipeNode();
    void enableDumpImage(MBOOL flag);
//
protected:
    MBOOL onInit()          override    { return MTRUE; }
    MBOOL onUninit()        override    { return MTRUE; }
    MBOOL onThreadStart()   override    { return MTRUE; }
    MBOOL onThreadStop()    override    { return MTRUE; }
    virtual MBOOL onThreadLoop() = 0;
//
protected:
    bool                    miPipeLogEnable = false;
    MBOOL                   mbDumpImageBuffer = MFALSE;
};
}; // namespace NSFeaturePipe
}; // namespace NSCamFeature
}; // namespace NSCam
#endif // _MTK_CAMERA_FEATURE_PIPE_BOKEH_PIPE_NODE_H_