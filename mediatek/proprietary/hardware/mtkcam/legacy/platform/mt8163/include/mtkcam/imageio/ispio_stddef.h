/********************************************************************************************
 *     LEGAL DISCLAIMER
 *
 *     (Header of MediaTek Software/Firmware Release or Documentation)
 *
 *     BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 *     THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED
 *     FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS
 *     ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED,
 *     INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR
 *     A PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY
 *     WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 *     INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK
 *     ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *     NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION
 *     OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *
 *     BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE LIABILITY WITH
 *     RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION,
TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE
 *     FEES OR SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 *     THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH THE LAWS
 *     OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LAWS PRINCIPLES.
 ************************************************************************************************/

/**
* @file ispio_stddef.h
*
* ispio_stddef Header File
*/

#ifndef _ISPIO_STDDEF_H_
#define _ISPIO_STDDEF_H_

#include <mtkcam/common.h>
using namespace NSCam;

/**/
#include <mtkcam/ispio_sw_scenario.h>
#include <utils/Mutex.h>    // For android::Mutex.


namespace NSImageio
{
    namespace NSIspio
    {
        /**
             * @brief Pipe support command list
             */
        enum EPIPECmd {
            EPIPECmd_SET_SENSOR_DEV          = 0x1001,
            EPIPECmd_SET_SENSOR_GAIN         = 0x1002,
            EPIPECmd_SET_SENSOR_EXP          = 0x1003,
            EPIPECmd_SET_CAM_MODE            = 0x1004,
            EPIPECmd_SET_SCENE_MODE          = 0x1005,
            EPIPECmd_SET_ISO                 = 0x1006,
            EPIPECmd_SET_FLUORESCENT_CCT     = 0x1007,
            EPIPECmd_SET_SCENE_LIGHT_VALUE   = 0x1008,
            EPIPECmd_VALIDATE_FRAME          = 0x1009,
            EPIPECmd_SET_OPERATION_MODE      = 0x100A,
            EPIPECmd_SET_EFFECT              = 0x100B,
            EPIPECmd_SET_ZOOM_RATIO          = 0x100C,
            EPIPECmd_SET_BRIGHTNESS          = 0x100D,
            EPIPECmd_SET_CONTRAST            = 0x100E,
            EPIPECmd_SET_EDGE                = 0x100F,
            EPIPECmd_SET_HUE                 = 0x1010,
            EPIPECmd_SET_SATURATION          = 0x1011,
            EPIPECmd_SEND_TUNING_CMD         = 0x1012,
            EPIPECmd_DECIDE_OFFLINE_CAPTURE  = 0x1013,
            EPIPECmd_LOCK_REG                = 0x1014,
            EPIPECmd_SET_SHADING_IDX         = 0x1018,
            EPIPECmd_SET_ISP_CDRZ            = 0x1100,
            EPIPECmd_SET_ISP_IMGO            = 0x1101,
            EPIPECmd_SET_BASE_ADDR           = 0x1102,
            EPIPECmd_SET_CQ_CHANNEL          = 0x1103,
            EPIPECmd_SET_CQ_TRIGGER_MODE     = 0x1104,
            EPIPECmd_SET_CURRENT_BUFFER      = 0x1105,
            EPIPECmd_SET_NEXT_BUFFER         = 0x1106,
            EPIPECmd_SET_FMT_EN              = 0x1107,
            EPIPECmd_SET_GDMA_LINK_EN        = 0x1108,
            EPIPECmd_SET_FMT_START           = 0x1109,
            EPIPECmd_SET_CAM_CTL_DBG         = 0x110A,
            EPIPECmd_SET_IMG_PLANE_BY_IMGI   = 0x110B,
            EPIPECmd_SET_IMGO_RAW_TYPE       = 0x110C,
            EPIPECmd_SET_CONFIG_STAGE        = 0x1200,
            EPIPECmd_GET_SENSOR_PRV_RANGE    = 0x2001,
            EPIPECmd_GET_SENSOR_FULL_RANGE   = 0x2002,
            EPIPECmd_GET_RAW_DUMMY_RANGE     = 0x2003,
            EPIPECmd_GET_SENSOR_NUM          = 0x2004,
            EPIPECmd_GET_SENSOR_TYPE         = 0x2005,
            EPIPECmd_GET_RAW_INFO            = 0x2006,
            EPIPECmd_GET_EXIF_DEBUG_INFO     = 0x2007,
            EPIPECmd_GET_SHADING_IDX         = 0x2008,
            EPIPECmd_GET_ATV_DISP_DELAY      = 0x2009,
            EPIPECmd_GET_SENSOR_DELAY_FRAME_CNT = 0x200A,
            EPIPECmd_GET_CAM_CTL_DBG         = 0x200B,
            EPIPECmd_GET_FMT                 = 0x200C,
            EPIPECmd_GET_GDMA                = 0x200D,
            EPIPECmd_FREE_MAPPED_BUFFER      = 0x3001,
            EPIPECmd_ISP_RESET               = 0x4001,
            EPIPECmd_MAX                 = 0xFFFF
        };

        /**
             * @brief Interrupr event
             */
        enum EPipeIRQ {
            EPIPEIRQ_VSYNC      = 0,
            EPIPEIRQ_SOF,
            EPIPEIRQ_PATH_DONE
        };

        /**
             * @brief CQ
             */
        enum EPipeCQ {
            EPIPE_CQ_NONE = (-1),
            EPIPE_PASS2_CQ3 = 0,
            EPIPE_PASS1_CQ0,
        //    EPIPE_PASS1_CQ0 = 0,
            EPIPE_PASS1_CQ0B,
            EPIPE_PASS1_CQ0C,
            EPIPE_PASS2_CQ1,
            EPIPE_PASS2_CQ1_SYNC,
            EPIPE_PASS2_CQ2,
            EPIPE_PASS2_CQ2_SYNC,
        //    EPIPE_PASS2_CQ3
        };

        /**
             * @brief CQ trigger type
             */
        enum EPipeCQTriger {
            EPIPECQ_TRIGGER_SINGLE_IMMEDIATE = 0,
            EPIPECQ_TRIGGER_SINGLE_EVENT,
            EPIPECQ_TRIGGER_CONTINUOUS_EVENT
        };

        /**
             * @brief CQ trigger source
             */
        enum EPipeCQStart {
            EPIPECQ_TRIG_BY_START = 0,
            EPIPECQ_TRIG_BY_PASS1_DONE,
            EPIPECQ_TRIG_BY_PASS2_DONE,
            EPIPECQ_TRIG_BY_IMGO_DONE,
            EPIPECQ_TRIG_BY_IMG2O_DONE,
        };

        /**
             * @brief buffer source type
             */
        enum EBufType
        {
            eBufType_PMEM       = 0,  ///<  ISP_BUF_TYPE_PMEM,
            eBufType_STD_M4U,         ///<  ISP_BUF_TYPE_STD_M4U,
            eBufType_ION,             ///<  ISP_BUF_TYPE_ION,
        };

        /**
             * @brief free buffer mode.
             */
        enum EFreeBufMode {
            eFreeBufMode_SINGLE         = 0x0000,
            eFreeBufMode_ALL            = 0x0001,
        };

        /**
             * @brief Image Rotation
             */
        enum EImageRotation
        {
            eImgRot_0      = 0,
            eImgRot_90,         ///<  90 CW
            eImgRot_180,
            eImgRot_270
        };

        /**
             * @brief Image Flip
             */
        enum EImageFlip
        {
            eImgFlip_OFF     = 0,
            eImgFlip_ON      = 1,
        };

        /**
             * @brief raw image pixel ID
             */
        enum ERawPxlID
        {
            ERawPxlID_B   = 0,  ///<  B Gb Gr R
            ERawPxlID_Gb,       ///<  Gb B R Gr
            ERawPxlID_Gr,       ///<  Gr R B Gb
            ERawPxlID_R         ///<  R Gr Gb B
        };

        /**
             * @brief raw data memory footprint bit per pixel
             */
        enum ERAW_MEM_FP_BPP
        {
            ERAW8_MEM_FP_BPP   = 8,
            ERAW10_MEM_FP_BPP  = 10,
            ERAW12_MEM_FP_BPP  = 12,
        };

        /**
             * @brief STRIDE INFO INDEX
             */
        enum EIMAGE_STRIDE
        {
            ESTRIDE_1ST_PLANE   = 0,
            ESTRIDE_2ND_PLANE   = 1,
            ESTRIDE_3RD_PLANE   = 2
        };

        /**
             * @brief Config Setting Stage
             */
        enum EConfigSettingStage
        {
            eConfigSettingStage_Unknown         = 0x0000,   ///<  unknow
            eConfigSettingStage_Init            = 0x0001,   ///<  Init setting for Image IO path
            eConfigSettingStage_UpdateTrigger   = 0x0002,   ///<  Trigger ring tpipe or partial update
        };

        /**
             * @brief raw image Type setting
             */
        enum ERawImageType
        {
            eRawImageType_Pure                  = 0x0000,   ///<  Pure Raw
            eRawImageType_PreProc               = 0x0001,   ///<  Pre-processed Raw
        };

        /**
             * @brief Ring Tpipe Error Control
             */
        enum ETpipeMessage
        {
            TPIPE_MESSAGE_UNKNOWN = 0,
            TPIPE_MESSAGE_OK,
            TPIPE_MESSAGE_UNKNOWN_DRIVER_CONFIGURED_REG_MODE_ERROR,
            TPIPE_MESSAGE_DIFFERENT_TPIPE_CONFIG_NO_ERROR,
            TPIPE_MESSAGE_OVER_MAX_TPIPE_WORD_NO_ERROR,
            TPIPE_MESSAGE_OVER_MAX_TPIPE_TOT_NO_ERROR,
            TPIPE_MESSAGE_UNDER_MIN_TPIPE_FUNC_NO_ERROR,
            TPIPE_MESSAGE_OVER_MAX_TPIPE_FUNC_NO_ERROR,
            TPIPE_MESSAGE_NOT_FOUND_INIT_TPIPE_FUNC_ERROR,
            TPIPE_MESSAGE_NOT_FOUND_ENABLE_TPIPE_FUNC_ERROR,
            TPIPE_MESSAGE_NOT_FOUND_SUB_RDMA_TDR_FUNC_ERROR,
            TPIPE_MESSAGE_DUPLICATED_SUB_RDMA_FUNC_ERROR,
            TPIPE_MESSAGE_DUPLICATED_SUPPORT_FUNC_ERROR,
            TPIPE_MESSAGE_OVER_MAX_BRANCH_NO_ERROR,
            TPIPE_MESSAGE_OVER_MAX_INPUT_TPIPE_FUNC_NO_ERROR,
            TPIPE_MESSAGE_TPIPE_FUNC_CANNOT_FIND_LAST_FUNC_ERROR,
            TPIPE_MESSAGE_SCHEDULING_BACKWARD_ERROR,
            TPIPE_MESSAGE_SCHEDULING_FORWARD_ERROR,
            TPIPE_MESSAGE_FULL_SIZE_Y_IN_ERROR,
            TPIPE_MESSAGE_FULL_SIZE_X_IN_ERROR,
            TPIPE_MESSAGE_FULL_SIZE_Y_OUT_ERROR,
            TPIPE_MESSAGE_FULL_SIZE_X_OUT_ERROR,
            TPIPE_MESSAGE_IN_CONST_X_ERROR,
            TPIPE_MESSAGE_IN_CONST_Y_ERROR,
            TPIPE_MESSAGE_OUT_CONST_X_ERROR,
            TPIPE_MESSAGE_OUT_CONST_Y_ERROR,
            TPIPE_MESSAGE_NULL_BACK_COMP_TPIPE_LOSS_TYPE_ERROR,
            TPIPE_MESSAGE_NULL_FOR_COMP_TPIPE_LOSS_TYPE_ERROR,
            TPIPE_MESSAGE_NULL_INIT_PTR_FOR_START_FUNC_ERROR,
            TPIPE_MESSAGE_XS_NOT_DIV_BY_IN_CONST_X_ERROR,
            TPIPE_MESSAGE_XE_NOT_DIV_BY_IN_CONST_X_ERROR,
            TPIPE_MESSAGE_YS_NOT_DIV_BY_IN_CONST_Y_ERROR,
            TPIPE_MESSAGE_YE_NOT_DIV_BY_IN_CONST_Y_ERROR,
            TPIPE_MESSAGE_INIT_INCORRECT_X_INPUT_SIZE_POS_ERROR,
            TPIPE_MESSAGE_INIT_INCORRECT_Y_INPUT_SIZE_POS_ERROR,
            TPIPE_MESSAGE_INIT_INCORRECT_X_OUTPUT_SIZE_POS_ERROR,
            TPIPE_MESSAGE_INIT_INCORRECT_Y_OUTPUT_SIZE_POS_ERROR,
            TPIPE_MESSAGE_IN_XS_LESS_THAN_LAST_ERROR,
            TPIPE_MESSAGE_OUT_XS_LESS_THAN_LAST_ERROR,
            TPIPE_MESSAGE_IN_YS_LESS_THAN_LAST_ERROR,
            TPIPE_MESSAGE_OUT_YS_LESS_THAN_LAST_ERROR,
            TPIPE_MESSAGE_TPIPE_X_DIR_NOT_END_TOGETHER_ERROR,
            TPIPE_MESSAGE_TPIPE_Y_DIR_NOT_END_TOGETHER_ERROR,
            TPIPE_MESSAGE_INCORRECT_XE_INPUT_POS_REDUCED_BY_TPIPE_SIZE_ERROR,
            TPIPE_MESSAGE_INCORRECT_YE_INPUT_POS_REDUCED_BY_TPIPE_SIZE_ERROR,
            TPIPE_MESSAGE_FORWARD_FUNC_CAL_LOOP_COUNT_OVER_MAX_ERROR,
            TPIPE_MESSAGE_TPIPE_LOSS_OVER_TPIPE_HEIGHT_ERROR,
            TPIPE_MESSAGE_TPIPE_LOSS_OVER_TPIPE_WIDTH_ERROR,
            TPIPE_MESSAGE_TPIPE_HEIGHT_EQ_ONE_ERROR,
            TPIPE_MESSAGE_TPIPE_WIDTH_EQ_ONE_ERROR,
            TPIPE_MESSAGE_TPIPE_OUTPUT_HORIZONTAL_OVERLAP_ERROR,
            TPIPE_MESSAGE_TPIPE_OUTPUT_VERTICAL_OVERLAP_ERROR,
            TPIPE_MESSAGE_TP8_FOR_INVALID_OUT_XYS_XYE_ERROR,
            TPIPE_MESSAGE_TP4_FOR_INVALID_OUT_XYS_XYE_ERROR,
            TPIPE_MESSAGE_SRC_ACC_FOR_INVALID_OUT_XYS_XYE_ERROR,
            TPIPE_MESSAGE_CUB_TRI_FOR_INVALID_OUT_XYS_XYE_ERROR,
            TPIPE_MESSAGE_BACKWARD_START_LESS_THAN_FORWARD_ERROR,
            TPIPE_MESSAGE_BACKWARD_END_LESS_THAN_FORWARD_ERROR,
            TPIPE_MESSAGE_NOT_SUPPORT_RESIZER_MODE_ERROR,
            TPIPE_MESSAGE_RECURSIVE_FOUND_ERROR,
            TPIPE_MESSAGE_CHECK_IN_CONFIG_ALIGN_XS_POS_ERROR,
            TPIPE_MESSAGE_CHECK_IN_CONFIG_ALIGN_XE_POS_ERROR,
            TPIPE_MESSAGE_CHECK_IN_CONFIG_ALIGN_YS_POS_ERROR,
            TPIPE_MESSAGE_CHECK_IN_CONFIG_ALIGN_YE_POS_ERROR,
            TPIPE_MESSAGE_START_FUNC_XS_NOT_DIV_BY_IN_CONST_X_ERROR,
            TPIPE_MESSAGE_START_FUNC_YS_NOT_DIV_BY_IN_CONST_Y_ERROR,
            TPIPE_MESSAGE_END_FUNC_XE_NOT_DIV_BY_OUT_CONST_X_ERROR,
            TPIPE_MESSAGE_END_FUNC_YE_NOT_DIV_BY_OUT_CONST_Y_ERROR,
            TPIPE_MESSAGE_TPIPE_FORWARD_OUT_OVER_TPIPE_WIDTH_ERROR,
            TPIPE_MESSAGE_TPIPE_FORWARD_OUT_OVER_TPIPE_HEIGHT_ERROR,
            TPIPE_MESSAGE_TPIPE_BACKWARD_IN_OVER_TPIPE_WIDTH_ERROR,
            TPIPE_MESSAGE_TPIPE_BACKWARD_IN_OVER_TPIPE_HEIGHT_ERROR,
            TPIPE_MESSAGE_FORWARD_CHECK_TOP_EDGE_ERROR,
            TPIPE_MESSAGE_FORWARD_CHECK_BOTTOM_EDGE_ERROR,
            TPIPE_MESSAGE_FORWARD_CHECK_LEFT_EDGE_ERROR,
            TPIPE_MESSAGE_FORWARD_CHECK_RIGHT_EDGE_ERROR,
            TPIPE_MESSAGE_BACKWARD_CHECK_TOP_EDGE_ERROR,
            TPIPE_MESSAGE_BACKWARD_CHECK_BOTTOM_EDGE_ERROR,
            TPIPE_MESSAGE_BACKWARD_CHECK_LEFT_EDGE_ERROR,
            TPIPE_MESSAGE_BACKWARD_CHECK_RIGHT_EDGE_ERROR,
            TPIPE_MESSAGE_TDR_CHECK_NO_MODULE_EDGE_ERROR,
            TPIPE_MESSAGE_CHECK_OUT_CONFIG_ALIGN_XS_POS_ERROR,
            TPIPE_MESSAGE_CHECK_OUT_CONFIG_ALIGN_XE_POS_ERROR,
            TPIPE_MESSAGE_CHECK_OUT_CONFIG_ALIGN_YS_POS_ERROR,
            TPIPE_MESSAGE_CHECK_OUT_CONFIG_ALIGN_YE_POS_ERROR,
            TPIPE_MESSAGE_TPIPE_HEIGHT_ANR_II_MODE_CHECK_ERROR,
            TPIPE_MESSAGE_UNKNOWN_RESIZER_DIR_MODE_ERROR,
            TPIPE_MESSAGE_UNKNOWN_FEM_HARRIS_TPIPE_MODE_ERROR,
            TPIPE_MESSAGE_TOO_SMALL_FE_INPUT_XSIZE_ERROR,
            TPIPE_MESSAGE_TOO_SMALL_FE_INPUT_YSIZE_ERROR,
            TPIPE_MESSAGE_TOO_SMALL_TPIPE_WIDTH_FOR_FE_OUT_XE_ERROR,
            TPIPE_MESSAGE_TOO_SMALL_TPIPE_HEIGHT_FOR_FE_OUT_YE_ERROR,
            TPIPE_MESSAGE_NOT_SUPPORT_FE_IP_WIDTH_ERROR,
            TPIPE_MESSAGE_NOT_SUPPORT_FE_IP_HEIGHT_ERROR,
            TPIPE_MESSAGE_DISABLE_FUNC_X_SIZE_CHECK_ERROR,
            TPIPE_MESSAGE_DISABLE_FUNC_Y_SIZE_CHECK_ERROR,
            TPIPE_MESSAGE_OUTPUT_DISABLE_INPUT_FUNC_CHECK_ERROR,
            TPIPE_MESSAGE_RESIZER_SRC_ACC_SCALING_UP_ERROR,
            TPIPE_MESSAGE_RESIZER_CUBIC_ACC_SCALING_UP_ERROR,
            TPIPE_MESSAGE_BACKWARD_IN_XS_POS_ALIGN_ERROR,
            TPIPE_MESSAGE_BACKWARD_IN_XE_POS_ALIGN_ERROR,
            TPIPE_MESSAGE_BACKWARD_IN_YS_POS_ALIGN_ERROR,
            TPIPE_MESSAGE_BACKWARD_IN_YE_POS_ALIGN_ERROR,
            TPIPE_MESSAGE_TDR_TPIPE_EDGE_DIFFERENT_ERROR,
            TPIPE_MESSAGE_TDR_CDP_EDGE_DIFFERENT_ERROR,
            TPIPE_MESSAGE_NOT_SUPPORT_MFB_WITH_CURZ_CROP_ERROR,
            TPIPE_MESSAGE_NOT_SUPPORT_MFB_IN_FMT_ERROR,
            TPIPE_MESSAGE_RDMA_RING_BUFFER_CONFIG_ERRO,
            TPIPE_MESSAGE_RDMA_MODULE_CONFIG_ERROR,
            TPIPE_MESSAGE_CONFIG_FE_INPUT_SIZE_ERROR,
            /* verification */
            TPIPE_MESSAGE_VERIFY_CRZ_BACKWARD_FORWARD_HORIZONTAL_START_CONSISTENCE_ERROR,
            TPIPE_MESSAGE_VERIFY_CRZ_BACKWARD_FORWARD_HORIZONTAL_END_CONSISTENCE_ERROR,
            TPIPE_MESSAGE_VERIFY_CRZ_BACKWARD_FORWARD_VERTICAL_START_CONSISTENCE_ERROR,
            TPIPE_MESSAGE_VERIFY_CRZ_BACKWARD_FORWARD_VERTICAL_END_CONSISTENCE_ERROR,
            TPIPE_MESSAGE_VERIFY_CUBIC_BACKWARD_FORWARD_HORIZONTAL_START_CONSISTENCE_ERROR,
            TPIPE_MESSAGE_VERIFY_CUBIC_BACKWARD_FORWARD_HORIZONTAL_END_CONSISTENCE_ERROR,
            TPIPE_MESSAGE_VERIFY_CUBIC_BACKWARD_FORWARD_VERTICAL_START_CONSISTENCE_ERROR,
            TPIPE_MESSAGE_VERIFY_CUBIC_BACKWARD_FORWARD_VERTICAL_END_CONSISTENCE_ERROR,
            TPIPE_MESSAGE_VERIFY_VRZ_BACKWARD_FORWARD_HORIZONTAL_START_CONSISTENCE_ERROR,
            TPIPE_MESSAGE_VERIFY_VRZ_BACKWARD_FORWARD_HORIZONTAL_END_CONSISTENCE_ERROR,
            TPIPE_MESSAGE_VERIFY_VRZ_BACKWARD_FORWARD_VERTICAL_START_CONSISTENCE_ERROR,
            TPIPE_MESSAGE_VERIFY_VRZ_BACKWARD_FORWARD_VERTICAL_END_CONSISTENCE_ERROR,
            TPIPE_MESSAGE_VERIFY_BACKWARD_XS_LESS_THAN_FORWARD_ERROR,
            TPIPE_MESSAGE_VERIFY_FORWARD_XE_LESS_THAN_BACKWARD_ERROR,
            TPIPE_MESSAGE_VERIFY_BACKWARD_YS_LESS_THAN_FORWARD_ERROR,
            TPIPE_MESSAGE_VERIFY_FORWARD_YE_LESS_THAN_BACKWARD_ERROR,
            TPIPE_MESSAGE_VERIFY_BACKWARD_OFFSET_ERROR,
            TPIPE_MESSAGE_VERIFY_BACKWARD_BIAS_ERROR,
            TPIPE_MESSAGE_VERIFY_FORWARD_OFFSET_ERROR,
            TPIPE_MESSAGE_VERIFY_FORWARD_BIAS_ERROR,
            /* Tpipe ring buffer control */
            TPIPE_MESSAGE_INCORRECT_RING_CONFIG_ERROR,
            TPIPE_MESSAGE_INCORRECT_IMGI_RING_SIZE_ERROR,
            TPIPE_MESSAGE_INCORRECT_VIPI_RING_EN_ERROR,
            TPIPE_MESSAGE_INCORRECT_VIP2I_RING_EN_ERROR,
            TPIPE_MESSAGE_INCORRECT_VIPI_RING_SIZE_ERROR,
            TPIPE_MESSAGE_INCORRECT_VIP2I_RING_SIZE_ERROR,
            /* Tdr ring buffer control */
            TPIPE_MESSAGE_UNKNOWN_RING_RDMA_NAME_ERROR,
            TPIPE_MESSAGE_IMGI_FILE_PTR_REOPEN_ERROR,
            TPIPE_MESSAGE_VIPI_FILE_PTR_REOPEN_ERROR,
            TPIPE_MESSAGE_VIP2I_FILE_PTR_REOPEN_ERROR,
            TPIPE_MESSAGE_IMGI_FILE_OPEN_ERROR,
            TPIPE_MESSAGE_VIPI_FILE_OPEN_ERROR,
            TPIPE_MESSAGE_VIP2I_FILE_OPEN_ERROR,
            TPIPE_MESSAGE_MEMORY_ALLOCATE_ERROR,
            TPIPE_MESSAGE_INVALID_MCU_NO_ERROR,
            TPIPE_MESSAGE_TPIPE_RING_CONFIG_FILE_PTR_OPEN_ERROR,
            TPIPE_MESSAGE_TPIPE_RING_CONFIG_FILE_PTR_REOPEN_ERROR,
            TPIPE_MESSAGE_TPIPE_RING_CONFIG_NULL_PTR_ERROR,
            TPIPE_MESSAGE_TPIPE_RING_INCORRECT_CONFIG_ORDER_ERROR,
            /* dump c model hex */
            TPIPE_MESSAGE_TPIPE_CONFIG_EN_FILE_OPEN_ERROR,
            TPIPE_MESSAGE_TPIPE_CONFIG_MAP_FILE_OPEN_ERROR,
            /* tpipe mode control */
            TPIPE_MESSAGE_TPIPE_MODE_NO_OVER_MAX_COUNT_ERROR,
            TPIPE_MESSAGE_TPIPE_MODE_UNKNOWN_ENUM_ERROR,
            TPIPE_MESSAGE_TPIPE_MODE_NO_DUPLICATED_INIT_ERROR,
            TPIPE_MESSAGE_TPIPE_MODE_OUTPUT_FILE_COPY_ERROR,
            TPIPE_MESSAGE_TPIPE_MODE_OUTPUT_FILE_CMP_ERROR,
            TPIPE_MESSAGE_TPIPE_MODE_OUTPUT_FILE_DEL_ERROR,
            /* tpipe constraint */
            TPIPE_MESSAGE_DEBUG_PRINT_FILE_OPEN_ERROR,
            TPIPE_MESSAGE_UNWANTED_X_CAL_ERROR,
            TPIPE_MESSAGE_SKIP_X_NOT_BAKCUP_ERROR,
            TPIPE_MESSAGE_DEBUG_MODE_PASS_BUT_NO_TDR_DUMP_TO_RUN_CMODEL_ERROR,
            TPIPE_MESSAGE_VIDO_CROP_DISABLE_ERROR,
            TPIPE_MESSAGE_DTPIPEO_CROP_DISABLE_ERROR,
            /* tpipe platform */
            TPIPE_MESSAGE_TPIPE_PLATFORM_NULL_INPUT_CONFIG_ERROR,
            TPIPE_MESSAGE_TPIPE_PLATFORM_NULL_WORKING_BUFFER_ERROR,
            TPIPE_MESSAGE_TPIPE_PLATFORM_LESS_WORKING_BUFFER_ERROR,
            TPIPE_MESSAGE_TPIPE_NULL_PTR_COMP_ERROR,
            TPIPE_MESSAGE_TPIPE_HEX_DUMP_COMP_DIFF_ERROR,
            TPIPE_MESSAGE_TPIPE_REG_MAP_COMP_DIFF_ERROR,
            TPIPE_MESSAGE_TPIPE_PLATFORM_RETURN_ERROR,
            TPIPE_MESSAGE_TPIPE_NULL_MEM_PTR_ERROR,
            TPIPE_MESSAGE_TPIPE_NULL_FILE_PTR_ADDRESS_ERROR,
            TPIPE_MESSAGE_TPIPE_NULL_PTR_TDR_INV_ERROR,
            TPIPE_MESSAGE_TPIPE_DESCRIPTOR_PTR_NON_4_BYTES_ALGIN_ERROR,
            TPIPE_MESSAGE_WORKING_BUFFER_PTR_NON_4_BYTES_ALGIN_ERROR,
            TPIPE_MESSAGE_WORKING_BUFFER_SIZE_NON_4_BYTES_ALGIN_ERROR,
            /* tpipe dump check */
            TPIPE_MESSAGE_TDR_DUMP_DUPLICATED_MASK_ERROR,
            TPIPE_MESSAGE_FUNC_LUT_DUPLICATED_FOUND_ERROR,
            /* tdr inverse */
            TPIPE_MESSAGE_TDR_INV_TPIPE_NO_OVER_MAX_ERROR,
            TPIPE_MESSAGE_TDR_INV_DIFFERENT_TPIPE_CONFIG_NO_ERROR,
            TPIPE_MESSAGE_TDR_INV_NULL_PTR_ERROR,
            /* tpipe ut */
            TPIPE_MESSAGE_TPIPE_UT_WITH_WRONG_PLATFORM_DEF_FAIL,
            TPIPE_MESSAGE_TPIPE_UT_FILE_OPEN_ERROR,
            TPIPE_MESSAGE_TPIPE_UT_UNKOWN_REG_ERROR,
            /* resizer coeff check */
            TPIPE_MESSAGE_CDRZ_UNMATCH_HORZ_COEFF_ERROR,
            TPIPE_MESSAGE_CDRZ_UNMATCH_VERT_COEFF_ERROR,
            TPIPE_MESSAGE_CURZ_UNMATCH_HORZ_COEFF_ERROR,
            TPIPE_MESSAGE_CURZ_UNMATCH_VERT_COEFF_ERROR,
            TPIPE_MESSAGE_PRZ_UNMATCH_HORZ_COEFF_ERROR,
            TPIPE_MESSAGE_PRZ_UNMATCH_VERT_COEFF_ERROR,
            TPIPE_MESSAGE_CRZ_UNMATCH_INPUT_WIDTH_ERROR,
            TPIPE_MESSAGE_CRZ_UNMATCH_INPUT_HEIGHT_ERROR,
            /* vdec blk mode config check */
            TPIPE_MESSAGE_MFB_NOT_SUPPORT_VDEC_BLK_ERROR,
            /* last irq check */
            TPIPE_MESSAGE_TDR_LAST_IRQ_ERROR,
            /* final count, can not be changed */
            TPIPE_MESSAGE_MAX_NO
        };

        /**
             * @brief Ring Conf Tpipe Table
             */
        typedef struct ISPIO_TDRI_INFORMATION_STRUCT
        {
            MUINT32 mcu_buffer_start_no;    ///<  mcu row start no
            MUINT32 mcu_buffer_end_no;      ///<  mcu row end no
            MUINT32 tpipe_stop_flag;        ///<  stop flag
            MUINT32 dump_offset_no;         ///<  word offset
        }ISPIO_TDRI_INFORMATION_STRUCT;

        /**
             * @brief mage crop
             */
        struct STImgCrop{
        public:
            MUINT32 x;
            MUINT32 y;
            MUINT32 floatX; ///<  x float precise - 32 bit
            MUINT32 floatY; ///<  y float precise - 32 bit
            MUINT32 w;
            MUINT32 h;
        public:

            /**
                   * @brief Constructor
                   */
            STImgCrop()
                :x(0)
                ,y(0)
                ,floatX(0)
                ,floatY(0)
                ,w(0)
                ,h(0)
            {
            }
        };

        /**
             * @brief Image Info
             */
        struct ImgInfo
        {
        public:     //// fields.
            typedef EImageFormat EImgFmt_t;
            typedef EImageRotation EImgRot_t;
            typedef EImageFlip EImgFlip_t;
            typedef ERawPxlID ERawPxlID_t;
            EImgFmt_t   eImgFmt;        ///<   Image Pixel Format
            EImgRot_t   eImgRot;        ///<   Image Rotation degree in CW
            EImgFlip_t  eImgFlip;       ///<   Image Flip ON/OFF
            ERawPxlID_t eRawPxlID;      ///<  raw data pixel ID

            MUINT32     u4ImgWidth;     ///<   Image Width
            MUINT32     u4ImgHeight;    ///<   Image Height
            MUINT32     u4Offset;       ///<   Image offset byte size
            MUINT32     u4Stride[3];    ///<   Image line byte size,0 for one or Y plae/1 for u or uv plane/2 for v plane
            STImgCrop   crop;           ///<  image crop info. (ring buffer use curz to run crop)
            //
        public:

            /**
                   * @brief Constructor
                   */
            ImgInfo(
                EImgFmt_t const _eImgFmt = eImgFmt_UNKNOWN,
                EImgRot_t const _eImgFot = eImgRot_0,
                EImgFlip_t const _eImgFlip = eImgFlip_OFF,
                MUINT32 const _u4ImgWidth = 0,
                MUINT32 const _u4ImgHeight = 0
            )
                : eImgFmt(_eImgFmt)
                , eImgRot(_eImgFot)
                , eImgFlip(_eImgFlip)
                , u4ImgWidth(_u4ImgWidth)
                , u4ImgHeight(_u4ImgHeight)
                , crop()
            {
            }
        };

        /**
             * @brief Buffer Info
             */
        struct BufInfo
        {
        public:     //// fields.
            MUINT32     u4BufSize;  ///<  Per buffer size
            MUINTPTR    u4BufVA;    ///<   Vir Address of pool
            MUINTPTR    u4BufPA;    ///<   Phy Address of pool
            MINT32      memID;      ///<   memory ID
            MINT32      bufSecu;
            MINT32      bufCohe;
            //EBufType    eBufType;   // buffer type, by ION or other interface
            //
            MINT32      i4TimeStamp_sec;///<   time stamp in seconds.
            MINT32      i4TimeStamp_us; ///<   time stamp in microseconds
            //
        public:

            /**
                   * @brief Constructor
                   */
            BufInfo(
                MUINT32 const _u4BufSize = 0,
                MUINTPTR const _u4BufVA = 0,
                MUINTPTR const _u4BufPA = 0,
                MINT32  const _memID = 0,
                MINT32  const _bufSecu = 0,
                MINT32  const _bufCohe = 0
                //EBufType const _eBufType = eBufType_STD_M4U
            )
                : u4BufSize(_u4BufSize)
                , u4BufVA(_u4BufVA)
                , u4BufPA(_u4BufPA)
                , memID(_memID)
                , bufSecu(_bufSecu)
                , bufCohe(_bufCohe)
                //, eBufType(_eBufType)
                , i4TimeStamp_sec(0)
                , i4TimeStamp_us(0)
            {
            }

        public: ////    operations.
            inline MINT64   getTimeStamp_ns() const
            {
                return  i4TimeStamp_sec * 1000000000LL + i4TimeStamp_us * 1000LL;
            }
            //
        /*
            inline MBOOL    setTimeStamp()
            {
                struct timeval tv;
                if  ( 0 == ::gettimeofday(&tv, NULL) )
                {
                    i4TimeStamp_sec = tv.tv_sec;
                    i4TimeStamp_us  = tv.tv_usec;
                    return  MTRUE;
                }
                return  MFALSE;
            }
        */
            //
        };

        /**
             * @brief Ring Info
             */
        struct RingInfo
        {
        public:
            MUINT32 u4EnRingBuffer;         ///<  0:disable ring buffer, 1: enable ring buffer
            MUINT32 u4RingSize;             ///<  Ring Buffer Size
            MUINT32 u4RingBufferMcuRowNo;   ///< MCU Row number for ring buffer
            MUINT32 u4RingBufferMcuHeight;  ///< MCU Height for ring buffer
            MUINT32 u4RingConfBufVA;        ///<  Vir Address of ring conf buffer
            MUINT32 u4RingConfNumVA;        ///<  Vir Address of ring conf number (get from tpipe algorithm)
            MUINT32 u4RingConfVerNumVA;     ///<  Vir Address of ring vertical tpipe number (get from tpipe algorithm)
            MUINT32 u4RingErrorControlVA;   ///< for ring tpipe error control
            MUINT32 u4RingTdriBufOffset;    ///<  hardware tpipe table address offset

        public:

            /**
                   * @brief Constructor
                   */
            RingInfo(
                MBOOL const                     enRingBuffer = 0,
                MUINT32 const                   u4RingSize = 0,
                MUINT32 const                   u4RingBufferMcuRowNo = 0,
                MUINT32 const                   u4RingBufferMcuHeight = 0,
                MUINT32 const                   u4RingConfBufVA = 0,
                MUINT32 const                   u4RingConfNumVA = 0,
                MUINT32 const                   u4RingConfVerNumVA = 0,
                MUINT32 const                   u4RingErrorControlVA = 0,
                MUINT32 const                   u4RingTdriBufOffset = 0
            )
                : u4EnRingBuffer(enRingBuffer)
                , u4RingSize(u4RingSize)
                , u4RingBufferMcuRowNo(u4RingBufferMcuRowNo)
                , u4RingBufferMcuHeight(u4RingBufferMcuHeight)
                , u4RingConfBufVA(u4RingConfBufVA)
                , u4RingConfNumVA(u4RingConfNumVA)
                , u4RingConfVerNumVA(u4RingConfVerNumVA)
                , u4RingErrorControlVA(u4RingErrorControlVA)
                , u4RingTdriBufOffset(u4RingTdriBufOffset)

            {}
        };

        /**
             * @brief Capture Info
             */
        struct SegmentInfo
        {
        public:
            MUINT32 u4IsRunSegment;              ///<  0:withoud runnig segmentation interrupt, 1: run segmentation interrupt
            MUINT32 u4SegNumVa;                   ///<   get Tpipe number
            MUINT32 u4SegTpipeSimpleConfigIdx;  ///<   set segmentation idx for tpipe

        public:

            /**
                   * @brief Constructor
                   */
            SegmentInfo(
                MBOOL const                     u4IsRunSegment = 0,
                MUINT32 const                   u4SegNumVa = 0,
                MUINT32 const                   u4SegTpipeSimpleConfigIdx = 0
            )
                : u4IsRunSegment(u4IsRunSegment)
                , u4SegNumVa(u4SegNumVa)
                , u4SegTpipeSimpleConfigIdx(u4SegTpipeSimpleConfigIdx)
            {}
        };
    };  //namespace NSIspio
};  //namespace NSImageio


/*******************************************************************************
*
*******************************************************************************/
namespace NSImageio_FrmB {
namespace NSIspio_FrmB   {
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
* pipe support command list
********************************************************************************/
enum EPIPECmd {
    EPIPECmd_SET_SENSOR_DEV             = 0x1001,
    EPIPECmd_SET_SENSOR_GAIN            = 0x1002,
    EPIPECmd_SET_SENSOR_EXP             = 0x1003,
    EPIPECmd_SET_CAM_MODE               = 0x1004,
    EPIPECmd_SET_SCENE_MODE             = 0x1005,
    EPIPECmd_SET_ISO                    = 0x1006,
    EPIPECmd_SET_FLUORESCENT_CCT        = 0x1007,
    EPIPECmd_SET_SCENE_LIGHT_VALUE      = 0x1008,
    EPIPECmd_VALIDATE_FRAME             = 0x1009,
    EPIPECmd_SET_OPERATION_MODE         = 0x100A,
    EPIPECmd_SET_EFFECT                 = 0x100B,
    EPIPECmd_SET_ZOOM_RATIO             = 0x100C,
    EPIPECmd_SET_BRIGHTNESS             = 0x100D,
    EPIPECmd_SET_CONTRAST               = 0x100E,
    EPIPECmd_SET_EDGE                   = 0x100F,
    EPIPECmd_SET_HUE                    = 0x1010,
    EPIPECmd_SET_SATURATION             = 0x1011,
    EPIPECmd_SEND_TUNING_CMD            = 0x1012,
    EPIPECmd_DECIDE_OFFLINE_CAPTURE     = 0x1013,
    EPIPECmd_LOCK_REG                   = 0x1014,
    EPIPECmd_SET_SHADING_IDX            = 0x1018,
    EPIPECmd_SET_HRZ                    = 0x101A,
    EPIPECmd_SET_P1_UPDATE              = 0x101B,
    EPIPECmd_SET_IMGO                   = 0x101C,
    EPIPECmd_SET_IMGOBYPASS             = 0x101D,   //BYPASS imgo magic-sync for v1
    EPIPECmd_SET_IMG2OBYPASS            = 0x101E,   //BYPASS img2o magic-sync
    EPIPECmd_SET_BASE_ADDR              = 0x1102,
    EPIPECmd_SET_CQ_CHANNEL             = 0x1103,
    EPIPECmd_SET_CQ_TRIGGER_MODE        = 0x1104,
    EPIPECmd_AE_SMOOTH                  = 0x1105,
    EPIPECmd_SET_FMT_EN                 = 0x1107,
    EPIPECmd_SET_GDMA_LINK_EN           = 0x1108,
    EPIPECmd_SET_FMT_START              = 0x1109,
    EPIPECmd_SET_CAM_CTL_DBG            = 0x110A,
    EPIPECmd_SET_IMG_PLANE_BY_IMGI      = 0x110B,
    EPIPECmd_SET_D_CQ_CHANNEL           = 0x110C,
    EPIPECmd_SET_D_CQ_TRIGGER_MODE      = 0x110D,
    //EPIPECmd_SET_D_PATH_SCENARIO_TYPE   = 0x110E,
    EPIPECmd_GET_TG_OUT_SIZE            = 0x110F,
    EPIPECmd_GET_RMX_OUT_SIZE           = 0x1110,
    EPIPECmd_GET_HBIN_INFO              = 0x1111,
    EPIPECmd_GET_EIS_INFO               = 0x1112,
    EPIPECmd_GET_SUGG_BURST_QUEUE_NUM   = 0x1114,
    EPIPECmd_UPDATE_BURST_QUEUE_NUM     = 0x1115,
    EPIPECmd_GET_TWIN_INFO              = 0x1116,
    EPIPECmd_SET_EIS_CBFP               = 0X1117,
    EPIPECmd_SET_LCS_CBFP               = 0X1118,
    EPIPECmd_GET_CUR_FRM_STATUS         = 0x1119,
    EPIPECmd_GET_CUR_SOF_IDX            = 0x111a,

    EPIPECmd_SET_NR3D_EN                = 0x1300,
    EPIPECmd_SET_NR3D_DMA_SEL           = 0x1301,
    EPIPECmd_SET_CRZ_EN                 = 0x1302,
    EPIPECmd_SET_JPEG_CFG               = 0x1303,
    EPIPECmd_SET_JPEG_WORKBUF_SIZE      = 0x1304,
    EPIPECmd_SET_P2_QUEUE_CONTROL_STATE = 0x1305,

    EPIPECmd_SET_MODULE_EN              = 0x1401, //config top control enable
    EPIPECmd_SET_MODULE_SEL             = 0x1402, //config top control sel mask
    EPIPECmd_SET_MODULE_CFG             = 0x1403,
    EPIPECmd_GET_MODULE_HANDLE          = 0x1404,
    EPIPECmd_SET_MODULE_CFG_DONE        = 0x1405,
    EPIPECmd_RELEASE_MODULE_HANDLE      = 0x1406,
    EPIPECmd_SET_MODULE_DBG_DUMP        = 0x1407, //only for dbg

    EPIPECmd_GET_SENSOR_PRV_RANGE       = 0x2001,
    EPIPECmd_GET_SENSOR_FULL_RANGE      = 0x2002,
    EPIPECmd_GET_RAW_DUMMY_RANGE        = 0x2003,
    EPIPECmd_GET_SENSOR_NUM             = 0x2004,
    EPIPECmd_GET_SENSOR_TYPE            = 0x2005,
    EPIPECmd_GET_RAW_INFO               = 0x2006,
    EPIPECmd_GET_EXIF_DEBUG_INFO        = 0x2007,
    EPIPECmd_GET_SHADING_IDX            = 0x2008,
    EPIPECmd_GET_ATV_DISP_DELAY         = 0x2009,
    EPIPECmd_GET_SENSOR_DELAY_FRAME_CNT = 0x200A,
    EPIPECmd_GET_CAM_CTL_DBG            = 0x200B,
    EPIPECmd_GET_FMT                    = 0x200C,
    EPIPECmd_GET_GDMA                   = 0x200D,
    EPIPECmd_GET_NR3D_GAIN              = 0x200E,
    EPIPECmd_ISP_RESET                  = 0x4001,
    EPIPECmd_MAX                        = 0xFFFF
};

enum EPIPE_BUFQUECmd {
    EPIPE_BUFQUECmd_ENQUE_FRAME         = 0x0000,   //enque frame
    EPIPE_BUFQUECmd_WAIT_DEQUE          = 0x0001,   //wait deque for deque thread
    EPIPE_BUFQUECmd_DEQUE_SUCCESS       = 0x0002,   //deque done
    EPIPE_BUFQUECmd_DEQUE_FAIL          = 0x0003,   //deque done
    EPIPE_BUFQUECmd_WAIT_FRAME          = 0x0004,   //wait frame for user
    EPIPE_BUFQUECmd_WAKE_WAITFRAME      = 0x0005,   //wake up user that wait for a frame to check
    EPIPE_BUFQUECmd_CLAER_ALL           = 0x0006    //clear all stored buffer in kernel list
};

/*******************************************************************************
* interrupr event
********************************************************************************/
enum EPipeIRQ {
    EPIPEIRQ_VSYNC      = 0,
    EPIPEIRQ_SOF,
    EPIPEIRQ_PATH_DONE
};


/*******************************************************************************
* CQ
********************************************************************************/
enum EPipeCQ {
    EPIPE_CQ_NONE = (-1),
    EPIPE_PASS1_CQ0 = 0,
    EPIPE_PASS1_CQ0B,
    EPIPE_PASS1_CQ0C,
    EPIPE_PASS1_CQ0_D,
    EPIPE_PASS1_CQ0B_D,
    EPIPE_PASS1_CQ0C_D,
    EPIPE_PASS2_CQ1,
    EPIPE_PASS2_CQ1_SYNC,
    EPIPE_PASS2_CQ2,
    EPIPE_PASS2_CQ2_SYNC,
    EPIPE_PASS2_CQ3
};
//
enum EPipeCQTriger {
    EPIPECQ_TRIGGER_SINGLE_IMMEDIATE = 0,
    EPIPECQ_TRIGGER_SINGLE_EVENT,
    EPIPECQ_TRIGGER_CONTINUOUS_EVENT
};
//
enum EPipeCQStart {
    EPIPECQ_TRIG_BY_START = 0,
    EPIPECQ_TRIG_BY_PASS1_DONE,
    EPIPECQ_TRIG_BY_PASS2_DONE,
    EPIPECQ_TRIG_BY_IMGO_DONE,
    EPIPECQ_TRIG_BY_IMG2O_DONE,
};

/*******************************************************************************
* buffer source type
********************************************************************************/
enum EBufType
{
    eBufType_PMEM       = 0,  //= ISP_BUF_TYPE_PMEM,
    eBufType_STD_M4U,         //= ISP_BUF_TYPE_STD_M4U,
    eBufType_ION,             //= ISP_BUF_TYPE_ION,
};
/*******************************************************************************
* free buffer mode.
********************************************************************************/
enum EFreeBufMode {
    eFreeBufMode_SINGLE         = 0x0000,   //
    eFreeBufMode_ALL            = 0x0001,   //
};


/*******************************************************************************
* Image Rotation.
********************************************************************************/
enum EImageRotation
{
    eImgRot_0      = 0, //
    eImgRot_90,         //90 CW
    eImgRot_180,
    eImgRot_270
};
/*******************************************************************************
* Image Rotation.
********************************************************************************/
enum EImageFlip
{
    eImgFlip_OFF     = 0, //
    eImgFlip_ON      = 1, //
};

/*******************************************************************************
* raw image pixel ID
********************************************************************************/
enum ERawPxlID
{
    ERawPxlID_B   = 0,  // B Gb Gr R
    ERawPxlID_Gb,       // Gb B R Gr
    ERawPxlID_Gr,       // Gr R B Gb
    ERawPxlID_R         // R Gr Gb B
};

/*******************************************************************************
* raw data memory footprint bit per pixel
********************************************************************************/
enum ERAW_MEM_FP_BPP
{
    ERAW8_MEM_FP_BPP   = 8,
    ERAW10_MEM_FP_BPP  = 10,
    ERAW12_MEM_FP_BPP  = 12,
};

/*******************************************************************************
* STRIDE INFO INDEX
********************************************************************************/
enum EIMAGE_STRIDE
{
    ESTRIDE_1ST_PLANE   = 0,
    ESTRIDE_2ND_PLANE   = 1,
    ESTRIDE_3RD_PLANE   = 2
};




/*******************************************************************************
* raw image Type setting
********************************************************************************/
enum ERawFmt
{
    eRawFmt_Processed          = 0x0000,   // processed Raw
    eRawFmt_Pure               = 0x0001,   // Pure Raw
};

/*******************************************************************************
* TG pixel sampling mode setting
********************************************************************************/
enum EPxlMode
{
    ePxlMode_One_Single   = 0x0000,   // 1 pixel mode single raw
    ePxlMode_One_Twin     = 0x0001,   // 1 pixel mode twin mode
    ePxlMode_Two_Single   = 0x0002,   // 2 pixel mode single raw
    ePxlMode_Two_Twin     = 0x0004,   // 2 pixel mode twin mode
    ePxlMode_RSVD         = 0x000FF   // 2 pixel mode twin mode
};

/*******************************************************************************
* pass1 module list
********************************************************************************/
enum EModule
{
    //raw
    EModule_OB          = 00,
    EModule_BNR         = 05,
    EModule_LSC         = 10,
    EModule_RPG         = 15,
    EModule_AE          = 20,
    EModule_AWB         = 25,
    EModule_SGG1        = 30,
    EModule_FLK         = 35,
    EModule_AF          = 40,
    EModule_SGG2        = 45,
    EModule_SGG3        = 46,
    EModule_EIS         = 50,
    EModule_LCS         = 55,
    EModule_BPCI        = 60,
    EModule_LSCI        = 65,
    EModule_AAO         = 70,
    EModule_ESFKO       = 75,
    EModule_AFO         = 80,
    EModule_EISO        = 85,
    EModule_LCSO        = 90,
    EModule_iHDR        = 95,
    //raw_d
    EModule_OB_D        = 1000,
    EModule_BNR_D       = 1005,
    EModule_LSC_D       = 1010,
    EModule_RPG_D       = 1015,
    EModule_BPCI_D      = 1020,
    EModule_LSCI_D      = 1025,
    EModule_AE_D        = 1030,
    EModule_AWB_D       = 1035,
    EModule_SGG1_D      = 1040,
    EModule_AF_D        = 1045,
    EModule_LCS_D       = 1050,
    EModule_AAO_D       = 1055,
    EModule_AFO_D       = 1060,
    EModule_LCSO_D      = 1065,
    EModule_iHDR_D      = 1070
};

/*******************************************************************************
* pass2 runtime module list
********************************************************************************/
enum EP2Module
{
    EP2Module_NONE      = 0x0000,
    EP2Module_NR3D      = 0x0001,
    EP2Module_STA_FEO   = 0x0010,  //statistic dma data(linke feo)
    EP2Module_SRZ1      = 0x0100,
    EP2Module_STA_LCEI  = 0x1000,  //when use statistic dma data in lcei (only for work around)
};

/*******************************************************************************
* image resizer
********************************************************************************/
struct STImgResize{
    public:
        MUINT32 src_x;
        MUINT32 src_y;
        MUINT32 src_w;
        MUINT32 src_h;
        MUINT32 tar_x;
        MUINT32 tar_y;
        MUINT32 tar_w;
        MUINT32 tar_h;
    public:
    STImgResize()
        :src_x(0)
        ,src_y(0)
        ,src_w(0)
        ,src_h(0)
        ,tar_x(0)
        ,tar_y(0)
        ,tar_w(0)
        ,tar_h(0)
        {
        }
};

/*******************************************************************************
* image crop
********************************************************************************/
struct STImgCrop{
public:
    MUINT32 x;
    MUINT32 y;
    MUINT32 floatX; /* x float precise - 32 bit */
    MUINT32 floatY; /* y float precise - 32 bit */
    MUINT32 w;
    MUINT32 h;
public:
    STImgCrop()
        :x(0)
        ,y(0)
        ,floatX(0)
        ,floatY(0)
        ,w(0)
        ,h(0)
    {
    }
};

/*******************************************************************************
* Image Info.
********************************************************************************/
struct ImgInfo
{
public:     //// fields.
    typedef EImageFormat EImgFmt_t;
    typedef EImageRotation EImgRot_t;
    typedef EImageFlip EImgFlip_t;
    typedef ERawPxlID ERawPxlID_t;
    typedef EPxlMode EPxlMode_t;
    EImgFmt_t   eImgFmt;        //  Image Pixel Format
    EImgRot_t   eImgRot;        //  Image Rotation degree in CW
    EImgFlip_t  eImgFlip;       //  Image Flip ON/OFF
    ERawPxlID_t eRawPxlID;      //  raw data pixel ID
    EPxlMode_t  ePxlMode;       //  seninf/tg sampling mode
    //
    MFLOAT      rrzRatio;       //  for sl2
    MUINT32     rrzCropX;       //  for sl2
    MUINT32     rrzCropY;       //  for sl2
    MUINT32     u4MagicNum;     //  magic number for tuning queue
    MUINT32     u4PureRaw;
    MUINT32     u4PureRawPak;
    MUINT32     u4ImgWidth;     //  Image Width
    MUINT32     u4ImgHeight;    //  Image Height
    MUINT32     u4Offset;       //  Image offset byte size
    MUINT32     u4Stride[3];    //  Image line byte size,0 for one or Y plae/1 for u or uv plane/2 for v plane
    STImgCrop   crop1;           // image crop info. (ring buffer use curz to run crop)
    STImgResize resize1;
    STImgCrop   crop2;           // image crop info. (ring buffer use curz to run crop)
    STImgResize resize2;
    STImgCrop   crop3;           // image crop info. (ring buffer use curz to run crop)
    STImgResize resize3;
    //
public:     //// constructors.
    ImgInfo(
        EImgFmt_t const _eImgFmt = eImgFmt_UNKNOWN,
        EImgRot_t const _eImgFot = eImgRot_0,
        EImgFlip_t const _eImgFlip = eImgFlip_OFF,
        EPxlMode_t const _ePxlMode = ePxlMode_One_Single,
        MUINT32 const _u4PureRaw = 0,
        MUINT32 const _u4PureRawPak = 0,
        MUINT32 const _u4ImgWidth = 0,
        MUINT32 const _u4ImgHeight = 0
    )
        : eImgFmt(_eImgFmt)
        , eImgRot(_eImgFot)
        , eImgFlip(_eImgFlip)
        , ePxlMode(_ePxlMode)
        , u4PureRaw(_u4PureRaw)
        , u4PureRawPak(_u4PureRawPak)
        , u4ImgWidth(_u4ImgWidth)
        , u4ImgHeight(_u4ImgHeight)
        , crop1()
    {
    }
};


/*******************************************************************************
* Buffer Info.
********************************************************************************/
struct BufInfo  //buffer for each dma port (size/va/pa/memid should be enlarge to 3 for multi-plane support in one dma port)
{
public:     //// fields.
    MUINT32     u4BufSize[3];  //  Per buffer size
    MUINTPTR    u4BufVA[3];    //  Vir Address of pool
    MUINTPTR    u4BufPA[3];    //  Phy Address of pool
    MINT32      memID[3];      //  memory ID
    MINT32      bufSecu[3];
    MINT32      bufCohe[3];
    //EBufType    eBufType;   // buffer type, by ION or other interface
    //
    MINT32      i4TimeStamp_sec;//  time stamp in seconds.
    MINT32      i4TimeStamp_us; //  time stamp in microseconds
    //
    MUINT32     img_w;
    MUINT32     img_h;
    MUINT32     img_stride;
    MUINT32     img_fmt;
    MUINT32     img_pxl_id;
    MUINT32     img_wbn;
    MUINT32     img_ob;
    MUINT32     img_lsc;
    MUINT32     img_rpg;
    MUINT32     m_num_0;
    MUINT32     m_num_1;
    MUINT32     frm_cnt;
    MUINT32     jpg_size;
    MVOID       *header; //refer to stISP_BUF_INFO*
    MUINT32     headerSize;

    MINT32      mBufIdx; // used for replace buffer
    MUINT32     xoffset;    //starting x-offset of dma
    MUINT32     yoffset;    //starting y-offset of dma
    MRect       crop_win;   //crop windon, IN TG coordinate axis
    MSize       DstSize;    // image w/h on dram
    //
public:     //// constructors.
    BufInfo()
        : u4BufSize({0,0,0})
        , u4BufVA({0,0,0})
        , u4BufPA({0,0,0})
        , memID({0,0,0})
        , bufSecu({0,0,0})
        , bufCohe({0,0,0})
        , i4TimeStamp_sec(0)
        , i4TimeStamp_us(0)
        , img_w(0)
        , img_h(0)
        , img_stride(0)
        , img_fmt(0)
        , img_pxl_id(0)
        , img_wbn(0)
        , img_ob(0)
        , img_lsc(0)
        , img_rpg(0)
        , m_num_0(0)
        , m_num_1(0)
        , frm_cnt(0)
        , xoffset(0)
        , yoffset(0)
    {
        crop_win = MRect(MPoint(0,0),MSize(0,0));
        DstSize  = MSize(0,0);
    }
    //

public: ////    operations.
    inline MINT64   getTimeStamp_ns() const
    {
        return  i4TimeStamp_sec * 1000000000LL + i4TimeStamp_us * 1000LL;
    }
    //
/*
    inline MBOOL    setTimeStamp()
    {
        struct timeval tv;
        if  ( 0 == ::gettimeofday(&tv, NULL) )
        {
            i4TimeStamp_sec = tv.tv_sec;
            i4TimeStamp_us  = tv.tv_usec;
            return  MTRUE;
        }
        return  MFALSE;
    }
*/
    //
};

/*******************************************************************************
* irq
********************************************************************************/
class Irq_t

{
public:
    MUINT32 Type;
    MUINT32 Status;
    MINT32  UserEnum;
    MUINT32 Timeout;
    MINT8*   UserName;
    MUINT32 irq_TStamp;
public:     //// constructors.
    Irq_t(
        MUINT32 const   _Type = 0,
        MUINT32 const   _Status = 0,
        MINT32  const   _UserEnum = 0,
        MUINT32 const   _Timeout = 0,
        MINT8*  const   _UserName = (MINT8* const)"default_usr",
        MUINT32 const   _irq_TStamp = 0
    )
        : Type(_Type)
        , Status(_Status)
        , UserEnum(_UserEnum)
        , Timeout(_Timeout)
        , UserName(_UserName)
        , irq_TStamp(_irq_TStamp)
    {}

};

////////////////////////////////////////////////////////////////////////////////
};  //namespace NSIspio_FrmB
};  //namespace NSImageio_FrmB

#endif // _ISPIO_STDDEF_H_

