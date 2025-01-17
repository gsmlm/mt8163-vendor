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
ifneq ($(BUILD_MTK_LDVT), yes)

################################################################################
#
################################################################################
LOCAL_PATH := $(call my-dir)

################################################################################
#
################################################################################
include $(CLEAR_VARS)

#-----------------------------------------------------------
sinclude $(MTK_PATH_SOURCE)/hardware/mtkcam/mtkcam.mk

#-----------------------------------------------------------
LOCAL_SRC_FILES += LegacyPipelineBuilder.cpp
LOCAL_SRC_FILES += PipelineBuilderBase.cpp
LOCAL_SRC_FILES += PipelineBuilderPreview.cpp
LOCAL_SRC_FILES += PipelineBuilderCapture.cpp
LOCAL_SRC_FILES += LegacyPipelinePreview.cpp
LOCAL_SRC_FILES += LegacyPipelineCapture.cpp
LOCAL_SRC_FILES += ResourceContainer.cpp
#
LOCAL_SRC_FILES += request/RequestControllerImp.cpp
LOCAL_SRC_FILES += request/RequestControllerImp.request.cpp
LOCAL_SRC_FILES += request/RequestSettingBuilder.cpp
#
LOCAL_SRC_FILES += processor/StreamingProcessor.cpp
LOCAL_SRC_FILES += processor/ResultProcessor.cpp
LOCAL_SRC_FILES += processor/TimestampProcessor.cpp
#
LOCAL_SRC_FILES += buffer/StreamBufferProviderFactory.cpp
LOCAL_SRC_FILES += buffer/StreamBufferProviderImp.provider.cpp
LOCAL_SRC_FILES += buffer/PairMetadataImp.cpp
LOCAL_SRC_FILES += buffer/BufferPoolImp.cpp
LOCAL_SRC_FILES += buffer/VirtualBufferPool.cpp
LOCAL_SRC_FILES += buffer/Selector.cpp
LOCAL_SRC_FILES += buffer/NormalCShotSelector.cpp
#
LOCAL_SRC_FILES += LegacyPipelineUtils.cpp
#
LOCAL_SRC_FILES += mfc/LegacyPipelineMFC.cpp
LOCAL_SRC_FILES += mfc/PipelineBuilderMFC.cpp
LOCAL_SRC_FILES += mfc/buffer/Selector.cpp
#
ifneq ($(MTK_BASIC_PACKAGE), yes)
LOCAL_SRC_FILES += PipelineBuilderFeaturePreview.cpp
LOCAL_SRC_FILES += PipelineBuilderFeatureCapture.cpp
endif
#-----------------------------------------------------------
LOCAL_C_INCLUDES += $(MTKCAM_C_INCLUDES)
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/hardware
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/hardware/include
LOCAL_C_INCLUDES += $(MTK_PATH_SOURCE)/hardware/gralloc_extra/include
LOCAL_C_INCLUDES += $(MTK_PATH_SOURCE)/hardware/mtkcam/
LOCAL_C_INCLUDES += $(MTK_PATH_SOURCE)/hardware/mtkcam/ext/include
LOCAL_C_INCLUDES += $(MTK_PATH_SOURCE)/hardware/mtkcam/common/include
LOCAL_C_INCLUDES += $(MTK_PATH_SOURCE)/hardware/mtkcam/utils/include
LOCAL_C_INCLUDES += $(MTK_PATH_SOURCE)/hardware/mtkcam/middleware/common/include
LOCAL_C_INCLUDES += $(MTK_PATH_SOURCE)/hardware/mtkcam/middleware/common/include/v1
LOCAL_C_INCLUDES += $(MTKCAM_HAL_INCLUDE)/metadata
LOCAL_C_INCLUDES += $(MTKCAM_3A_INCLUDE)
LOCAL_C_INCLUDES += $(MTK_PATH_CUSTOM_PLATFORM)/hal/inc/isp_tuning
LOCAL_C_INCLUDES += $(MTK_PATH_SOURCE)/custom/common/hal/inc

#[workaround] for local partial build
LOCAL_C_INCLUDES += $(MTK_PATH_SOURCE)/hardware/mtkcam/middleware/v1.4/include

#for camera metadata
LOCAL_C_INCLUDES += $(TOP)/system/media/camera/include
# STL SUPPORT
LOCAL_C_INCLUDES += $(TOP)/bionic
LOCAL_C_INCLUDES += $(TOP)/external/stlport/stlport
#
#-----------------------------------------------------------
LOCAL_CFLAGS += $(MTKCAM_CFLAGS)
#-----------------------------------------------------------
# define MTKCAM_HAVE_MFB_SUPPORT if necessary
ifneq ($(strip $(MTK_CAM_MFB_SUPPORT)),0)
    LOCAL_CFLAGS += -DMTKCAM_HAVE_MFB_SUPPORT=1
endif
#-----------------------------------------------------------
LOCAL_STATIC_LIBRARIES +=
#
LOCAL_WHOLE_STATIC_LIBRARIES +=
#-----------------------------------------------------------
#
LOCAL_SHARED_LIBRARIES += libutils
LOCAL_SHARED_LIBRARIES += libcutils
#LOCAL_SHARED_LIBRARIES += libstlport
#
LOCAL_SHARED_LIBRARIES += libcam.client
LOCAL_SHARED_LIBRARIES += libcam_utils
LOCAL_SHARED_LIBRARIES += libcam3_pipeline
LOCAL_SHARED_LIBRARIES += libcam3_utils
LOCAL_SHARED_LIBRARIES += libcam3_hwnode
LOCAL_SHARED_LIBRARIES += libcam.halsensor
#
LOCAL_SHARED_LIBRARIES += libcam.metadata
LOCAL_SHARED_LIBRARIES += libcam.metadataprovider
#
LOCAL_SHARED_LIBRARIES += libcamera_client
LOCAL_SHARED_LIBRARIES += libcam.paramsmgr
# stereo
ifeq ($(MTK_CAM_STEREO_CAMERA_SUPPORT), yes)
$(info including libcam.legacypipeline.stereo)
LOCAL_WHOLE_STATIC_LIBRARIES += libcam.legacypipeline.stereo
LOCAL_SHARED_LIBRARIES += libfeature.vsdof.hal
LOCAL_SHARED_LIBRARIES += libcam3_contextbuilder
endif
#
LOCAL_SHARED_LIBRARIES += libcameracustom
#-----------------------------------------------------------
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := libcam.legacypipeline
#-----------------------------------------------------------
include $(BUILD_SHARED_LIBRARY)

################################################################################
#
################################################################################
include $(CLEAR_VARS)
include $(call all-makefiles-under,$(LOCAL_PATH))

################################################################################
#
################################################################################
else
$(info skip build LegacyPipeline under ldvt environment)
endif

