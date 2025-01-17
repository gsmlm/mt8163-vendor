#
# libcamdrv_imgsensor
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

sinclude $(TOP)/$(MTK_PATH_SOURCE)/hardware/mtkcam/mtkcam.mk
sinclude $(TOP)/$(MTK_MTKCAM_PLATFORM)/mtkcam.mk

#temp mark
LOCAL_SRC_FILES := \
#  nvram_buf_mgr.cpp \
#  nvbuf_util.cpp \
#  nvram_drv.cpp \
#  oem_cam_drv.cpp \





#
LOCAL_C_INCLUDES := \
    $(TOP)/$(MTK_MTKCAM_PLATFORM)/hardware/mtkcam/core/ \
    $(TOP)/$(MTK_MTKCAM_PLATFORM)/hardware/mtkcam/inc \
    $(TOP)/$(MTK_MTKCAM_PLATFORM)/hardware/mtkcam/inc/drv \
    $(TOP)/$(MTK_MTKCAM_PLATFORM)/hardware/mtkcam/inc/imageio \
    $(TOP)/$(MTK_MTKCAM_PLATFORM)/hardware/mtkcam/core/drv/inc \
    $(TOP)/$(MTK_MTKCAM_PLATFORM)/hardware/mtkcam/core/drv/imgsensor \
    $(TOP)/$(MTK_MTKCAM_PLATFORM)/kernel/core/include/mach \
    $(TOP)/$(MTK_MTKCAM_PLATFORM)/external/ldvt/include \
    $(TOP)/$(MTK_PATH_CUSTOM_PLATFORM)/kernel/sensor/inc \
    $(TOP)/$(MTK_PATH_CUSTOM_PLATFORM)/hal/inc \
    $(TOP)/$(MTK_PATH_CUSTOM_PLATFORM)/hal/inc/camera_feature \
    $(TOP)/$(MTK_PATH_CUSTOM_PLATFORM)/hal/inc/isp_tuning \
    $(TOP)/$(MTK_PATH_CUSTOM_PLATFORM)/hal/inc/aaa \
    $(TOP)/$(MTK_PATH_CUSTOM_PLATFORM)/hal/inc/debug_exif/cam \
    $(TOP)/$(MTK_PATH_CUSTOM_PLATFORM)/cgen/cfgfileinc \
    $(TOP)/$(MTK_MTKCAM_PLATFORM)/hardware/mtkcam/inc/common/camutils \
    $(TOP)/bionic/libc/kernel/arch-arm/asm/arch \
    $(TOP)/mediatek/hardware/bwc/inc \
    $(TOP)/mediatek/hardware/mtkcam/inc/drv \
    $(TOP)/bionic/libc/kernel/common/linux/mt6582 \
    $(TOP)/device/mediatek/sprout/kernel-headers
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/hardware/mtkcam/inc
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/hardware/mtkcam/inc/common
LOCAL_C_INCLUDES += $(TOP)/$(MTK_PATH_SOURCE)/hardware/mtkcam/inc/common/camexif

#
#LOCAL_SHARED_LIBRARIES := \
#    libcutils \

ifneq ($(CUSTOM_KERNEL_MAIN2_IMGSENSOR),)
    LOCAL_CFLAGS += -DMTK_MAIN2_IMGSENSOR
endif

ifneq ($(CUSTOM_KERNEL_SUB_IMGSENSOR),)
    LOCAL_CFLAGS += -DMTK_SUB_IMGSENSOR
endif


#
#LOCAL_STATIC_LIBRARIES := \



LOCAL_C_INCLUDES += \
    $(TOP)/$(MTK_PATH_SOURCE)/external/matv_cust  \
    $(TOP)/$(MTK_PATH_SOURCE)/frameworks-ext/av/include/media \
    $(TOP)/$(MTK_PATH_SOURCE)/frameworks-ext/av/include \
    $(TOP)/$(MTK_PATH_SOURCE)/frameworks/av/media/libs \
    $(TOP)/frameworks/base/include/media \
    $(TOP)/frameworks/base/include/utils \
    $(TOP)/frameworks/base/include

LOCAL_C_INCLUDES += \
  $(MTK_PATH_COMMON)/kernel/imgsensor/inc \
  $(MTK_PATH_SOURCE)/external/nvram/libnvram \
  $(MTK_PATH_CUSTOM_PLATFORM)/hal/inc/aaa \
  $(MTK_PATH_CUSTOM_PLATFORM)/hal/inc \
  $(MTK_PATH_CUSTOM_PLATFORM)/hal/camera \
  $(MTK_PATH_CUSTOM_PLATFORM)/kernel/flashlight/inc \
  $(MTK_PATH_CUSTOM_PLATFORM)/kernel/lens/inc \
  $(TOP)/$(MTK_MTKCAM_PLATFORM)/hardware/mtkcam/core/featureio/drv/inc \
    $(TOP)/$(MTK_MTKCAM_PLATFORM)/hardware/mtkcam/core/drv/imem \
  $(TOP)/$(MTK_MTKCAM_PLATFORM)/hardware/mtkcam/inc/common \
    $(TOP)/mediatek/hardware/mtkcam/inc/drv\
  $(TOP)/$(MTK_MTKCAM_PLATFORM)/hardware/mtkcam/inc/drv \
  $(TOP)/$(MTK_MTKCAM_PLATFORM)/hardware/mtkcam/inc/featureio \
  $(TOP)/$(MTK_MTKCAM_PLATFORM)/external/ldvt/include \
  $(TOP)/$(MTK_PATH_SOURCE)/hardware/m4u/$(PLATFORM) \
  $(TOP)/$(MTK_MTKCAM_PLATFORM)/hardware/mtkcam/inc/common/camutils \
  $(TOP)/$(MTK_MTKCAM_PLATFORM)/include/mtkcam/featureio \
  $(TOP)/$(MTK_PATH_CUSTOM_PLATFORM)/cgen/inc \
  $(TOP)/$(MTK_PATH_CUSTOM_PLATFORM)/cgen/cfgfileinc


ifneq ($(BUILD_MTK_LDVT),yes)
ifeq ($(HAVE_AEE_FEATURE),yes)
LOCAL_SHARED_LIBRARIES += libaed
LOCAL_C_INCLUDES += $(MTK_ROOT)/external/aee/binary/inc
LOCAL_CFLAGS += -DHAVE_AEE_FEATURE
endif
endif

LOCAL_CFLAGS+= -DATVCHIP_MTK_ENABLE


#
#LOCAL_WHOLE_STATIC_LIBRARIES +=

#
LOCAL_MODULE := libcamdrv_nvram

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

LOCAL_C_INCLUDES += $(TOP)/$(MTK_MTKCAM_PLATFORM)/include

# End of common part ---------------------------------------
#
include $(BUILD_STATIC_LIBRARY)



#
#include $(call all-makefiles-under, $(LOCAL_PATH))
