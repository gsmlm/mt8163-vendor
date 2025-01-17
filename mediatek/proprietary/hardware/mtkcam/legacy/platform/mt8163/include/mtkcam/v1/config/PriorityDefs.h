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

#ifndef _MTK_CAMERA_INC_CONFIG_PRIORITYDEFS_H_
#define _MTK_CAMERA_INC_CONFIG_PRIORITYDEFS_H_
/******************************************************************************
 *  Priority Definitions.
 ******************************************************************************/
#include <linux/rtpm_prio.h>


/******************************************************************************
 *  Real-Time Priority (SCHED_RR, SCHED_FIFO)
 ******************************************************************************/
enum
{
    //
    PRIO_RT_CAMERA_PREVIEW                  = (RTPM_PRIO_CAMERA_TOPBASE - 1),
    PRIO_RT_CAMERA_CAPTURE                  = (RTPM_PRIO_CAMERA_TOPBASE - 1),
    //
    PRIO_RT_CAMERA_SHUTTER_CB               = (RTPM_PRIO_CAMERA_TOPBASE - 1),
    PRIO_RT_CAMERA_ZIP_IMAGE_CB             = (RTPM_PRIO_CAMERA_TOPBASE - 1),
    //
    //  Clients
    PRIO_RT_CAMERA_RECORD_CLIENT            = (RTPM_PRIO_CAMERA_TOPBASE - 1),
    PRIO_RT_CAMERA_PREVIEW_CLIENT           = (RTPM_PRIO_CAMERA_TOPBASE - 1),
    PRIO_RT_CAMERA_DISPLAY_CLIENT           = (RTPM_PRIO_CAMERA_TOPBASE - 0),
    //
    //
    PRIO_RT_ISP_EVENT_THREAD                = (RTPM_PRIO_CAMERA_TOPBASE - 1),
    //
    PRIO_RT_AF_THREAD                       = (RTPM_PRIO_CAMERA_TOPBASE - 2),
    PRIO_RT_3A_THREAD                       = (RTPM_PRIO_CAMERA_TOPBASE - 2),
    PRIO_RT_F858_THREAD                     = (RTPM_PRIO_CAMERA_TOPBASE - 2),
    //
    PRIO_RT_VSS_THREAD                      = (RTPM_PRIO_CAMERA_TOPBASE - 2),
    //
    PRIO_RT_FD_THREAD                       = (RTPM_PRIO_CAMERA_TOPBASE - 3),
};
/******************************************************************************
 * Frame Based
 ******************************************************************************/
#include <utils/ThreadDefs.h> // for SCHED_OTHER
/******************************************************************************
 *  Real-Time Priority (SCHED_RR, SCHED_FIFO)
 ******************************************************************************/
enum
{
    PRIO_RT_ISPDEQUEUE_THREAD               = (RTPM_PRIO_CAMERA_TOPBASE - 1),
};


/******************************************************************************
 *  Nice value (SCHED_OTHER)
 ******************************************************************************/
enum
{
    //
    NICE_CAMERA_PASS1                = ANDROID_PRIORITY_FOREGROUND,
    NICE_CAMERA_PASS2                = ANDROID_PRIORITY_FOREGROUND,
    NICE_CAMERA_VSS_PASS2            = ANDROID_PRIORITY_NORMAL,
    NICE_CAMERA_SM_PASS2             = ANDROID_PRIORITY_NORMAL - 8,
    NICE_CAMERA_JPEG                 = ANDROID_PRIORITY_NORMAL,
    NICE_CAMERA_SHOTCB               = ANDROID_PRIORITY_NORMAL,
    //
    NICE_CAMERA_CAPTURE              = ANDROID_PRIORITY_NORMAL,
    //
    NICE_CAMERA_SHUTTER_CB           = ANDROID_PRIORITY_NORMAL,
    NICE_CAMERA_ZIP_IMAGE_CB         = ANDROID_PRIORITY_NORMAL,
    //
    //
    NICE_CAMERA_EIS                  = ANDROID_PRIORITY_NORMAL,
    NICE_CAMERA_VHDR                 = ANDROID_PRIORITY_NORMAL,
    //Lomo Jni for Matrix Menu of Effect
    NICE_CAMERA_LOMO                = ANDROID_PRIORITY_NORMAL-8,
    //
    //  3A-related
    NICE_CAMERA_3A_MAIN              = (ANDROID_PRIORITY_NORMAL - 4),
    NICE_CAMERA_AF                   = (ANDROID_PRIORITY_NORMAL - 3),
    NICE_CAMERA_TSF                  = (ANDROID_PRIORITY_NORMAL - 3),
};

/******************************************************************************
 *
 ******************************************************************************/
#endif  //_MTK_CAMERA_INC_CONFIG_PRIORITYDEFS_H_

