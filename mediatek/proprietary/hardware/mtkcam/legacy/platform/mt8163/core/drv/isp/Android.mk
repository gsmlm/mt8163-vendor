#
# libcamdrv_isp
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

sinclude $(TOP)/$(MTK_PATH_SOURCE)/hardware/mtkcam/mtkcam.mk
sinclude $(TOP)/$(MTK_MTKCAM_PLATFORM)/mtkcam.mk

#
LOCAL_SRC_FILES := isp_drv.cpp

# camutils: For CameraProfile APIs.
#
LOCAL_C_INCLUDES := \
    $(TOP)/$(MTK_MTKCAM_PLATFORM)/hardware/mtkcam/inc \
    $(TOP)/$(MTK_MTKCAM_PLATFORM)/hardware/mtkcam/inc/drv \
    $(TOP)/$(MTK_MTKCAM_PLATFORM)/core/ \
    $(TOP)/$(MTK_MTKCAM_PLATFORM)/core/drv_common/inc \
    $(TOP)/$(MTK_MTKCAM_PLATFORM)/external/ldvt/include \
    $(TOP)/$(MTK_MTKCAM_PLATFORM)/kernel/core/include/mach \
    $(TOP)/$(MTK_PATH_CUSTOM_PLATFORM)/hal/inc/isp_tuning \
    $(TOP)/mediatek/source/external/mhal/src/core/drv/inc \
    $(MTK_MTKCAM_PLATFORM)hardware/m4u \
    $(TOP)/$(MTK_MTKCAM_PLATFORM)/hardware/mtkcam/inc/common/camutils \
    $(TOP)/bionic/libc/kernel/common/linux/mt6582

# Add a define value that can be used in the code to indicate that it's using LDVT now.
# For print message function when using LDVT.
# Note: It will be cleared by "CLEAR_VARS", so if this line needed in other module, it
# have to be set in other module again.
ifeq ($(BUILD_MTK_LDVT),yes)
    LOCAL_CFLAGS += -DUSING_MTK_LDVT
endif

#
LOCAL_STATIC_LIBRARIES := \

#
LOCAL_WHOLE_STATIC_LIBRARIES := \

#
#LOCAL_SHARED_LIBRARIES := \
#    libcutils \

#
LOCAL_MODULE := libcamdrv_isp

#
LOCAL_PRELINK_MODULE := false

#
LOCAL_MODULE_TAGS := optional

#-----------------------------------------------------------
LOCAL_CFLAGS += $(MTKCAM_CFLAGS)

#-----------------------------------------------------------
LOCAL_C_INCLUDES += $(MTKCAM_C_INCLUDES)
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/hardware/gralloc_extra/include
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/hardware/mtkcam/ext/include


#-----------------------------------------------------------
LOCAL_C_INCLUDES +=$(TOP)/$(MTK_MTKCAM_PLATFORM)/include
LOCAL_C_INCLUDES +=$(TOP)/$(MTKCAM_C_INCLUDES)
LOCAL_C_INCLUDES +=$(TOP)/$(MTKCAM_C_INCLUDES)/..

LOCAL_C_INCLUDES += $(TOP)/$(MTK_MTKCAM_PLATFORM)/include/

# End of common part ---------------------------------------
#
include $(BUILD_STATIC_LIBRARY)


