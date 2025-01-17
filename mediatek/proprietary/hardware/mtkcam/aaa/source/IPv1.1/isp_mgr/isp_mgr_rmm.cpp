/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

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
#define LOG_TAG "isp_mgr_rmm"

#ifndef ENABLE_MY_LOG
    #define ENABLE_MY_LOG       (1)
#endif

#include <cutils/properties.h>
#include <aaa_types.h>
#include <aaa_error_code.h>
#include <aaa_log.h>
#include "isp_mgr.h"

namespace NSIspTuningv3
{

#ifndef MAX
#define MAX(a,b) ((a) >= (b) ? (a) : (b))
#endif

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// RMM
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
ISP_MGR_RMM_T&
ISP_MGR_RMM_T::
getInstance(ESensorDev_T const eSensorDev)
{
    switch (eSensorDev)
    {
    case ESensorDev_Main: //  Main Sensor
        return  ISP_MGR_RMM_DEV<ESensorDev_Main>::getInstance();
    case ESensorDev_MainSecond: //  Main Second Sensor
        return  ISP_MGR_RMM_DEV<ESensorDev_MainSecond>::getInstance();
    case ESensorDev_Sub: //  Sub Sensor
        return  ISP_MGR_RMM_DEV<ESensorDev_Sub>::getInstance();
    default:
        MY_ERR("eSensorDev(%d)", eSensorDev);
        return  ISP_MGR_RMM_DEV<ESensorDev_Main>::getInstance();
    }
}

template <>
ISP_MGR_RMM_T&
ISP_MGR_RMM_T::
put(ISP_NVRAM_RMM_T const& rParam)
{
#if 1
    PUT_REG_INFO(CAM_RMM_OSC, osc);
    PUT_REG_INFO(CAM_RMM_MC, mc);
    PUT_REG_INFO(CAM_RMM_MC2, mc2);
    PUT_REG_INFO(CAM_RMM_MA, ma);
    PUT_REG_INFO(CAM_RMM_TUNE, tune);
    PUT_REG_INFO(CAM_RMM_IDX, ridx);
#endif

    // other register not tuning in NVRAM

    return  (*this);
}

template <>
ISP_MGR_RMM_T&
ISP_MGR_RMM_T::
get(ISP_NVRAM_RMM_T& rParam)
{
#if 1
    GET_REG_INFO(CAM_RMM_OSC, osc);
    GET_REG_INFO(CAM_RMM_MC, mc);
    GET_REG_INFO(CAM_RMM_MC2, mc2);
    GET_REG_INFO(CAM_RMM_MA, ma);
    GET_REG_INFO(CAM_RMM_TUNE, tune);
    GET_REG_INFO(CAM_RMM_IDX, ridx);
#endif

    // other register not tuning in NVRAM

    return  (*this);
}

#if 0
MVOID
ISP_MGR_RMM_T::
setAeLeSeRatio(MINT32 aeRatio)
{
    MY_LOG("[%s] aeRatio(%d)",__func__,aeRatio);
    mAeExpRatio = aeRatio/100.0;

    if(mAeExpRatio < 1.0)
    {
        MY_LOG("mAeExpRatio < 1.0");
        mAeExpRatio = 1.0;
    }

    MY_LOG("[%s] mAeExpRatio(%f),dev(%d)",__func__,mAeExpRatio,m_eSensorDev);
}
#endif

MINT32 GetOffset(MINT32 IDX)
{
     if(IDX > 192)
         return 0;
    else if (IDX > 96)
         return 1;
    else if(IDX > 48)
         return 2;
    else if(IDX > 24)
         return 3;
    else if(IDX > 12)
         return 4;
    else if(IDX > 6)
         return 5;
    else if (IDX >3)
         return 6;
    else
        return  7;

}


MBOOL
ISP_MGR_RMM_T::
apply(RAWIspCamInfo& rRawIspCamInfo, TuningMgr& rTuning, MINT32 i4SubsampleIdex)
{

    MBOOL bRMM_EN = isEnable();

    addressErrorCheck("Before ISP_MGR_RMM_T::apply()");

    rTuning.updateEngine(eTuningMgrFunc_RMM, bRMM_EN, i4SubsampleIdex);

    // TOP
    TUNING_MGR_WRITE_BITS_CAM((&rTuning), CAM_CTL_EN, RMM_EN, bRMM_EN, i4SubsampleIdex);

    ISP_MGR_CTL_EN_P1_T::getInstance(m_eSensorDev).setEnable_RMM(bRMM_EN);

     //> prepar register value
    if(bRMM_EN)
    {

        MINT32 aeLeSeRatio = (rRawIspCamInfo.rAEInfo.i4LESE_Ratio + 50) / 100;
        MINT32 rmgTH = rRawIspCamInfo.rAEInfo.i4HdrSeg;

        MY_LOG_IF(debugDump, "isEnable(%d), RMG_TH(%d) i4LESE_Ratio(%d)->asLeSeRatio(%d)", bRMM_EN, rmgTH, rRawIspCamInfo.rAEInfo.i4LESE_Ratio, aeLeSeRatio);

        MINT32 rmmOcsTh_default = 0;

        if( rmgTH != 0)
            rmmOcsTh_default = 1020 * rmgTH / 1024;
        else
        {
            if(aeLeSeRatio == 0){
                MY_ERR("asLeSeRatio is 0, set it to default 1");
                aeLeSeRatio = 1;
            }
            rmmOcsTh_default = 4080/aeLeSeRatio;
        }

        // Need to use int to do MAX calculation
        MINT32 rmmOcsIdx = reinterpret_cast<ISP_CAM_RMM_IDX_T*>(REG_INFO_VALUE_PTR(CAM_RMM_IDX))->RMM_OSC_IDX;
        MINT32 rmmPsIdx = reinterpret_cast<ISP_CAM_RMM_IDX_T*>(REG_INFO_VALUE_PTR(CAM_RMM_IDX))->RMM_PS_IDX;
        MINT32 rmmMoseIdx = reinterpret_cast<ISP_CAM_RMM_IDX_T*>(REG_INFO_VALUE_PTR(CAM_RMM_IDX))->RMM_MOSE_IDX;


        MINT32 rmmOsbldWd = reinterpret_cast<ISP_CAM_RMM_MA_T*>(REG_INFO_VALUE_PTR(CAM_RMM_MA))->RMM_OSBLD_WD;
        MINT32 rmmLebldWd = reinterpret_cast<ISP_CAM_RMM_OSC_T*>(REG_INFO_VALUE_PTR(CAM_RMM_OSC))->RMM_LEBLD_WD;
        MINT32 rmmMasebldWd = reinterpret_cast<ISP_CAM_RMM_MA_T*>(REG_INFO_VALUE_PTR(CAM_RMM_MA))->RMM_MASE_BLDWD;
        MINT32 rmmSebldWd = reinterpret_cast<ISP_CAM_RMM_OSC_T*>(REG_INFO_VALUE_PTR(CAM_RMM_OSC))->RMM_SEBLD_WD;
        MINT32 rmmMosebldWd = reinterpret_cast<ISP_CAM_RMM_MC2_T*>(REG_INFO_VALUE_PTR(CAM_RMM_MC2))->RMM_MOSE_BLDWD;

        MY_LOG_IF(debugDump, "Prev Val : RMM_OSC_IDX(%d), RMM_PS_IDX(%d), RMM_MOSE_IDX(%d), RMM_OSBLD_WD(%d),RMM_LEBLD_WD(%d),RMM_MASE_BLDWD(%d),RMM_SEBLD_WD(%d),RMM_MOSE_BLDWD(%d)",
               rmmOcsIdx, rmmPsIdx,  rmmMoseIdx, rmmOsbldWd, rmmLebldWd, rmmMasebldWd, rmmSebldWd, rmmMosebldWd);


        // Need to use int to do MAX calculation
        MINT32 rmmOscTh = (rmmOcsTh_default * (rmmOcsIdx + 1)) >> 8;
        MINT32 rmmPsTh = (rmmOcsTh_default * (rmmPsIdx + 1)) >> 8;
        MINT32 rmmMoseTh = (rmmOcsTh_default * (rmmMoseIdx + 1)) >> 8;
        MINT32 rmmLeosGray = rmmOscTh;

        rmmOsbldWd = MAX( (rmmOsbldWd - GetOffset(rmmOcsIdx)) , 0);
        rmmLebldWd = MAX( (rmmLebldWd - GetOffset(rmmOcsIdx)) , 0);
        rmmMasebldWd = MAX( (rmmMasebldWd - GetOffset(rmmOcsIdx)) , 0);
        rmmSebldWd = MAX( (rmmSebldWd - GetOffset(rmmPsIdx)) , 0);
        rmmMosebldWd = MAX( (rmmMosebldWd - GetOffset(rmmMoseIdx)) , 0);

        MY_LOG_IF(debugDump, "Now Val : rmmOscTh(%d), rmmPsTh(%d), rmmMoseTh(%d), rmmLeosGray(%d), rmmOsbldWd(%d), rmmLebldWd(%d), rmmMasebldWd(%d), rmmSebldWd(%d), rmmMosebldWd(%d)", rmmOscTh, rmmPsTh, rmmMoseTh, rmmLeosGray, rmmOsbldWd, rmmLebldWd, rmmMasebldWd, rmmSebldWd, rmmMosebldWd);

        MUINT32 awbGainR = rRawIspCamInfo.rAWBInfo.rCurrentAWBGain.i4R;
        MUINT32 awbGainG = rRawIspCamInfo.rAWBInfo.rCurrentAWBGain.i4G;
        MUINT32 awbGainB = rRawIspCamInfo.rAWBInfo.rCurrentAWBGain.i4B;

        // == log input parameter ===
        // TODO After vhdr stable, must remove this log to avoid performance
        MY_LOG("in: LeRatio(%d),hdrTH(%d),AWB rgb(%d, %d, %d)", rRawIspCamInfo.rAEInfo.i4LESE_Ratio, rRawIspCamInfo.rAEInfo.i4HdrSeg,
        awbGainR, awbGainG, awbGainB);

        if(awbGainR == 0 || awbGainG == 0 || awbGainB == 0 ){
            MY_ERR("awb gain has 0, r,g,b = (%d,%d,%d), set it to all 512.", awbGainR, awbGainG, awbGainB);
            awbGainR = 512;
            awbGainG = 512;
            awbGainB = 512;
        }

        MUINT32 rmmRevgR = 512 * 1024 / awbGainR;
        MUINT32 rmmRevgGR = 512 * 1024 / awbGainG;
        MUINT32 rmmRevgB = 512 * 1024 / awbGainB;
        MUINT32 rmmRevgGB = rmmRevgGR;

        MY_LOG_IF(debugDump, "awbGain r,g,b = (%d,%d,%d), REVG_R(%d), REVG_GR(%d), REVG_B(%d), REVG_GB(%d)", awbGainR, awbGainG, awbGainB, rmmRevgR, rmmRevgGR, rmmRevgB, rmmRevgGB);


         // Register setting
        MUINT32 orig = 0;
        //== Set RMM_OSC_T ===
        orig = REG_INFO_VALUE(CAM_RMM_OSC);
        REG_INFO_VALUE(CAM_RMM_OSC) = (orig & 0xFF00F000)
                                | (rmmOscTh & 0xFFF)
                                | ((rmmSebldWd & 0xF) << 16)
                                | ((rmmLebldWd & 0xF) << 20);

        // === set RMM_MC_T ===
        //  No register need update

        // === set RMM_REVG_1 ===
        orig = REG_INFO_VALUE(CAM_RMM_REVG_1);
        REG_INFO_VALUE(CAM_RMM_REVG_1) = (orig & 0xF800F800)
                                | (rmmRevgR & 0x7FF)
                                | ((rmmRevgGR & 0x7FF) << 16);


        // === set RMM_REVG_2 ===
        orig = REG_INFO_VALUE(CAM_RMM_REVG_2);
        REG_INFO_VALUE(CAM_RMM_REVG_2) = (orig & 0xF800F800)
                                | (rmmRevgB & 0x7FF)
                                | ((rmmRevgGB & 0x7FF) << 16);

        // === set RMM_LEOS ===
        orig = REG_INFO_VALUE(CAM_RMM_LEOS);
        REG_INFO_VALUE(CAM_RMM_LEOS) = (orig & 0xFFFFF000)
                                | (rmmLeosGray & 0xFFF);

        // === set RMM_MC2 ===
        orig = REG_INFO_VALUE(CAM_RMM_MC2);
        REG_INFO_VALUE(CAM_RMM_MC2) = (orig & 0xFFF0F000)
                                | (rmmMoseTh & 0xFFF)
                                | ((rmmMosebldWd & 0xF) << 16);

        // === set RMM_DIFF_LB ===
        // No register need Update
        // === set RMM_MA ===
        orig = REG_INFO_VALUE(CAM_RMM_MA);
        REG_INFO_VALUE(CAM_RMM_MA) = (orig & 0xFFFF00FF)
                                | ((rmmOsbldWd & 0xF) << 8)
                                | ((rmmMasebldWd & 0xF) << 12);
        // === set RMM_TUNE ===
        orig = REG_INFO_VALUE(CAM_RMM_TUNE);
        REG_INFO_VALUE(CAM_RMM_TUNE) = (orig & 0xF000FFFF)
                                | ((rmmPsTh & 0xFFF) << 16);




#if 0
        // ================ TEST force set NVRAM value =============
        REG_INFO_VALUE(CAM_RMM_OSC) = 0x009743fc;
        REG_INFO_VALUE(CAM_RMM_MC) = 0x00040461; //0x00040465;
        REG_INFO_VALUE(CAM_RMM_REVG_1) = 0x04000231;
        REG_INFO_VALUE(CAM_RMM_REVG_2) = 0x04000247;
        REG_INFO_VALUE(CAM_RMM_LEOS) = 0x000003fc;
        REG_INFO_VALUE(CAM_RMM_MC2) = 0x00020083;
        REG_INFO_VALUE(CAM_RMM_DIFF_LB) = 0x00000000;
        REG_INFO_VALUE(CAM_RMM_MA) = 0x08088908;
        REG_INFO_VALUE(CAM_RMM_TUNE) = 0x32FD1113; //0x21020013;
#endif


    } // if bRMM_EN end


    rTuning.updateEngine(eTuningMgrFunc_RMM, bRMM_EN, 0);

    // TOP
    TUNING_MGR_WRITE_BITS_CAM((&rTuning), CAM_CTL_EN, RMM_EN, bRMM_EN, 0);

    ISP_MGR_CTL_EN_P1_T::getInstance(m_eSensorDev).setEnable_RMM(bRMM_EN);


    // Register setting  Notice: RMM_IDX doesn't exist in HW, so m_u4RegInfoNum-1
    rTuning.tuningMgrWriteRegs(
            static_cast<TUNING_MGR_REG_IO_STRUCT*>(m_pRegInfo),
            (m_u4RegInfoNum-1), i4SubsampleIdex);


    dumpRegInfo("RMM");

    addressErrorCheck("After ISP_MGR_RMM_T::apply()");

    return  MTRUE;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// RMM2
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
ISP_MGR_RMM2_T&
ISP_MGR_RMM2_T::
getInstance(ESensorDev_T const eSensorDev)
{
    switch (eSensorDev)
    {
    case ESensorDev_Main: //  Main Sensor
        return  ISP_MGR_RMM2_DEV<ESensorDev_Main>::getInstance();
    case ESensorDev_MainSecond: //  Main Second Sensor
        return  ISP_MGR_RMM2_DEV<ESensorDev_MainSecond>::getInstance();
    case ESensorDev_Sub: //  Sub Sensor
        return  ISP_MGR_RMM2_DEV<ESensorDev_Sub>::getInstance();
    default:
        MY_ERR("eSensorDev(%d)", eSensorDev);
        return  ISP_MGR_RMM2_DEV<ESensorDev_Main>::getInstance();
    }
}

template <>
ISP_MGR_RMM2_T&
ISP_MGR_RMM2_T::
put(ISP_NVRAM_RMM_T const& rParam)
{
    PUT_REG_INFO(DIP_X_RMM2_OSC, osc);
    PUT_REG_INFO(DIP_X_RMM2_MC, mc);
    PUT_REG_INFO(DIP_X_RMM2_MC2, mc2);
    PUT_REG_INFO(DIP_X_RMM2_MA, ma);
    PUT_REG_INFO(DIP_X_RMM2_TUNE, tune);
    PUT_REG_INFO(DIP_X_RMM2_IDX, ridx);

    // other register not tuning in NVRAM

    return  (*this);
}


template <>
ISP_MGR_RMM2_T&
ISP_MGR_RMM2_T::
get(ISP_NVRAM_RMM_T& rParam)
{
    GET_REG_INFO(DIP_X_RMM2_OSC, osc);
    GET_REG_INFO(DIP_X_RMM2_MC, mc);
    GET_REG_INFO(DIP_X_RMM2_MC2, mc2);
    GET_REG_INFO(DIP_X_RMM2_MA, ma);
    GET_REG_INFO(DIP_X_RMM2_TUNE, tune);
    GET_REG_INFO(DIP_X_RMM2_IDX, ridx);

    // other register not tuning in NVRAM

    return  (*this);
}

template <>
MBOOL
ISP_MGR_RMM2_T::
get(ISP_NVRAM_RMM_T& rParam, const dip_x_reg_t* pReg) const
{
    if (pReg)
    {
        GET_REG_INFO_BUF(DIP_X_RMM2_OSC, osc);
        GET_REG_INFO_BUF(DIP_X_RMM2_MC, mc);
        GET_REG_INFO_BUF(DIP_X_RMM2_MC2, mc2);
        GET_REG_INFO_BUF(DIP_X_RMM2_MA, ma);
        GET_REG_INFO_BUF(DIP_X_RMM2_TUNE, tune);
        GET_REG_INFO(DIP_X_RMM2_IDX, ridx);
    }
    // other register not tuning in NVRAM
    return MTRUE;
}

#if 0
MVOID
ISP_MGR_RMM_T::
setAeLeSeRatio(MINT32 aeRatio)
{
    MY_LOG("[%s] aeRatio(%d)",__func__,aeRatio);
    mAeExpRatio = aeRatio/100.0;

    if(mAeExpRatio < 1.0)
    {
        MY_LOG("mAeExpRatio < 1.0");
        mAeExpRatio = 1.0;
    }

    MY_LOG("[%s] mAeExpRatio(%f),dev(%d)",__func__,mAeExpRatio,m_eSensorDev);
}
#endif

MBOOL
ISP_MGR_RMM2_T::
apply(const RAWIspCamInfo& rRawIspCamInfo, dip_x_reg_t* pReg)
{
    MBOOL bRMM_EN = isEnable();

    // TOP
    ISP_WRITE_ENABLE_BITS(pReg, DIP_X_CTL_RGB_EN, RMM2_EN, bRMM_EN);
    ISP_MGR_CTL_EN_P2_T::getInstance(m_eSensorDev).setEnable_RMM2(bRMM_EN);

    // Register setting  Notice: RMM_IDX doesn't exist in HW, so m_u4RegInfoNum-1
    writeRegs(static_cast<RegInfo_T*>(m_pRegInfo), (m_u4RegInfoNum-1), pReg);

    dumpRegInfo("RMM2");

    return  MTRUE;

}

}

