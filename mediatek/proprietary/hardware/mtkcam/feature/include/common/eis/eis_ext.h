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

/**
* @file EIS_EXT.h
*
* EIS extension Header File
*/


#ifndef _EIS_EXT_H_
#define _EIS_EXT_H_
typedef enum
{
    EIS_MODE_OFF = 0,
    EIS_MODE_CALIBRATION,
    EIS_MODE_EIS_12,
    EIS_MODE_EIS_22,//GIS
} EIS_ADVMODE_ENUM;

/**
 *  Data type in MTK_EIS_REGION is all MINT32
 */
typedef enum
{
    EIS_REGION_INDEX_XINT = 0,
    EIS_REGION_INDEX_XFLOAT,
    EIS_REGION_INDEX_YINT,
    EIS_REGION_INDEX_YFLOAT,

    /**
     *  Resolution here is describing that the ROI of EIS, a central cropping
     *  should be applied follows this resolution.
     */
    EIS_REGION_INDEX_WIDTH, // width that valid by EIS
    EIS_REGION_INDEX_HEIGHT, // height that valid by EIS
    EIS_REGION_INDEX_MV2CENTERX,
    EIS_REGION_INDEX_MV2CENTERY,
    EIS_REGION_INDEX_ISFROMRZ,
    EIS_REGION_INDEX_GMVX,
    EIS_REGION_INDEX_GMVY,
    EIS_REGION_INDEX_CONFX,
    EIS_REGION_INDEX_CONFY,
    EIS_REGION_INDEX_EXPTIME,
    EIS_REGION_INDEX_HWTS, // highword timestamp (bit[32:63])
    EIS_REGION_INDEX_LWTS, // lowword timestamp  (bit[0:31])

    /* for indicating to size only */
    EIS_REGION_INDEX_SIZE,
} EIS_REGION_INDEX;


// EIS ratio
#define EIS_FACTOR 120

#define VR_1080P_W 1920
#define VR_1080P_H 1088

#define EIS_MODE_ENABLE_CALIBRATION(x)      (x)|=(1<<EIS_MODE_CALIBRATION)
#define EIS_MODE_IS_CALIBRATION_ENABLED(x)  ((x& (1<<EIS_MODE_CALIBRATION))?true:false)

#define EIS_MODE_ENABLE_EIS_12(x)           (x)|=(1<<EIS_MODE_EIS_12)
#define EIS_MODE_IS_EIS_12_ENABLED(x)       ((x& (1<<EIS_MODE_EIS_12))?true:false)

#define EIS_MODE_ENABLE_EIS_22(x)           (x)|=(1<<EIS_MODE_EIS_22)
#define EIS_MODE_IS_EIS_22_ENABLED(x)       ((x& (1<<EIS_MODE_EIS_22))?true:false)

#endif // _EIS_EXT_H_
