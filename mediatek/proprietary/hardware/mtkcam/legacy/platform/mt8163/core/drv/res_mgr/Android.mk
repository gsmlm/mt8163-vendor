#
# libcamdrv_res_mgr
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

sinclude $(TOP)/$(MTK_PATH_SOURCE)/hardware/mtkcam/mtkcam.mk
sinclude $(TOP)/$(MTK_MTKCAM_PLATFORM)/mtkcam.mk

#
LOCAL_SRC_FILES := \
    res_mgr_drv.cpp

#
LOCAL_C_INCLUDES += \
    $(TOP)/$(MTK_MTKCAM_PLATFORM)/hardware/mtkcam/inc/common \
    $(TOP)/$(MTK_MTKCAM_PLATFORM)/hardware/mtkcam/inc/drv \
    $(TOP)/$(MTK_MTKCAM_PLATFORM)/core/src/drv/inc \
    $(TOP)/$(MTK_MTKCAM_PLATFORM)/kernel/core/include/mach \
    $(TOP)/$(MTK_ROOT)/hardware/bwc/inc \
    $(TOP)/$(MTK_MTKCAM_PLATFORM)/kernel/drivers/hdmitx \
    $(TOP)/bionic/libc/kernel/common/linux/mt6582 \

# Add a define value that can be used in the code to indicate that it's using LDVT now.
# For print message function when using LDVT.
# Note: It will be cleared by "CLEAR_VARS", so if it is needed in other module, it
# has to be set in other module again.
ifeq ($(BUILD_MTK_LDVT),true)
    LOCAL_CFLAGS += -DUSING_MTK_LDVT
endif

#

#
LOCAL_MODULE := libcamdrv_res_mgr

#
#LOCAL_MULTILIB := 32

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



#
#include $(call all-makefiles-under, $(LOCAL_PATH))
