# Copyright 2006 The Android Open Source Project

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	rild.c


LOCAL_SHARED_LIBRARIES := \
	liblog \
	libcutils \
	librilproxy \
	libdl

# temporary hack for broken vendor rils
LOCAL_WHOLE_STATIC_LIBRARIES := \
	librilproxyutils_static

LOCAL_CFLAGS := -DRIL_SHLIB
#LOCAL_CFLAGS += -DANDROID_MULTI_SIM

ifeq ($(SIM_COUNT), 2)
    LOCAL_CFLAGS += -DANDROID_SIM_COUNT_2
endif

LOCAL_MODULE:= rilproxy
LOCAL_MODULE_TAGS := optional

LOCAL_C_INCLUDES += $(TARGET_OUT_HEADERS)/librilproxy

include $(BUILD_EXECUTABLE)

# For radiooptions binary
# =======================
include $(CLEAR_VARS)

#LOCAL_SRC_FILES:= \
#	radiooptions.c

#LOCAL_SHARED_LIBRARIES := \
#	liblog \
#	libcutils \

#LOCAL_CFLAGS := \

#LOCAL_MODULE:= radiooptions
#LOCAL_MODULE_TAGS := debug

#include $(BUILD_EXECUTABLE)
