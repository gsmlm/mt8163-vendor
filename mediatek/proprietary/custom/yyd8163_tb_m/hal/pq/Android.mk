LOCAL_PATH:= $(call my-dir)
ifneq ($(MTK_BASIC_PACKAGE), yes)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    cust_pq_main.cpp \
    cust_tdshp.cpp \
    cust_pqds.cpp \
    cust_pqdc.cpp \
    cust_color.cpp \
    ../gamma/cust_gamma.cpp

LOCAL_SHARED_LIBRARIES := \
    libcutils \
    libdpframework \

LC_MTK_PLATFORM := $(shell echo $(MTK_PLATFORM) | tr A-Z a-z )

LOCAL_C_INCLUDES += \
    $(TOP)/$(MTK_PATH_SOURCE)/hardware/pq/mt8163 \
    $(TOP)/$(MTK_PATH_SOURCE)/platform/$(LC_MTK_PLATFORM)/kernel/drivers/dispsys \


LOCAL_MODULE:= libpq_cust
LOCAL_MULTILIB := both

include $(BUILD_SHARED_LIBRARY)
endif
