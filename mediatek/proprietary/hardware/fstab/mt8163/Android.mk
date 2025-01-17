LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
FSTAB_OUT := $(PRODUCT_OUT)/obj/FAKE
LOCAL_PREBUILT_MODULE_FILE := $(FSTAB_OUT)/fstab.mt8163

LOCAL_MODULE := fstab.mt8163
LOCAL_SRC_FILES := fstab.mt8163
LOCAL_MODULE_CLASS := FAKE
LOCAL_MODULE_PATH := $(TARGET_ROOT_OUT)

ifeq ($(strip $(MTK_NAND_MTK_FTL_SUPPORT)),yes)
__CFLAGS += -D__MTK_FTL_SUPPORT
endif
ifeq ($(strip $(MTK_PERSIST_PARTITION_SUPPORT)),yes)
__CFLAGS += -D__PERSIST_PARTITION_SUPPORT
endif
ifeq ($(strip $(MTK_CIP_SUPPORT)),yes)
__CFLAGS += -D__CIP_SUPPORT
endif
ifeq ($(strip $(MTK_ICUSB_SUPPORT)),yes)
__CFLAGS += -D__ICUSB_SUPPORT
endif
ifeq ($(strip $(MTK_MULTI_PARTITION_MOUNT_ONLY_SUPPORT)),yes)
__CFLAGS += -D__MULTI_PARTITION_MOUNT_ONLY_SUPPORT
endif
ifeq ($(strip $(MTK_EMMC_SUPPORT)),yes)
__CFLAGS += -D__MTK_EMMC_SUPPORT
endif
ifeq ($(strip $(MTK_ATF_SUPPORT)),yes)
__CFLAGS += -D__MTK_ATF_SUPPORT
endif
ifeq ($(strip $(MTK_TEE_SUPPORT)),yes)
__CFLAGS += -D__MTK_TEE_SUPPORT
endif
ifneq ($(strip $(BOARD_SYSTEMIMAGE_FILE_SYSTEM_TYPE)),)
__CFLAGS += -D__MTK_SYSIMG_FSTYPE=$(BOARD_SYSTEMIMAGE_FILE_SYSTEM_TYPE)
endif

ifeq ($(strip $(MTK_FDE_NO_FORCE)),yes)
  __CFLAGS += -D__MTK_FDE_NO_FORCE
else ifeq ($(strip $(CUSTOM_CONFIG_MAX_DRAM_SIZE)),0x20000000)
  __CFLAGS += -D__MTK_FDE_NO_FORCE
endif
ifeq ($(strip $(MTK_FDE_TYPE_FILE)),yes)
  __CFLAGS += -D__MTK_FDE_TYPE_FILE
endif
ifeq (true,$(PRODUCTS.$(INTERNAL_PRODUCT).PRODUCT_SUPPORTS_VERITY))
__CFLAGS += -D__MTK_SEC_VERITY
endif

$(LOCAL_PREBUILT_MODULE_FILE): $(LOCAL_PATH)/fstab.in $(MTK_TARGET_PROJECT_FOLDER)/ProjectConfig.mk
	echo "Generate fstab"
	echo "MTK_PERSIST_PARTITION_SUPPORT $(MTK_PERSIST_PARTITION_SUPPORT)"
	echo "MTK_CIP_SUPPORT $(MTK_CIP_SUPPORT)"
	echo "MTK_ICUSB_SUPPORT $(MTK_ICUSB_SUPPORT)"
	echo "MTK_MULTI_PARTITION_MOUNT_ONLY_SUPPORT $(MTK_MULTI_PARTITION_MOUNT_ONLY_SUPPORT)"
	echo "MTK_ATF_SUPPORT $(MTK_ATF_SUPPORT)"
	echo "MTK_TEE_SUPPORT $(MTK_TEE_SUPPORT)"
	echo "BOARD_SYSTEMIMAGE_FILE_SYSTEM_TYPE $(BOARD_SYSTEMIMAGE_FILE_SYSTEM_TYPE)"
	@echo "MTK_FDE_NO_FORCE $(MTK_FDE_NO_FORCE)"
	@echo "MTK_FDE_TYPE_FILE $(MTK_FDE_TYPE_FILE)"
	@echo "CUSTOM_CONFIG_MAX_DRAM_SIZE $(CUSTOM_CONFIG_MAX_DRAM_SIZE)"
	@echo "PRODUCT_SUPPORTS_VERITY $(PRODUCTS.$(INTERNAL_PRODUCT).PRODUCT_SUPPORTS_VERITY)"
	mkdir -p $(FSTAB_OUT)
	gcc $(__CFLAGS) -x c -E $< -o $@

include $(BUILD_PREBUILT)


