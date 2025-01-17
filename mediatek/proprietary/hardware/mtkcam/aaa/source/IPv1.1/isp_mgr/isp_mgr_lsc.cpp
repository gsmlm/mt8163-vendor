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
#define LOG_TAG "isp_mgr_lsc"

#ifndef ENABLE_MY_LOG
    #define ENABLE_MY_LOG       (1)
#endif

#include <cutils/properties.h>
#include <aaa_types.h>
#include <aaa_error_code.h>
#include <aaa_log.h>
//#include <mtkcam/iopipe/CamIO/INormalPipe.h>
//#include <mtkcam/imageio/ispio_stddef.h>
#include <isp_reg.h>
#include "isp_mgr.h"

namespace NSIspTuningv3
{

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// LSC
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
ISP_MGR_LSC_T&
ISP_MGR_LSC_T::
getInstance(ESensorDev_T const eSensorDev)
{
    switch (eSensorDev)
    {
    case ESensorDev_Main: //  Main Sensor
        return  ISP_MGR_LSC_DEV<ESensorDev_Main>::getInstance();
    case ESensorDev_MainSecond: //  Main Second Sensor
        return  ISP_MGR_LSC_DEV<ESensorDev_MainSecond>::getInstance();
    case ESensorDev_Sub: //  Sub Sensor
        return  ISP_MGR_LSC_DEV<ESensorDev_Sub>::getInstance();
    default:
        MY_ERR("eSensorDev = %d", eSensorDev);
        return  ISP_MGR_LSC_DEV<ESensorDev_Main>::getInstance();
    }
}

MVOID
ISP_MGR_LSC_T::
enableLsc(MBOOL enable)
{
    MY_LOG_IF(ENABLE_MY_LOG,"%s %d\n", __FUNCTION__, enable);
    m_fgOnOff = enable;
}

MBOOL
ISP_MGR_LSC_T::
isEnable(void)
{
    return m_fgOnOff;
}

template <>
ISP_MGR_LSC_T&
ISP_MGR_LSC_T::
put(ISP_NVRAM_LSC_T const& rParam)
{
    MY_LOG_IF(ENABLE_MY_LOG, "[%s\n", __FUNCTION__);

//    PUT_REG_INFO(CAM_LSCI_BASE_ADDR, baseaddr);
    PUT_REG_INFO(CAM_LSC_CTL1, ctl1);
    PUT_REG_INFO(CAM_LSC_CTL2, ctl2);
    PUT_REG_INFO(CAM_LSC_CTL3, ctl3);
    PUT_REG_INFO(CAM_LSC_LBLOCK, lblock);
    PUT_REG_INFO(CAM_LSC_RATIO, ratio);
//    PUT_REG_INFO(CAM_LSC_GAIN_TH, gain_th);

    return  (*this);
}

ISP_MGR_LSC_T&
ISP_MGR_LSC_T::
putAddr(MUINT32 u4BaseAddr)
{
    MY_LOG_IF(ENABLE_MY_LOG, "[%s] eSensorDev(%d), u4BaseAddr(0x%08x)", __FUNCTION__, m_eSensorDev, u4BaseAddr);
    REG_INFO_VALUE(CAM_LSCI_BASE_ADDR) = u4BaseAddr;
    return  (*this);
}

template <>
ISP_MGR_LSC_T&
ISP_MGR_LSC_T::
get(ISP_NVRAM_LSC_T& rParam)
{
    MY_LOG_IF(ENABLE_MY_LOG, "[%s]\n", __FUNCTION__);

//    GET_REG_INFO(CAM_LSCI_BASE_ADDR, baseaddr);
    GET_REG_INFO(CAM_LSC_CTL1, ctl1);
    GET_REG_INFO(CAM_LSC_CTL2, ctl2);
    GET_REG_INFO(CAM_LSC_CTL3, ctl3);
    GET_REG_INFO(CAM_LSC_LBLOCK, lblock);
    GET_REG_INFO(CAM_LSC_RATIO, ratio);
//    GET_REG_INFO(CAM_LSC_GAIN_TH, gain_th);

    return  (*this);
}

MUINT32
ISP_MGR_LSC_T::
getAddr()
{
    MUINT32 u4Addr = REG_INFO_VALUE(CAM_LSCI_BASE_ADDR);
    MY_LOG_IF(ENABLE_MY_LOG, "[%s] u4BaseAddr(0x%08x)\n", __FUNCTION__, u4Addr);
    return u4Addr;
}

MBOOL
ISP_MGR_LSC_T::
reset()
{
    return MTRUE;
}

MBOOL
ISP_MGR_LSC_T::
putBuf(NSIspTuning::ILscBuf& rBuf)
{
    ISP_NVRAM_LSC_T rLscCfg;
    ::memset(&rLscCfg, 0, sizeof(ISP_NVRAM_LSC_T));
    ILscBuf::Config rCfg = rBuf.getConfig();
    MUINT32 u4Addr = rBuf.getPhyAddr();
    rBuf.validate();
    rLscCfg.ctl2.bits.LSC_SDBLK_XNUM        = rCfg.i4BlkX;
    rLscCfg.ctl3.bits.LSC_SDBLK_YNUM        = rCfg.i4BlkY;
    rLscCfg.ctl2.bits.LSC_SDBLK_WIDTH       = rCfg.i4BlkW;
    rLscCfg.ctl3.bits.LSC_SDBLK_HEIGHT      = rCfg.i4BlkH;
    rLscCfg.lblock.bits.LSC_SDBLK_lWIDTH    = rCfg.i4BlkLastW;
    rLscCfg.lblock.bits.LSC_SDBLK_lHEIGHT   = rCfg.i4BlkLastH;
    rLscCfg.ratio.val = 0x20202020;
    put(rLscCfg);
    putAddr(u4Addr);
    m_FD = rBuf.getFD();
    return MTRUE;
}

#define LSC_DIRECT_ACCESS 0
#define EN_WRITE_REGS     0
MBOOL
ISP_MGR_LSC_T::
apply(EIspProfile_T eIspProfile, TuningMgr& rTuning, MINT32 i4SubsampleIdex)
{
    MBOOL fgOnOff = m_fgOnOff;

    MUINT32 u4XNum, u4YNum, u4Wd, u4Ht;
    MUINT32 LSCI_XSIZE, LSCI_YSIZE, LSCI_STRIDE;

    u4XNum = reinterpret_cast<ISP_CAM_LSC_CTL2_T*>(REG_INFO_VALUE_PTR(CAM_LSC_CTL2))->LSC_SDBLK_XNUM;
    u4YNum = reinterpret_cast<ISP_CAM_LSC_CTL3_T*>(REG_INFO_VALUE_PTR(CAM_LSC_CTL3))->LSC_SDBLK_YNUM;
    u4Wd = reinterpret_cast<ISP_CAM_LSC_CTL2_T*>(REG_INFO_VALUE_PTR(CAM_LSC_CTL2))->LSC_SDBLK_WIDTH;
    u4Ht = reinterpret_cast<ISP_CAM_LSC_CTL3_T*>(REG_INFO_VALUE_PTR(CAM_LSC_CTL3))->LSC_SDBLK_HEIGHT;

#if 0
    LSCI_XSIZE = (u4XNum+1)*4*128/8 - 1;
    LSCI_YSIZE = u4YNum;
    LSCI_STRIDE = (LSCI_XSIZE+1);
#else
    LSCI_XSIZE = (u4XNum+1)*4*128/8;
    LSCI_YSIZE = u4YNum+1;
    LSCI_STRIDE = (LSCI_XSIZE);
#endif

    REG_INFO_VALUE(CAM_LSCI_OFST_ADDR)  = 0;
    REG_INFO_VALUE(CAM_LSCI_XSIZE)      = LSCI_XSIZE;
    REG_INFO_VALUE(CAM_LSCI_YSIZE)      = LSCI_YSIZE;
    REG_INFO_VALUE(CAM_LSCI_STRIDE)     = LSCI_STRIDE;
    REG_INFO_VALUE(CAM_LSC_CTL1)        = 0x30000000;
//    REG_INFO_VALUE(CAM_LSC_GAIN_TH)     = 0x03F00000;

    rTuning.updateEngineFD(eTuningMgrFunc_LSC, 0, m_FD);
    rTuning.updateEngine(eTuningMgrFunc_LSC, fgOnOff, i4SubsampleIdex);

    // TOP
    TUNING_MGR_WRITE_BITS_CAM((&rTuning), CAM_CTL_EN, LSC_EN, fgOnOff, i4SubsampleIdex);
    TUNING_MGR_WRITE_BITS_CAM((&rTuning), CAM_CTL_DMA_EN, LSCI_EN, fgOnOff, i4SubsampleIdex);

    ISP_MGR_CTL_EN_P1_T::getInstance(m_eSensorDev).setEnable_LSC(fgOnOff);

    // Register setting
    rTuning.tuningMgrWriteRegs(
        static_cast<TUNING_MGR_REG_IO_STRUCT*>(m_pRegInfo),
        m_u4RegInfoNum, i4SubsampleIdex);

    dumpRegInfo("LSC");

    return  MTRUE;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// LSC2
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
ISP_MGR_LSC2_T&
ISP_MGR_LSC2_T::
getInstance(ESensorDev_T const eSensorDev)
{
    switch (eSensorDev)
    {
    case ESensorDev_Main: //  Main Sensor
        return  ISP_MGR_LSC2_DEV<ESensorDev_Main>::getInstance();
    case ESensorDev_MainSecond: //  Main Second Sensor
        return  ISP_MGR_LSC2_DEV<ESensorDev_MainSecond>::getInstance();
    case ESensorDev_Sub: //  Sub Sensor
        return  ISP_MGR_LSC2_DEV<ESensorDev_Sub>::getInstance();
    default:
        MY_ERR("eSensorDev = %d", eSensorDev);
        return  ISP_MGR_LSC2_DEV<ESensorDev_Main>::getInstance();
    }
}

MVOID
ISP_MGR_LSC2_T::
enableLsc(MBOOL enable)
{
    MY_LOG_IF(ENABLE_MY_LOG,"[%s2] %d", __FUNCTION__, enable);
    m_fgOnOff = enable;
}

MBOOL
ISP_MGR_LSC2_T::
isEnable(void)
{
    return m_fgOnOff;
}

template <>
ISP_MGR_LSC2_T&
ISP_MGR_LSC2_T::
put(ISP_NVRAM_LSC_T const& rParam)
{
    MY_LOG_IF(ENABLE_MY_LOG, "[%s2]", __FUNCTION__);

//    PUT_REG_INFO(DIP_X_DEPI_BASE_ADDR, baseaddr);
    PUT_REG_INFO(DIP_X_LSC2_CTL1, ctl1);
    PUT_REG_INFO(DIP_X_LSC2_CTL2, ctl2);
    PUT_REG_INFO(DIP_X_LSC2_CTL3, ctl3);
    PUT_REG_INFO(DIP_X_LSC2_LBLOCK, lblock);
    PUT_REG_INFO(DIP_X_LSC2_RATIO, ratio);
//    PUT_REG_INFO(DIP_X_LSC2_GAIN_TH, gain_th);

    return  (*this);
}

ISP_MGR_LSC2_T&
ISP_MGR_LSC2_T::
putAddr(MUINT32 u4BaseAddr)
{
    MY_LOG_IF(ENABLE_MY_LOG, "[%s2] eSensorDev(%d), u4BaseAddr(0x%08x)", __FUNCTION__, m_eSensorDev, u4BaseAddr);
    REG_INFO_VALUE(DIP_X_DEPI_BASE_ADDR) = u4BaseAddr;
    return  (*this);
}

template <>
ISP_MGR_LSC2_T&
ISP_MGR_LSC2_T::
get(ISP_NVRAM_LSC_T& rParam)
{
    MY_LOG_IF(ENABLE_MY_LOG, "[%s2]\n", __FUNCTION__);

//    GET_REG_INFO(DIP_X_DEPI_BASE_ADDR, baseaddr);
    GET_REG_INFO(DIP_X_LSC2_CTL1, ctl1);
    GET_REG_INFO(DIP_X_LSC2_CTL2, ctl2);
    GET_REG_INFO(DIP_X_LSC2_CTL3, ctl3);
    GET_REG_INFO(DIP_X_LSC2_LBLOCK, lblock);
    GET_REG_INFO(DIP_X_LSC2_RATIO, ratio);
//    GET_REG_INFO(DIP_X_LSC2_GAIN_TH, gain_th);

    return  (*this);
}

template <>
MBOOL
ISP_MGR_LSC2_T::
get(ISP_NVRAM_LSC_T& rParam, const dip_x_reg_t* pReg) const
{
    if (pReg)
    {
        GET_REG_INFO_BUF(DIP_X_LSC2_CTL1, ctl1);
        GET_REG_INFO_BUF(DIP_X_LSC2_CTL2, ctl2);
        GET_REG_INFO_BUF(DIP_X_LSC2_CTL3, ctl3);
        GET_REG_INFO_BUF(DIP_X_LSC2_LBLOCK, lblock);
        GET_REG_INFO_BUF(DIP_X_LSC2_RATIO, ratio);
    }
    return MTRUE;
}

MUINT32
ISP_MGR_LSC2_T::
getAddr()
{
    MUINT32 u4Addr = REG_INFO_VALUE(DIP_X_DEPI_BASE_ADDR);
    MY_LOG_IF(ENABLE_MY_LOG, "[%s2] u4BaseAddr(0x%08x)\n", __FUNCTION__, u4Addr);
    return u4Addr;
}

MBOOL
ISP_MGR_LSC2_T::
reset()
{
    return MTRUE;
}

MBOOL
ISP_MGR_LSC2_T::
putBuf(NSIspTuning::ILscBuf& rBuf)
{
    ISP_NVRAM_LSC_T rLscCfg;
    ::memset(&rLscCfg, 0, sizeof(ISP_NVRAM_LSC_T));
    ILscBuf::Config rCfg = rBuf.getConfig();
    MUINT32 u4Addr = rBuf.getPhyAddr();
    rBuf.validate();
    rLscCfg.ctl2.bits.LSC_SDBLK_XNUM        = rCfg.i4BlkX;
    rLscCfg.ctl3.bits.LSC_SDBLK_YNUM        = rCfg.i4BlkY;
    rLscCfg.ctl2.bits.LSC_SDBLK_WIDTH       = rCfg.i4BlkW;
    rLscCfg.ctl3.bits.LSC_SDBLK_HEIGHT      = rCfg.i4BlkH;
    rLscCfg.lblock.bits.LSC_SDBLK_lWIDTH    = rCfg.i4BlkLastW;
    rLscCfg.lblock.bits.LSC_SDBLK_lHEIGHT   = rCfg.i4BlkLastH;
    rLscCfg.ratio.val = 0x20202020;
    put(rLscCfg);
    putAddr(u4Addr);
    return MTRUE;
}

MBOOL
ISP_MGR_LSC2_T::
apply(EIspProfile_T eIspProfile, dip_x_reg_t* pReg)
{
    MBOOL fgOnOff = m_fgOnOff;

    MUINT32 u4XNum, u4YNum, u4Wd, u4Ht;
    MUINT32 LSCI_XSIZE, LSCI_YSIZE, LSCI_STRIDE;

    u4XNum = reinterpret_cast<ISP_CAM_LSC_CTL2_T*>(REG_INFO_VALUE_PTR(DIP_X_LSC2_CTL2))->LSC_SDBLK_XNUM;
    u4YNum = reinterpret_cast<ISP_CAM_LSC_CTL3_T*>(REG_INFO_VALUE_PTR(DIP_X_LSC2_CTL3))->LSC_SDBLK_YNUM;
    u4Wd = reinterpret_cast<ISP_CAM_LSC_CTL2_T*>(REG_INFO_VALUE_PTR(DIP_X_LSC2_CTL2))->LSC_SDBLK_WIDTH;
    u4Ht = reinterpret_cast<ISP_CAM_LSC_CTL3_T*>(REG_INFO_VALUE_PTR(DIP_X_LSC2_CTL3))->LSC_SDBLK_HEIGHT;
#if 0
    LSCI_XSIZE = (u4XNum+1)*4*128/8 - 1;
    LSCI_YSIZE = u4YNum;
    LSCI_STRIDE = (LSCI_XSIZE+1);
#else
    LSCI_XSIZE = (u4XNum+1)*4*128/8;
    LSCI_YSIZE = u4YNum+1;
    LSCI_STRIDE = (LSCI_XSIZE);
#endif
    REG_INFO_VALUE(DIP_X_DEPI_OFST_ADDR)  = 0;
    REG_INFO_VALUE(DIP_X_DEPI_XSIZE)      = LSCI_XSIZE;
    REG_INFO_VALUE(DIP_X_DEPI_YSIZE)      = LSCI_YSIZE;
    REG_INFO_VALUE(DIP_X_DEPI_STRIDE)     = LSCI_STRIDE;
    REG_INFO_VALUE(DIP_X_LSC2_CTL1)        = 0x30000000;
//    REG_INFO_VALUE(DIP_X_LSC2_GAIN_TH)     = 0x03F00000;

    ESoftwareScenario eSwScn = static_cast<ESoftwareScenario>(m_rIspDrvScenario[eIspProfile]);

    // TOP
    ISP_WRITE_ENABLE_BITS(pReg, DIP_X_CTL_RGB_EN, LSC2_EN, fgOnOff);
    ISP_WRITE_ENABLE_BITS(pReg, DIP_X_CTL_DMA_EN, DEPI_EN, fgOnOff);
    ISP_MGR_CTL_EN_P2_T::getInstance(m_eSensorDev).setEnable_LSC2(fgOnOff);

    // Register setting
    writeRegs(static_cast<RegInfo_T*>(m_pRegInfo), m_u4RegInfoNum, pReg);

    dumpRegInfo("LSC2");

    return  MTRUE;
}

}
