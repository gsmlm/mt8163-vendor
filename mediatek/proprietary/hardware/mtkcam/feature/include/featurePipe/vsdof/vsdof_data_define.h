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
#ifndef _MTK_CAMERA_INCLUDE_VSDOF_DATA_ID_H
#define _MTK_CAMERA_INCLUDE_VSDOF_DATA_ID_H
// common
#define VSDOF_FRAME_SCENARIO "FRAME_SCENARIO"
#define VSDOF_FRAME_BOKEH_LEVEL "BOKEH_LEVEL"
//
#define BOKEH_EFFECT_REQUEST_OPEN_ID "BOKEH_PIPE_OPENID"
#define BOKEH_EFFECT_REQUEST_RUN_PATH "BOKEH_PIPE_RUN_PATH"
#define BOKEH_EFFECT_REQUEST_ERROR_MSG "BOKEH_EFFECT_HAL_ERROR_MSG"
#define VSDOF_FRAME_AF_TRIGGER_FLAG "GF_AF_TRIGGER_FLAG"
#define VSDOF_FRAME_AF_POINT_X "GF_AF_POINT_X"
#define VSDOF_FRAME_AF_POINT_Y "GF_AF_POINT_Y"
#define VSDOF_FRAME_3DNR_FLAG "NR3D_FLAG"
#define VSDOF_FRAME_GMV_X "BOKEH_GMV_X"
#define VSDOF_FRAME_GMV_Y "BOKEH_GMV_Y"
#define VSDOF_FRAME_CMV_X "BOKEH_CMV_X"
#define VSDOF_FRAME_CMV_Y "BOKEH_CMV_Y"
#define VSDOF_FRAME_ISO "BOKEH_ISO"
#define VSDOF_FRAME_USER_DATA "USER_DATA"
#define VSDOF_FRAME_G_SENSOR_ORIENTATION "BOKEH_G_SENSOR"
#define BOKEH_PIPELINE_FRAME_THUMBNAIL_SIZE_X "BOKEH_THUMBNAIL_X"
#define BOKEH_PIPELINE_FRAME_THUMBNAIL_SIZE_Y "BOKEH_THUMBNAIL_Y"
#define VSDOF_FEAME_STOP_MODE "STOP_MODE"
typedef enum BokehEffectRequestBufferType
{
    BOKEH_ER_BUF_NONE = 0,
    // The tag of Bokeh input buffer.
    BOKEH_ER_BUF_MYS,
    BOKEH_ER_BUF_DMW,
    BOKEH_ER_BUF_MAIN1,
    BOKEH_ER_BUF_DMG,
    BOKEH_ER_BUF_DMBG, //5
    BOKEH_ER_BUF_3DNR_INPUT,
    BOKEH_ER_BUG_TUNING_BUFFER,
    // The tag of Bokeh output buffer.
    BOKEH_ER_BUF_3DNR_OUTPUT,
    BOKEH_ER_BUF_VSDOF_IMG,
    BOKEH_ER_BUF_CLEAN_IMG,
    BOKEH_ER_BUF_RECORD,
    BOKEH_ER_BUF_DISPLAY,
    BOKEH_ER_BUF_THUMBNAIL,
    BOKEH_ER_BUF_WDMAIMG,
}BokehEffectRequestBufferType;
//
typedef enum BokehPipeRunPath
{
    GENERAL,
    ADVANCE,
    GF,
    P2B,
    MDP,
}BokehPipeRunPath;
//
typedef enum VSDOF_STOP_MODE
{
    SYNC,
    FLUSH,
}VSDOF_STOP_MODE;
#endif //_MTK_CAMERA_INCLUDE_VSDOF_DATA_ID_H