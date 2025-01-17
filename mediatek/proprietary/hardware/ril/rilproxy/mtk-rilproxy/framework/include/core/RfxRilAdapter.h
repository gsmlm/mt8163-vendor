/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 *
 * MediaTek Inc. (C) 2010. All rights reserved.
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
/*
 * RfxRilAdapter.h
 *
 *  Created on: 2015/7/22
 *      Author: MTK08471
 *
 *  RIL Adapter prototype
 */

#ifndef RFX_RIL_ADAPTER_H_
#define RFX_RIL_ADAPTER_H_

#include "RfxObject.h"
#include "RfxMessage.h"
#include "RfxVariant.h"
#include "RfxStatusDefs.h"
#include "RfxDefs.h"
#include "RfxDispatchThread.h"
#include "RfxLog.h"

using android::Parcel;
using android::Vector;

///// GSM RIL Includes
//// #include "ril_commands.h"
//extern "C" CommandInfo s_commands[];
//// #include "mtk_ril_commands.h"
//extern "C" CommandInfo s_mtk_commands[];
//// #include "ril_unsol_commands.h"
//extern "C" UnsolResponseInfo s_unsolResponses[];
//// #include "mtk_ril_unsol_commands.h"
//extern "C" static UnsolResponseInfo s_mtk_unsolResponses[];

/// C2K RIL Includes

class RfxRilAdapter : public RfxObject {

    RFX_DECLARE_CLASS(RfxRilAdapter);
    RFX_OBJ_DECLARE_SINGLETON_CLASS(RfxRilAdapter);

private:

    RfxRilAdapter();

    virtual ~RfxRilAdapter();

private:
    static int sim_count;

    pthread_mutex_t socket_1_mutex[RADIO_TECH_GROUP_NUM];
    pthread_mutex_t socket_2_mutex[RADIO_TECH_GROUP_NUM];
    int socket_1_fds[RADIO_TECH_GROUP_NUM]; // reserve for slot 0
    int socket_2_fds[RADIO_TECH_GROUP_NUM]; // reserve for slot 1

    pthread_mutex_t sap_socket_gsm_mutex[SIM_COUNT];
    pthread_mutex_t sap_socket_c2k_mutex[SIM_COUNT];
    pthread_mutex_t sap_socket_bt_mutex[SIM_COUNT];
    int socket_sap_gsm_fds[SIM_COUNT];
    int socket_sap_c2k_fds[SIM_COUNT];
    int socket_sap_bt_fds[SIM_COUNT];

    // a queue for ril request
    pthread_mutex_t request_queue_gsm_mutex[SIM_COUNT];
    pthread_mutex_t request_queue_c2k_mutex;
    Vector<sp<RfxMessage>> request_queue_gsm_1;
    Vector<sp<RfxMessage>> request_queue_gsm_2;
    Vector<sp<RfxMessage>> request_queue_c2k;

    bool requestToRildX(const sp<RfxMessage>& message);

    // request queue related functions
    bool isRequestQueueEmpty(int slotId, RILD_RadioTechnology_Group group);
    bool addRequestQueue(int slotId, RILD_RadioTechnology_Group group, const sp<RfxMessage>& message);
    bool dispatchRequestQueue(int slotId, RILD_RadioTechnology_Group group);
    void clearRequestQueue(int slotId, RILD_RadioTechnology_Group group);

    void registerSocketStateListener();
    void unregisterSocketStateListener();

public:

    void initSocketNotifyByFwk();

    bool setSocket(int slotId, RILD_RadioTechnology_Group group, int fd);
    bool switchC2kSocket(int targetSlotId);
    bool closeSocket(int slotId, RILD_RadioTechnology_Group group);

    bool requestToRild(const sp<RfxMessage>& message);
    bool responseToRilj(const sp<RfxMessage>& message);

    bool setSapSocket(RIL_SOCKET_ID socketId, RILD_RadioTechnology_Group group, int fd);
    bool sendSapMessageToRild(void *data, int datalen, RIL_SOCKET_ID socketId);

    void onSocketStateChanged(RfxStatusKeyEnum key, RfxVariant old_value, RfxVariant value);
    void clearAllRequestQueue();
};


class RfxRilAdapterUtils {

private:
    RfxRilAdapterUtils();

    virtual ~RfxRilAdapterUtils();

public:

    static Parcel* extractResponse(uint8_t* buf, int buflen);
    static RILD_RadioTechnology_Group choiceDestViaCurrCardType(int slotId);
};

#endif /* RFX_RIL_ADAPTER_H_ */
