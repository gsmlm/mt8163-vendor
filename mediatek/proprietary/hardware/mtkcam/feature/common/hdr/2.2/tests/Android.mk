LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

ifeq ($(MTK_CAM_HDR_SUPPORT), yes)

ifeq ($(TARGET_BOARD_PLATFORM), $(filter $(TARGET_BOARD_PLATFORM), mt6797))

LOCAL_MODULE := test-hdrproc

LOCAL_MODULE_TAGS := tests

LOCAL_ADDITIONAL_DEPENDENCIES := $(LOCAL_PATH)/Android.mk

MTK_PATH_CAM := $(MTK_PATH_SOURCE)/hardware/mtkcam

# camera3test_fixtures.cpp add for start camera3 preview
LOCAL_SRC_FILES := \
	HDRProcTest.cpp \
	camera3test_fixtures.cpp \
	main.cpp

# libhardware,libcamera_metadata, libdl add for start camera3 preview
LOCAL_SHARED_LIBRARIES := \
	libutils \
	libcutils \
	libhdrproc \
	libdl \
	libhardware \
	libcamera_metadata

LOCAL_C_INCLUDES := \
	$(TOP)/system/media/camera/include \
	$(MTK_PATH_CAM)/common/include \
	$(MTK_PATH_CAM)/feature/include \
	$(MTK_PATH_SOURCE)/hardware/gralloc_extra/include \
	$(TOP)/$(MTK_PATH_CUSTOM_PLATFORM)/hal/inc

# build the binary to $(TARGET_OUT_DATA_NATIVE_TESTS)/$(LOCAL_MODULE)
# to integrate with auto-test framework
include $(BUILD_NATIVE_TEST)

endif # TARGET_BOARD_PLATFORM

endif # MTK_CAM_HDR_SUPPORT
