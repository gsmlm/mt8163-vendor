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
#ifndef _ISP_MGR_SEEE_H_
#define _ISP_MGR_SEEE_H_

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  SEEE (SE + EE)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef class ISP_MGR_SEEE : public ISP_MGR_BASE_T
{
    typedef ISP_MGR_SEEE    MyType;
private:
    MBOOL m_bEnable;
    MBOOL m_bCCTEnable;
    MUINT32 m_u4StartAddr; // for debug purpose: CAM+0x0AA0

    enum
    {


        ERegInfo_DIP_X_SEEE_CTRL,
        ERegInfo_DIP_X_SEEE_CLIP_CTRL_1,
        ERegInfo_DIP_X_SEEE_CLIP_CTRL_2,
        ERegInfo_DIP_X_SEEE_CLIP_CTRL_3,
        ERegInfo_DIP_X_SEEE_BLND_CTRL_1,
        ERegInfo_DIP_X_SEEE_BLND_CTRL_2,
        ERegInfo_DIP_X_SEEE_GN_CTRL,
        ERegInfo_DIP_X_SEEE_LUMA_CTRL_1,
        ERegInfo_DIP_X_SEEE_LUMA_CTRL_2,
        ERegInfo_DIP_X_SEEE_LUMA_CTRL_3,
        ERegInfo_DIP_X_SEEE_LUMA_CTRL_4,
        ERegInfo_DIP_X_SEEE_SLNK_CTRL_1,
        ERegInfo_DIP_X_SEEE_SLNK_CTRL_2,
        ERegInfo_DIP_X_SEEE_GLUT_CTRL_1,
        ERegInfo_DIP_X_SEEE_GLUT_CTRL_2,
        ERegInfo_DIP_X_SEEE_GLUT_CTRL_3,
        ERegInfo_DIP_X_SEEE_GLUT_CTRL_4,
        ERegInfo_DIP_X_SEEE_GLUT_CTRL_5,
        ERegInfo_DIP_X_SEEE_GLUT_CTRL_6,

        ERegInfo_DIP_X_SEEE_OUT_EDGE_CTRL,
        ERegInfo_DIP_X_SEEE_SE_Y_CTRL,
        ERegInfo_DIP_X_SEEE_SE_EDGE_CTRL_1,
        ERegInfo_DIP_X_SEEE_SE_EDGE_CTRL_2,
        ERegInfo_DIP_X_SEEE_SE_EDGE_CTRL_3,
        ERegInfo_DIP_X_SEEE_SE_SPECL_CTRL,
        ERegInfo_DIP_X_SEEE_SE_CORE_CTRL_1,
        ERegInfo_DIP_X_SEEE_SE_CORE_CTRL_2,
        ERegInfo_NUM
    };
    RegInfo_T m_rIspRegInfo[ERegInfo_NUM];

protected:
    ISP_MGR_SEEE(ESensorDev_T const eSensorDev)
        : ISP_MGR_BASE_T(m_rIspRegInfo, ERegInfo_NUM, m_u4StartAddr, eSensorDev)
        , m_bEnable(MTRUE)
        , m_bCCTEnable(MTRUE)
//        , m_u4StartAddr(REG_ADDR_P2(DIP_X_SEEE_SRK_CTRL))
    {
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_CTRL);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_CLIP_CTRL_1);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_CLIP_CTRL_2);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_CLIP_CTRL_3);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_BLND_CTRL_1);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_BLND_CTRL_2);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_GN_CTRL);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_LUMA_CTRL_1);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_LUMA_CTRL_2);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_LUMA_CTRL_3);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_LUMA_CTRL_4);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_SLNK_CTRL_1);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_SLNK_CTRL_2);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_GLUT_CTRL_1);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_GLUT_CTRL_2);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_GLUT_CTRL_3);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_GLUT_CTRL_4);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_GLUT_CTRL_5);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_GLUT_CTRL_6);

        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_OUT_EDGE_CTRL);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_SE_Y_CTRL);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_SE_EDGE_CTRL_1);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_SE_EDGE_CTRL_2);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_SE_EDGE_CTRL_3);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_SE_SPECL_CTRL);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_SE_CORE_CTRL_1);
        INIT_REG_INFO_ADDR_P2(DIP_X_SEEE_SE_CORE_CTRL_2);

    }

    virtual ~ISP_MGR_SEEE() {}

public:
    static MyType&  getInstance(ESensorDev_T const eSensorDev);

public: // Interfaces.

    template <class ISP_xxx_T>
    MyType& put(ISP_xxx_T const& rParam);

    template <class ISP_xxx_T>
    MyType& get(ISP_xxx_T & rParam);

    template <class ISP_xxx_T>
    MBOOL get(ISP_xxx_T & rParam, const dip_x_reg_t* pReg) const;

    MBOOL
    isEnable()
    {
        return m_bEnable;
    }

    MVOID
    setEnable(MBOOL bEnable)
    {
        m_bEnable = bEnable;
    }

    MBOOL
    isCCTEnable()
    {
        return m_bCCTEnable;
    }

    MVOID
    setCCTEnable(MBOOL bEnable)
    {
        m_bCCTEnable = bEnable;
    }

    MBOOL apply(EIspProfile_T eIspProfile, dip_x_reg_t* pReg);
} ISP_MGR_SEEE_T;

template <ESensorDev_T const eSensorDev>
class ISP_MGR_SEEE_DEV : public ISP_MGR_SEEE_T
{
public:
    static
    ISP_MGR_SEEE_T&
    getInstance()
    {
        static ISP_MGR_SEEE_DEV<eSensorDev> singleton;
        return singleton;
    }
    virtual MVOID destroyInstance() {}

    ISP_MGR_SEEE_DEV()
        : ISP_MGR_SEEE_T(eSensorDev)
    {}

    virtual ~ISP_MGR_SEEE_DEV() {}

};


#endif

