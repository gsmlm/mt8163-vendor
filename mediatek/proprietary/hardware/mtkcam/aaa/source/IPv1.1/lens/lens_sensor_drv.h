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
/*
** $Log: lens_sensor_drv.h $
 *
*/

#ifndef _LENS_SENSOR_DRV_H_
#define _LENS_SENSOR_DRV_H_

#include <utils/threads.h>

using namespace android;

extern "C" {
#include <pthread.h>
#include <semaphore.h>
}


/*******************************************************************************
*
********************************************************************************/
class LensSensorDrv : public MCUDrv
{
private:    //// Instanciation outside is disallowed.
    /////////////////////////////////////////////////////////////////////////
    //
    // LensSensorDrv () -
    //! \brief
    //
    /////////////////////////////////////////////////////////////////////////
    LensSensorDrv();

    /////////////////////////////////////////////////////////////////////////
    //
    // ~LensSensorDrv () -
    //! \brief
    //
    /////////////////////////////////////////////////////////////////////////
    virtual ~LensSensorDrv();

public:     //// Interfaces
    /////////////////////////////////////////////////////////////////////////
    //
    /////////////////////////////////////////////////////////////////////////
    static MCUDrv* getInstance();

    /////////////////////////////////////////////////////////////////////////
    //
    /////////////////////////////////////////////////////////////////////////
    virtual void destroyInstance();

    /////////////////////////////////////////////////////////////////////////
    //
    // init () -
    //! \brief
    //
    /////////////////////////////////////////////////////////////////////////
    virtual int init(unsigned int a_u4CurrSensorDev);

    /////////////////////////////////////////////////////////////////////////
    //
    // uninit () -
    //! \brief
    //
    /////////////////////////////////////////////////////////////////////////
    virtual int uninit(unsigned int a_u4CurrSensorDev);

    /////////////////////////////////////////////////////////////////////////
    //
    // moveMCU () -
    //! \brief
    //
    /////////////////////////////////////////////////////////////////////////
    virtual int moveMCU(int a_i4FocusPos, unsigned int a_u4CurrSensorDev);

    /////////////////////////////////////////////////////////////////////////
    //
    // getMCUInfo () -
    //! \brief
    //
    /////////////////////////////////////////////////////////////////////////
    virtual int  getMCUInfo(mcuMotorInfo *a_pMotorInfo, unsigned int a_u4CurrSensorDev);

    /////////////////////////////////////////////////////////////////////////
    //
    // setMCUInfPos () -
    //! \brief
    //
    /////////////////////////////////////////////////////////////////////////
    virtual int setMCUInfPos(int a_i4FocusPos, unsigned int a_u4CurrSensorDev);

    /////////////////////////////////////////////////////////////////////////
    //
    // setMCUMacroPos () -
    //! \brief
    //
    /////////////////////////////////////////////////////////////////////////
    virtual int setMCUMacroPos(int a_i4FocusPos, unsigned int a_u4CurrSensorDev);

    /////////////////////////////////////////////////////////////////////////
    //
    // getMCUCalPos () -
    //! \brief
    //
    /////////////////////////////////////////////////////////////////////////
    virtual int getMCUCalPos(mcuMotorCalPos *a_pMotorCalPos,unsigned int a_u4CurrSensorDev );

    /////////////////////////////////////////////////////////////////////////
    //
    // setMCUParam () -
    //! \brief
    //
    /////////////////////////////////////////////////////////////////////////
    virtual int setMCUParam(int a_CmdId, int a_Param,unsigned int a_u4CurrSensorDev );

private:
    //
    int             m_fdMCU_main;
    int             m_fdMCU_main2;
    int             m_fdMCU_sub;
    int             m_userCnt_main;
    int             m_userCnt_main2;
    int             m_userCnt_sub;
    mutable Mutex   mLock;

    unsigned long             m_i4FocusPos_main;
    unsigned long             m_i4FocusPos_main2;
    unsigned long             m_i4FocusPos_sub;

};

#endif  //  _LENS_DRV_H_

