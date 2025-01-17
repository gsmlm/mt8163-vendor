#ifndef ANDROID_SPEECH_MESSENGER_ECCCI_H
#define ANDROID_SPEECH_MESSENGER_ECCCI_H

#include <pthread.h>

#include "AudioType.h"
#include "SpeechType.h"
#include "AudioUtility.h"

#include "SpeechBGSPlayer.h"
#include "SpeechPcm2way.h"
#include "SpeechMessengerInterface.h"


namespace android
{

class SpeechDriverLAD;

class SpeechMessengerECCCI : public SpeechMessengerInterface
{
    public:
        SpeechMessengerECCCI(modem_index_t modem_index, SpeechDriverLAD *pLad);
        virtual ~SpeechMessengerECCCI();

        virtual status_t    Initial();
        virtual status_t    Deinitial();

        virtual bool        A2MBufLock();
        virtual void        A2MBufUnLock();

        virtual status_t    WaitUntilModemReady();

        virtual ccci_buff_t InitCcciMailbox(uint16_t id, uint16_t param_16bit, uint32_t param_32bit);
        virtual status_t    SendMessageInQueue(ccci_buff_t ccci_buff);


        virtual uint16_t    GetM2AShareBufSyncWord(const ccci_buff_t &ccci_buff);
        virtual uint16_t    GetM2AShareBufDataType(const ccci_buff_t &ccci_buff);
        virtual uint16_t    GetM2AShareBufDataLength(const ccci_buff_t &ccci_buff);

        /**
         * get modem side modem function status
         */
        virtual bool        GetModemSideModemStatus(const modem_status_mask_t modem_status_mask) const;


        /**
         * check whether modem side get all necessary speech enhancement parameters here
         */
        virtual bool        CheckSpeechParamAckAllArrival();


        /**
         * check whether modem is ready. (if w/o SIM && phone_2 => modem sleep)
         */
        virtual bool        CheckModemIsReady();

        /**
         * check whether modem audio is ready from reset.
         */
        virtual bool        GetMDResetFlag();

        /**
         * set raw record type.
         */
        virtual status_t        SetPcmRecordType(record_type_t type_record);

    protected:
        SpeechMessengerECCCI() {}

        virtual char        GetModemCurrentStatus();

        virtual uint16_t    GetMessageID(const ccci_buff_t &ccci_buff);
        virtual uint16_t    GetMessageParam(const ccci_buff_t &ccci_buff);

        virtual uint16_t    GetMessageLength(const ccci_buff_t &ccci_buff);
        virtual uint16_t    GetMessageOffset(const ccci_buff_t &ccci_buff);
        virtual bool        CheckOffsetAndLength(const ccci_buff_t &ccci_buff);
        virtual uint16_t    GetPcmFreq(const uint16_t Idx_Freq);

        virtual ccci_message_ack_t JudgeAckOfMsg(const uint16_t message_id);

        virtual bool        IsModemFunctionOnOffMessage(const uint16_t message_id);

        virtual status_t    SendMessage(const ccci_buff_t &ccci_buff);
        virtual status_t    ReadMessage(ccci_buff_t &ccci_buff);
        virtual void         SendMsgFailErrorHandling(const ccci_buff_t &ccci_buff);

        virtual RingBuf     GetM2AUplinkRingBuffer(const ccci_buff_t &ccci_buff);
        virtual RingBuf     GetM2ARawPcmRingBuffer(const ccci_buff_t &ccci_buff);

        virtual status_t    CreateReadingThread();
        virtual status_t    CreateSendSphParaThread();

        static void        *CCCIReadThread(void *arg);
        static void        *SendSphParaThread(void *arg);


        // for message queue
        virtual uint32_t    GetQueueCount() const;
        virtual status_t    ConsumeMessageInQueue();
        virtual bool        MDReset_CheckMessageInQueue();
        virtual void        MDReset_FlushMessageInQueue();

        virtual void        ResetSpeechParamAckCount();
        virtual void        AddSpeechParamAckCount(speech_param_ack_t type);


        /**
         * set/reset AP side modem function status
         */
        virtual void        SetModemSideModemStatus(const modem_status_mask_t modem_status_mask);
        virtual void        ResetModemSideModemStatus(const modem_status_mask_t modem_status_mask);

        // lock
        virtual bool SpeechParamLock();
        virtual void SpeechParamUnLock();

        virtual void GetRFInfo(void);
        virtual void SetRFInfo(char mRFIdx, uint16_t mRfData);
        virtual void ResetRFInfo(void);
        status_t SetNWCodecInfo(const ccci_buff_t &ccci_buff);

        modem_index_t mModemIndex;
        SpeechDriverLAD *mLad;
        bool CCCIEnable;

        // file handle for ECCCI user space interface
        int32_t fHdl;

        // share buffer base and len
        uint32_t mA2MShareBufLen;
        uint32_t mM2AShareBufLen;

        char    *mECCCIShareBuf;
        char    *mM2AShareBufRead;

        ccci_queue_element_t pQueue[CCCI_MAX_QUEUE_NUM];
        int32_t iQRead;
        int32_t iQWrite;

        uint32_t mSpeechParamAckCount[NUM_SPEECH_PARAM_ACK_TYPE];


        uint32_t mModemSideModemStatus; // value |= modem_status_mask_t

        uint16_t mWaitAckMessageID;


        AudioLock mCCCIMessageQueueMutex;
        AudioLock mA2MShareBufMutex;
        AudioLock mSetSpeechParamMutex;

        pthread_t hReadThread;
        pthread_t hSendSphThread;

        bool mIsModemResetDuringPhoneCall;
        bool mIsModemReset;
        bool mIsModemEPOF; // 1=MD power off
        record_type_t mPcmRecordType;

};

} // end namespace android

#endif
