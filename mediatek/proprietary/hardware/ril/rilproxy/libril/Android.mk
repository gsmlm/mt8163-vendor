# Copyright 2006 The Android Open Source Project

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    ril.cpp \
    ril_event.cpp\
    RilSocket.cpp \
    RilSapSocket.cpp \

LOCAL_SHARED_LIBRARIES := \
    liblog \
    libutils \
    libbinder \
    libcutils \
    libhardware_legacy \
    librilproxyutils \

LOCAL_STATIC_LIBRARIES := \
    libprotobuf-c-nano-enable_malloc \

#LOCAL_CFLAGS := -DANDROID_MULTI_SIM -DDSDA_RILD1
LOCAL_CFLAGS := -DANDROID_MULTI_SIM

ifeq ($(SIM_COUNT), 2)
    LOCAL_CFLAGS += -DANDROID_SIM_COUNT_2
endif

LOCAL_C_INCLUDES += $(TARGET_OUT_HEADER)/librilproxyutils
LOCAL_C_INCLUDES += external/nanopb-c
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../include

LOCAL_MODULE:= librilproxy

LOCAL_COPY_HEADERS_TO := librilproxy
LOCAL_COPY_HEADERS := ril_ex.h

include $(BUILD_SHARED_LIBRARY)


# For RdoServD which needs a static library
# =========================================
ifneq ($(ANDROID_BIONIC_TRANSITION),)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    ril.cpp

LOCAL_STATIC_LIBRARIES := \
    libutils_static \
    libcutils \
    librilutils_static \
    libprotobuf-c-nano-enable_malloc

LOCAL_CFLAGS :=

LOCAL_MODULE:= librilproxy_static

include $(BUILD_STATIC_LIBRARY)
endif # ANDROID_BIONIC_TRANSITION
