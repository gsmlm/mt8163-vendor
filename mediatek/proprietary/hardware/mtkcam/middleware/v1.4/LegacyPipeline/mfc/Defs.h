/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2015. All rights reserved.
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

#ifndef _MTK_HARDWARE_MTKCAM_LEGACYPIPELINE_PIPELINEBUILDER_MFC_DEFS_H_
#define _MTK_HARDWARE_MTKCAM_LEGACYPIPELINE_PIPELINEBUILDER_MFC_DEFS_H_

#include <utils/RefBase.h>
#include <v3/stream/IStreamInfo.h>

using namespace android;
using namespace NSCam::v3;

// ---------------------------------------------------------------------------

namespace NSCam {
namespace v1 {
namespace NSLegacyPipeline {

enum NodeConfig
{
    eNodeConfigNone  = 0x0,
    eNodeConfigP1    = 0x1,
    eNodeConfigHdr   = 0x2,
    eNodeConfigMfll  = 0x4,
    eNodeConfigJpeg  = 0x8
};

struct Configuration : public virtual VirtualLightRefBase
{
    // input
    sp<IMetaStreamInfo>   controlMeta_App;
    sp<IMetaStreamInfo>   controlMeta_Hal;

    // output (metadata)
    sp<IMetaStreamInfo>   resultMeta_P1_App;
    sp<IMetaStreamInfo>   resultMeta_P1_Hal;
    sp<IMetaStreamInfo>   resultMeta_MFC_App;
    sp<IMetaStreamInfo>   resultMeta_MFC_Hal;
    sp<IMetaStreamInfo>   resultMeta_Jpeg_App;

    // output (image)
    sp<IImageStreamInfo>  imageInfo_imgoRaw;
    sp<IImageStreamInfo>  imageInfo_rrzoRaw;
    sp<IImageStreamInfo>  imageInfo_yuv00;
    sp<IImageStreamInfo>  imageInfo_yuvJpeg;
    sp<IImageStreamInfo>  imageInfo_yuvThumbnail;
    sp<IImageStreamInfo>  imageInfo_jpeg;

    // used to check which node is configured
    MUINT32 configFlag;

    Configuration()
    : configFlag(eNodeConfigNone)
    {}
};

} // NSLegacyPipeline
} // namespace v1
} // namespace NSCam

#endif // _MTK_HARDWARE_MTKCAM_LEGACYPIPELINE_PIPELINEBUILDER_MFC_DEFS_H_
