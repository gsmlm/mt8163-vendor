#include "AudioALSACaptureDataProviderVoiceUL.h"

#include <pthread.h>

#include <linux/rtpm_prio.h>
#include <sys/prctl.h>

#include "AudioType.h"

#include "SpeechDataProcessingHandler.h"

#define LOG_TAG "AudioALSACaptureDataProviderUL"

namespace android
{


/*==============================================================================
 *                     Constant
 *============================================================================*/


/*==============================================================================
 *                     Implementation
 *============================================================================*/
AudioLock mCaptureDataProviderVoiceULLock;
AudioALSACaptureDataProviderVoiceUL *AudioALSACaptureDataProviderVoiceUL::mAudioALSACaptureDataProviderVoiceUL = NULL;
AudioALSACaptureDataProviderVoiceUL *AudioALSACaptureDataProviderVoiceUL::getInstance()
{
    AudioAutoTimeoutLock _l(mCaptureDataProviderVoiceULLock);

    if (mAudioALSACaptureDataProviderVoiceUL == NULL)
    {
        mAudioALSACaptureDataProviderVoiceUL = new AudioALSACaptureDataProviderVoiceUL();
    }
    ASSERT(mAudioALSACaptureDataProviderVoiceUL != NULL);
    return mAudioALSACaptureDataProviderVoiceUL;
}

bool AudioALSACaptureDataProviderVoiceUL::hasInstance()
{
    return mAudioALSACaptureDataProviderVoiceUL != NULL ? true : false;
}

AudioALSACaptureDataProviderVoiceUL::AudioALSACaptureDataProviderVoiceUL()
{
    ALOGD("%s()", __FUNCTION__);
    mCaptureDataProviderType = CAPTURE_PROVIDER_VOICE;
}

AudioALSACaptureDataProviderVoiceUL::~AudioALSACaptureDataProviderVoiceUL()
{
    ALOGD("+%s()\n", __FUNCTION__);
    AudioAutoTimeoutLock _l(mCaptureDataProviderVoiceULLock);

    mAudioALSACaptureDataProviderVoiceUL = NULL;
    SpeechDataProcessingHandler::destoryInstanceSafely();
    
    ALOGD("-%s()\n", __FUNCTION__);
}


status_t AudioALSACaptureDataProviderVoiceUL::open()
{
    ALOGD("%s()", __FUNCTION__);
    ASSERT(mClientLock.tryLock() != 0); // lock by base class attach
    AudioAutoTimeoutLock _l(mEnableLock);

    ASSERT(mEnable == false);

    SpeechDataProcessingHandler::getInstance()->getStreamAttributeSource(&mStreamAttributeSource);
    ALOGD("%s(), mStreamAttributeSource: audio_format = %d, num_channels = %d, audio_channel_mask = %x, sample_rate = %d\n", __FUNCTION__, mStreamAttributeSource.audio_format, mStreamAttributeSource.num_channels, mStreamAttributeSource.audio_channel_mask, mStreamAttributeSource.sample_rate);

    mEnable = true;

    OpenPCMDump(LOG_TAG);

    return SpeechDataProcessingHandler::getInstance()->recordOn(RECORD_TYPE_UL);
}

status_t AudioALSACaptureDataProviderVoiceUL::close()
{
    ALOGD("%s()", __FUNCTION__);
    ASSERT(mClientLock.tryLock() != 0); // lock by base class detach

    mEnable = false;
    AudioAutoTimeoutLock _l(mEnableLock);

    ClosePCMDump();

    return SpeechDataProcessingHandler::getInstance()->recordOff(RECORD_TYPE_UL);
}

status_t AudioALSACaptureDataProviderVoiceUL::provideModemRecordDataToProvider(RingBuf modem_record_buf)
{
    status_t retval = mEnableLock.lock_timeout(300);
    ASSERT(retval == NO_ERROR);

    if (mEnable == false)
    {
        //ALOGW("%s(), already closed, return", __FUNCTION__);
        mEnableLock.unlock();
        return NO_INIT;
    }

    mPcmReadBuf = modem_record_buf;
    ALOGD("%s(), pBufBase(%p), bufLen(%d), pRead(%p), pWrite(%p)",
          __FUNCTION__,
          mPcmReadBuf.pBufBase,
          mPcmReadBuf.bufLen,
          mPcmReadBuf.pRead,
          mPcmReadBuf.pWrite);

    mEnableLock.unlock();
    provideCaptureDataToAllClients(mOpenIndex);

    return NO_ERROR;
}


} // end of namespace android

