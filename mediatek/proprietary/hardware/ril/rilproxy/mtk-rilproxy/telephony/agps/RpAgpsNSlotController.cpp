/***************************************************************************** 
 * Include
 *****************************************************************************/
#include "RpAgpsNSlotController.h"
#include "RpAgpsSlotController.h"
#include "RpAgpsThread.h"
#include "RpAgpsdAdapter.h"
#include "RpAgpsHandler.h"
#include "RpAgpsLog.h"
#include <cutils/properties.h>
#include <string.h>
#include <stdlib.h>
#include "misc.h"
#include "ril.h"

/***************************************************************************** 
 * Name space declaration
 *****************************************************************************/
using ::android::Parcel;

/***************************************************************************** 
 * Class RpAgpsNSlotController
 *****************************************************************************/

RFX_IMPLEMENT_CLASS("RpAgpsNSlotController",
        RpAgpsNSlotController, RfxController);


RpAgpsNSlotController::RpAgpsNSlotController() :
    m_agpsdAdapter(NULL),
    m_agpsThread(NULL),
    m_networkType(NETWORK_TYPE_UNKNOWN),
    m_state(OUT_OF_SERVICE),
    m_dataEnabledStatus(DATA_ENABLED_ON_GSM),
    m_testMode(false),
    m_mockDefaultDataSlot(0) {
    AGPS_LOGD("RpAgpsNSlotController::Constructor 0x%x", this);
}


RpAgpsNSlotController::~RpAgpsNSlotController() {
    AGPS_LOGD("RpAgpsNSlotController::Destructor %x0x", this);
}


void RpAgpsNSlotController::onInit() {
    RfxController::onInit();
    AGPS_LOGD("RpAgpsNSlotController::onInit slotID = %d", getSlotId());
    m_agpsdAdapter = RFX_OBJ_GET_INSTANCE(RpAgpsdAdapter);
    m_agpsThread = RpAgpsThread::create();
    registerServiceStateChanged();
}


void RpAgpsNSlotController::onDeinit() {
    AGPS_LOGD("RpAgpsNSlotController::onDeinit");
    unRegisterServiceStateChanged();
    RFX_OBJ_CLOSE_INSTANCE(RpAgpsdAdapter);
    m_agpsThread->requestExit();
    m_agpsThread->getLooper()->wake();
    m_agpsThread=NULL;
    RfxController::onDeinit();
}


sp<RpAgpsThread>& RpAgpsNSlotController::getAgpsThread() {
    return m_agpsThread;
}


void RpAgpsNSlotController::registerServiceStateChanged() {
    for (int i = 0; i < RFX_SLOT_COUNT; i++) {
        getStatusManager(i)->registerStatusChangedEx(
                RFX_STATUS_KEY_SERVICE_STATE,
                RfxStatusChangeCallbackEx(this,
                        &RpAgpsNSlotController::onServiceStateChanged));
    }
}


void RpAgpsNSlotController::unRegisterServiceStateChanged() {
    for (int i = 0; i < RFX_SLOT_COUNT; i++) {
        getStatusManager(i)->unRegisterStatusChangedEx(
                RFX_STATUS_KEY_SERVICE_STATE,
                RfxStatusChangeCallbackEx(this,
                        &RpAgpsNSlotController::onServiceStateChanged));
    }
}


RpAgpsNSlotController::NetworkType RpAgpsNSlotController::convertRadioTech(
        int radioTech) {
    switch (radioTech) {
        case RADIO_TECH_GPRS:
            return NETWORK_TYPE_GPRS;
        case RADIO_TECH_EDGE:
            return NETWORK_TYPE_EDGE;
        case RADIO_TECH_UMTS:
            return NETWORK_TYPE_UMTS;
        case RADIO_TECH_IS95A:
        case RADIO_TECH_IS95B:
            return NETWORK_TYPE_CDMA;
        case RADIO_TECH_1xRTT:
            return NETWORK_TYPE_1xRTT;
        case RADIO_TECH_EVDO_0:
            return NETWORK_TYPE_EVDO_0;
        case RADIO_TECH_EVDO_A:
            return NETWORK_TYPE_EVDO_A;
        case RADIO_TECH_HSDPA:
            return NETWORK_TYPE_HSDPA;
        case RADIO_TECH_HSUPA:
            return NETWORK_TYPE_HSUPA;
        case RADIO_TECH_HSPA:
            return NETWORK_TYPE_HSPA;
        case RADIO_TECH_EVDO_B:
            return NETWORK_TYPE_EVDO_B;
        case RADIO_TECH_EHRPD:
            return NETWORK_TYPE_EHRPD;
        case RADIO_TECH_LTE:
            return NETWORK_TYPE_LTE;
        case RADIO_TECH_HSPAP:
            return NETWORK_TYPE_HSPAP;
        case RADIO_TECH_GSM:
            return NETWORK_TYPE_GSM;
        default:
            return NETWORK_TYPE_UNKNOWN;
    }
}


RpAgpsNSlotController::ServiceState RpAgpsNSlotController::convertServiceState(
        int regState) {
    if (RfxNwServiceState::isInService(regState)) {
        return IN_SERVICE;
    } else {
        return OUT_OF_SERVICE;
    }
}


void RpAgpsNSlotController::onServiceStateChanged(
    int slotId, RfxStatusKeyEnum key,RfxVariant oldValue,RfxVariant newValue) {
    RFX_ASSERT(key == RFX_STATUS_KEY_SERVICE_STATE);
    RFX_UNUSED(oldValue);
    RfxNwServiceState nwSS = newValue.asServiceState();
    AGPS_LOGD("RpAgpsNSlotController::onServiceStateChanged %s",
            nwSS.toString().string());
    if ((slotId + 1) == getDefaultDataSlotId()) {
        RpAgpsNSlotController::NetworkType type;
        type = convertRadioTech(nwSS.getRilDataRadioTech());
        if (type != m_networkType) {
            sendNetworkType(type);
        }
        m_networkType = type;
    }
    if (slotId == getCDMASlotId()) {
        ServiceState state = convertServiceState(nwSS.getRilVoiceRegState());
        if (state != m_state) {
            sendC2KMDStatus(state);
        }
        m_state = state;
    }
    int status = getCurrentDataEnabledStatus();
    if (status != m_dataEnabledStatus) {
        sendDataEnabledStatus(status);
        m_dataEnabledStatus = status;
    }
}


void RpAgpsNSlotController::sendC2KMDStatus(int state) {
    AGPS_LOGD("RpAgpsNSlotController::sendC2KMDStatus %d", state);
    Parcel *p = new Parcel();
    p->writeInt32(state);
    sp<RpAgpsMessage> msg =
            RpAgpsMessage::obtainMessage(EVENT_AGPS_CDMA_PHONE_STATUS, p);
    sp<RpAgpsWorkingThreadHandler> handler = new RpAgpsWorkingThreadHandler(msg);
    handler->sendMessage(m_agpsThread->getLooper());
}


void RpAgpsNSlotController::sendNetworkType(int type) {
    AGPS_LOGD("RpAgpsNSlotController::sendNetworkType %d", type);
    Parcel *p = new Parcel();
    p->writeInt32(type);
    sp<RpAgpsMessage> msg =
            RpAgpsMessage::obtainMessage(EVENT_AGPS_NETWORK_TYPE, p);
    sp<RpAgpsWorkingThreadHandler> handler = new RpAgpsWorkingThreadHandler(msg);
    handler->sendMessage(m_agpsThread->getLooper());
}


int RpAgpsNSlotController::getCurrentDataEnabledStatus() {
    int status;
    if (getCDMASlotId() == RFX_SLOT_ID_UNKNOWN) {
        status  = DATA_ENABLED_ON_GSM;
    } else {
        status = ((getCDMASlotId() + 1) == getDefaultDataSlotId()) ?
            DATA_ENABLED_ON_CDMA_LTE : DATA_ENABLED_ON_GSM;
    }
    return status;
}


void RpAgpsNSlotController::sendDataEnabledStatus(int status) {
    Parcel *p = new Parcel();

    AGPS_LOGD("RpAgpsNSlotController::sendDataEnabledStatus %d", status);
    p->writeInt32(status);
    sp<RpAgpsMessage> msg =
            RpAgpsMessage::obtainMessage(EVENT_AGPS_MOBILE_DATA_STATUS, p);
    sp<RpAgpsWorkingThreadHandler> handler = new RpAgpsWorkingThreadHandler(msg);
    handler->sendMessage(m_agpsThread->getLooper());
}


void RpAgpsNSlotController::onHandleAgpsMessage(sp<RpAgpsMessage> & message) {
    AGPS_LOGD("RpAgpsNSlotController::onHandleAgpsMessage %d",
        message->getId());
    switch (message->getId()) {
        case EVENT_UPDATE_STATE_TO_AGPSD:
            sendDataEnabledStatus(m_dataEnabledStatus);
            sendNetworkType(m_networkType);
            sendC2KMDStatus(m_state);
            break;

        case EVENT_SET_APN_RESULT:
        {
            RpAgpsSlotController *ctrl =
                (RpAgpsSlotController *)findController(
                    getCDMASlotId(),
                    RFX_OBJ_CLASS_INFO(RpAgpsSlotController));
            if (ctrl != NULL) {
                Parcel *p = message->getParcel();
                p->setDataPosition(0);
                int state = p->readInt32();
                bool result = state ? true : false;
                ctrl->onApnSetResult(result);
            }
            break;
        }

        default:
            break;
    }
}


int RpAgpsNSlotController::getDefaultDataSlotId() {
    if (m_testMode) {
        return m_mockDefaultDataSlot;
    }
    int i = 0;
    char iccid[PROPERTY_VALUE_MAX] = {0};
    char defaultData[PROPERTY_VALUE_MAX] = {0};
    char PROPERTY_ICCID_SIM[4][25] = {
        "ril.iccid.sim1",
        "ril.iccid.sim2",
        "ril.iccid.sim3",
        "ril.iccid.sim4",
    };
    property_get("persist.radio.data.iccid", defaultData, "");
    if (strlen(defaultData) == 0 || strcmp("N/A", defaultData) == 0) {
        return 0;
    }

    for (i = 0; i < RFX_SLOT_COUNT; i++) {
        property_get(PROPERTY_ICCID_SIM[i], iccid, "");
        if (strlen(iccid) == 0 || strcmp("N/A", iccid) == 0) {
            continue;
        }
        if (strcmp(iccid, defaultData) == 0) {
            return (i + 1);
        }
    }
    return 0;
}


int RpAgpsNSlotController::getCDMASlotId() {
    RfxStatusManager *statusManager = getStatusManager();
    int slotId = statusManager->getIntValue(RFX_STATUS_KEY_CDMA_SOCKET_SLOT,
                         RFX_SLOT_ID_UNKNOWN);
    AGPS_LOGD("RpAgpsSlotController::getCDMASlotId slotId = %d", slotId);
    return slotId;
}