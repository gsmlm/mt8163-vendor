# Copyright Statement:
#
# This software/firmware and related documentation ("MediaTek Software") are
# protected under relevant copyright laws. The information contained herein
# is confidential and proprietary to MediaTek Inc. and/or its licensors.
# Without the prior written permission of MediaTek inc. and/or its licensors,
# any reproduction, modification, use or disclosure of MediaTek Software,
# and information contained herein, in whole or in part, shall be strictly prohibited.

# MediaTek Inc. (C) 2010. All rights reserved.
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

$(warning "the value of PLATFORM_SDK_VERSION is $(PLATFORM_SDK_VERSION), $(sort 21 $(PLATFORM_SDK_VERSION)), $(word 1, $(sort 21 $(PLATFORM_SDK_VERSION)))")



#ifneq ($(strip $(MTK_EMULATOR_SUPPORT)),yes)
LOCAL_PATH := $(call my-dir)

################################################################################
#
################################################################################
include $(CLEAR_VARS)
-include $(TOP)/$(MTK_PATH_SOURCE)/hardware/mtkcam/mtkcam.mk
-include $(TOP)/$(MTK_PATH_SOURCE)/hardware/mtkcam/feature/effectHal.mk

LOCAL_SRC_FILES += $(call all-c-cpp-files-under, .)




#sinclude $(TOP)/$(MTK_PATH_SOURCE)/frameworks/av/services/mmsdk/libmmsdkservice/mmsdk.mk
#-----------------------------------------------------------
LOCAL_C_INCLUDES += $(MTKCAM_C_INCLUDES)
##LOCAL_C_INCLUDES += $(MY_ADAPTER_C_INCLUDES)
LOCAL_C_INCLUDES += $(TOP)/$(MTKCAM_C_INCLUDES)
LOCAL_C_INCLUDES += $(TOP)/$(MTK_MTKCAM_PLATFORM)/include

# EffectHal Framework include
LOCAL_C_INCLUDES += $(EFFECTHAL_C_INCLUDE)


#
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/external/aee/binary/inc
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/frameworks/av/include
#
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_COMMON)/hal/inc
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_CUSTOM_PLATFORM)/hal/inc
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_CUSTOM)/hal/inc
#
LOCAL_C_INCLUDES += $(TOP)/$(MTKCAM_C_INCLUDES)/mtkcam/v1/camutils
LOCAL_C_INCLUDES += $(TOP)/system/media/camera/include
#
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_CUSTOM)/hal/inc/camera_feature
LOCAL_C_INCLUDES += $(MTK_PATH_COMMON)/hal/inc/camera_feature

LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_CUSTOM)/kernel/imgsensor/inc
LOCAL_C_INCLUDES += $(MTK_PATH_COMMON)/kernel/imgsensor/inc

LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/hardware/gralloc_extra/include

LOCAL_C_INCLUDES += $(MTK_PATH_SOURCE)/hardware/mtkcam/legacy/include/mtkcam/utils

#-----------------------------------------------------------
LOCAL_CFLAGS += $(MTKCAM_CFLAGS)
LOCAL_CFLAGS += -DPLATFORM_SDK_VERSION=$(PLATFORM_SDK_VERSION)

#-----------------------------------------------------------
LOCAL_WHOLE_STATIC_LIBRARIES +=
#
LOCAL_STATIC_LIBRARIES +=
#
LOCAL_SHARED_LIBRARIES += liblog
LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libcutils
LOCAL_SHARED_LIBRARIES += libbinder
LOCAL_SHARED_LIBRARIES += libui
LOCAL_SHARED_LIBRARIES += libstdc++
LOCAL_SHARED_LIBRARIES += libdl

LOCAL_SHARED_LIBRARIES += libgui
LOCAL_SHARED_LIBRARIES +=  libcam_utils


#-----------------------------------------------------------
LOCAL_MODULE := libeffecthal.base
#-----------------------------------------------------------
#include $(BUILD_STATIC_LIBRARY)
include $(BUILD_SHARED_LIBRARY)

#endif
