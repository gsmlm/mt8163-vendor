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

#ifndef _MTK_PLATFORM_HARDWARE_INCLUDE_MTKCAM_LEGACYPIPELINE_STREAMID_H_
#define _MTK_PLATFORM_HARDWARE_INCLUDE_MTKCAM_LEGACYPIPELINE_STREAMID_H_
//


/******************************************************************************
 *
 ******************************************************************************/
namespace NSCam {


/******************************************************************************
 * Legacy Pipeline Stream ID
 ******************************************************************************/
enum
{
    //==========================================================================
    eSTREAMID_BEGIN_OF_PIPE = 0,
    //==========================================================================

        eSTREAMID_IMAGE_PIPE_RAW_OPAQUE,

        eSTREAMID_IMAGE_PIPE_RAW_RESIZER,

        eSTREAMID_IMAGE_PIPE_RAW16,

        eSTREAMID_IMAGE_PIPE_YUV_00,

        eSTREAMID_IMAGE_PIPE_YUV_01,

        eSTREAMID_IMAGE_YUV_FD,

        eSTREAMID_IMAGE_PIPE_YUV_JPEG,

        eSTREAMID_IMAGE_PIPE_YUV_THUMBNAIL,

        eSTREAMID_IMAGE_JPEG,

        // Please add META HAL insides
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        eSTREAMID_META_HAL_BEGIN   = (eSTREAMID_BEGIN_OF_PIPE + 0x1000UL),
        eSTREAMID_META_HAL_CONTROL = eSTREAMID_META_HAL_BEGIN,
        eSTREAMID_META_HAL_DYNAMIC_P1,
        eSTREAMID_META_HAL_DYNAMIC_P2,
        eSTREAMID_META_HAL_DYNAMIC_HDR,
        // HalMetas:
        eSTREAMID_META_HAL_CONTROL_MAIN2,
        eSTREAMID_META_HAL_DYNAMIC_P1_MAIN2,
        eSTREAMID_META_HAL_DYNAMIC_DEPTH,
        eSTREAMID_META_HAL_DYNAMIC_BOKEH,
        // Full Result
        eSTREAMID_META_HAL_FULL,

        // Please add META APP insides
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        eSTREAMID_META_APP_BEGIN   = (eSTREAMID_BEGIN_OF_PIPE + 0x2000UL),
        eSTREAMID_META_APP_CONTROL = eSTREAMID_META_APP_BEGIN,
        eSTREAMID_META_APP_DYNAMIC_P1,
        eSTREAMID_META_APP_DYNAMIC_P2,
        eSTREAMID_META_APP_DYNAMIC_FD,
        eSTREAMID_META_APP_DYNAMIC_JPEG,
        eSTREAMID_META_APP_DYNAMIC_HDR,
        // AppMetas:
        eSTREAMID_META_APP_CONTROL_MAIN2,
        eSTREAMID_META_APP_DYNAMIC_P1_MAIN2,
        eSTREAMID_META_APP_DYNAMIC_DEPTH,
        eSTREAMID_META_APP_DYNAMIC_FDYUV,
        eSTREAMID_META_APP_DYNAMIC_BOKEH,
        eSTREAMID_META_APP_DYNAMIC_BOKEH_JPG,
        eSTREAMID_META_APP_DYNAMIC_JPS,
        // Full Result
        eSTREAMID_META_APP_FULL,

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        eSTREAMID_IMAGE_HDR,

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        eSTREAMID_IMAGE_MFLL,
        eSTREAMID_META_HAL_DYNAMIC_MFLL,
        eSTREAMID_META_APP_DYNAMIC_MFLL,

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        eSTREAMID_IMAGE_NR3D,

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // VSDoF
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        eSTREAMID_IMAGE_PIPE_RAW_OPAQUE_01,
        eSTREAMID_IMAGE_PIPE_RAW_RESIZER_01,

        // DepthmapNode
        eSTREAMID_IMAGE_PIPE_DEPTHMAPNODE_MY_SYUV,
        eSTREAMID_IMAGE_PIPE_DEPTHMAPNODE_DMWYUV,
        eSTREAMID_IMAGE_PIPE_DEPTHMAPNODE_MAINIMAGEYUV,
        eSTREAMID_IMAGE_PIPE_DEPTHMAPNODE_FDYUV,
        eSTREAMID_IMAGE_PIPE_DEPTHMAPNODE_MAINIMAGE_CAPYUV,
        eSTREAMID_IMAGE_PIPE_DEPTHMAPNODE_JPSMAIN1YUV,
        eSTREAMID_IMAGE_PIPE_DEPTHMAPNODE_JPSMAIN2YUV,
        eSTREAMID_IMAGE_PIPE_DEPTHMAPNODE_DEPTHMAPYUV,
        // BokehNode
        eSTREAMID_IMAGE_PIPE_BOKEHNODE_RECORDYUV,
        eSTREAMID_IMAGE_PIPE_BOKEHNODE_PREVIEWYUV,
        eSTREAMID_IMAGE_PIPE_BOKEHNODE_CLEANIMAGEYUV,
        eSTREAMID_IMAGE_PIPE_BOKEHNODE_RESULTYUV,
        // DualImageTransformNode
        eSTREAMID_IMAGE_PIPE_DUALIMAGETRANSFORM_JPSYUV,
        // Jpeg
        eSTREAMID_IMAGE_PIPE_JPG_Bokeh,
        eSTREAMID_IMAGE_PIPE_JPG_JPS,

    //==========================================================================
    eSTREAMID_END_OF_PIPE = (0x7FFFFFFFUL),
    //==========================================================================
};


/******************************************************************************
 *
 ******************************************************************************/
};  //namespace NSCam
#endif  //_MTK_PLATFORM_HARDWARE_INCLUDE_MTKCAM_LEGACYPIPELINE_STREAMID_H_

