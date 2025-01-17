# Copyright Statement:
#
# This software/firmware and related documentation ("MediaTek Software") are
# protected under relevant copyright laws. The information contained herein
# is confidential and proprietary to MediaTek Inc. and/or its licensors.
# Without the prior written permission of MediaTek inc. and/or its licensors,
# any reproduction, modification, use or disclosure of MediaTek Software,
# and information contained herein, in whole or in part, shall be strictly prohibited.

# MediaTek Inc. (C) 2015. All rights reserved.
#
# BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
# THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
# RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
# AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
# NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
# SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
# SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
# THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
# THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
# CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
# SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
# STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
# CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
# AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
# OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
# MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
#
# The following software/firmware and/or related documentation ("MediaTek Software")
# have been modified by MediaTek Inc. All revisions are subject to any receiver's
# applicable license agreements with MediaTek Inc.

################################################################################
#
################################################################################
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
-include $(TOP)/$(MTK_PATH_SOURCE)/hardware/mtkcam/mtkcam.mk
-include $(TOP)/$(MTK_PATH_SOURCE)/hardware/mtkcam/feature/effectHal.mk
################################################################################
#
################################################################################
ifneq ($(IS_LEGACY), yes)
ifneq ($(MTK_BASIC_PACKAGE), yes)
LOCAL_SRC_FILES += BokehPipeNode.cpp
LOCAL_SRC_FILES += BokehPipeImp.cpp
LOCAL_SRC_FILES += IBokehPipe.cpp
LOCAL_SRC_FILES += GuidedFilterNode.cpp
LOCAL_SRC_FILES += VSDOF_P2BNode.cpp
LOCAL_SRC_FILES += MDPNode.cpp
LOCAL_SRC_FILES += DebugNode.cpp
endif
endif
################################################################################
#
################################################################################
LOCAL_C_INCLUDES += $(call include-path-for, camera)
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/hardware
# for graphics_mtk_defs.h
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/hardware/gralloc_extra/include
################################################################################
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/hardware/mtkcam/feature/core/featurePipe
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/hardware/mtkcam/feature/core/featurePipe/core/include
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/hardware/mtkcam/feature/core
# mtkcam folder
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/hardware/mtkcam
# ispio_sw_scenario
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/hardware/mtkcam/include/$(PLATFORM)
# camera common folder
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/hardware/mtkcam/common/include/
#
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/hardware/mtkcam/feature/include
################################################################################
# for effectHal
# EffectHal and BasicParameter
LOCAL_C_INCLUDES += $(EFFECTHAL_C_INCLUDE)
################################################################################
#
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/hardware/dpframework/include
################################################################################
# INormalStream
################################################################################
LOCAL_C_INCLUDES += $(TOP)/$(MTKCAM_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(TOP)/$(MTKCAM_DRV_INCLUDE)/imageio
LOCAL_C_INCLUDES += $(TOP)/$(MTKCAM_DRV_INCLUDE)/iopipe
LOCAL_C_INCLUDES += $(TOP)/$(MTKCAM_DRV_INCLUDE)/drv
################################################################################
LOCAL_WHOLE_STATIC_LIBRARIES += libmtkcam.featurepipe.core
LOCAL_SHARED_LIBRARIES += liblog
LOCAL_SHARED_LIBRARIES += libui
LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libcutils
LOCAL_SHARED_LIBRARIES += libcam.halsensor
LOCAL_SHARED_LIBRARIES += libcam.iopipe
LOCAL_SHARED_LIBRARIES += libcam_utils
LOCAL_SHARED_LIBRARIES += libeffecthal.base
LOCAL_SHARED_LIBRARIES += libgralloc_extra
#LOCAL_SHARED_LIBRARIES += libcam.hal3a.v3
LOCAL_SHARED_LIBRARIES += libcam.metadata
# for ion
LOCAL_SHARED_LIBRARIES += libion
LOCAL_SHARED_LIBRARIES += libion_mtk
# for 3dnr
# Algo hal
LOCAL_SHARED_LIBRARIES += libfeature.vsdof.hal
# DpBlitStream
LOCAL_SHARED_LIBRARIES += libdpframework
LOCAL_SHARED_LIBRARIES += libmtkcam.featurepipe.vsdof_util
################################################################################
LOCAL_STATIC_LIBRARIES += libmtkcam.featurepipe.core
LOCAL_STATIC_LIBRARIES += libcameracustom.camera
LOCAL_WHOLE_STATIC_LIBRARIES += libfeatureiopipe_3dnr_common
LOCAL_MODULE := libmtkcam.featurepipe.bokeh
include $(BUILD_SHARED_LIBRARY)
################################################################################
#
################################################################################
