#ifndef ANDROID_AUDIO_ALSA_PLAYBACK_HANDLER_SPEAKERPROTECTION_H
#define ANDROID_AUDIO_ALSA_PLAYBACK_HANDLER_SPEAKERPROTECTION_H

#include "AudioALSAPlaybackHandlerBase.h"
#include "AudioALSAPcmDataCaptureIn.h"
extern "C" {
#include <mlds_api.h>
}
#define DSM_CHANNELS        1

namespace android
{

class AudioALSAPlaybackHandlerSpeakerProtection : public AudioALSAPlaybackHandlerBase
{
    public:
        AudioALSAPlaybackHandlerSpeakerProtection(const stream_attribute_t *stream_attribute_source);
        virtual ~AudioALSAPlaybackHandlerSpeakerProtection();

        status_t setParameters(const String8 &keyValuePairs);
        String8  getParameters(const String8 &keys);

        /**
         * open/close audio hardware
         */
        virtual status_t open();
        virtual status_t close();
        virtual status_t pause();
        virtual status_t resume();
        virtual status_t flush();
        virtual int drain(audio_drain_type_t type);

        virtual status_t routing(const audio_devices_t output_devices);
	virtual status_t setVolume(uint32_t vol);

        /**
         * write data to audio hardware
         */
        virtual ssize_t  write(const void *buffer, size_t bytes);
        virtual status_t setFilterMng(AudioMTKFilterManager *pFilterMng);

        /**
         * low latency
         */
        virtual status_t setLowLatencyMode(bool mode, size_t lowLatencyHalBufferSize, size_t reduceInterruptSize, bool bforce = false);

        unsigned int GetSampleSize(unsigned int Format);
        unsigned int GetFrameSize(unsigned int channels , unsigned int Format);

       // post processing interface
        virtual status_t SpeakerProtectionInterfaceInit(unsigned int SampleRate,unsigned int chennels , unsigned int Format);
        virtual status_t SpeakerProtectionInterfaceDeinit();
        virtual status_t Initmldsconfig(const stream_attribute_t *mStreamAttributeSource ,stream_attribute_t *mStreamAttributeTarget);
        virtual status_t SpeakerBufferInit(void);
        virtual status_t SpeakerBufferDeInit(void);
        status_t DoSpeakerProtionInterfaceProcessing(void *pInBuffer, uint32_t inBytes, void **ppOutBuffer, uint32_t *pOutBytes);
        status_t DoSpeakerProctionPacking(int *Dsmtempbuffer,int ValidInputBuffersize);
        status_t DoSpeakerProctionUnPacking(int *pbuffer,int ValidInputBuffersize);
        status_t MonoToStereo(int *pbuffer, int ValidInputBuffersize);

        status_t EnableIVTask(pcm_config mPcm_config);
        status_t DisableIVTask(void);
        status_t CopyIVbuffer(void* Input , short* Rbuffer , short* Lbuffer,unsigned int samplecount);
        void OpenPCMIVDump(const char *class_name);
        void ClosePCMIVDump();

        // using dl to do function open
        virtual status_t InitmldsInterface();

	FILE *mPCMPlayIVDumpFile;
	int mDumpPlayIVFileNum;

    private:
        struct timespec mNewtime, mOldtime;
        struct mixer *mMixer;
        uint32_t ChooseTargetSampleRate(uint32_t SampleRate,audio_devices_t outputdevice);
        double latencyTime[3];


        //  for MAXIM porting
        void *dsm_handler;
        void *mMlds_handle;
        unsigned int mu4DsmMemSize;
        int mDsmMemSize;
        int *mDsmMemBuffer;
        int mDsmBuffer[DSM_CHANNELS*4+1 ];
        int remaining_bytes;
        const int mDsmBufferSize = 1024*16;
        unsigned int mDsmSamples;
        unsigned int mDsmChannels;
        unsigned int mInputChannels;
        unsigned int mDsmSampleRate;
        int *mDsmpcmIn, *mDsmpcmOut,*mDsmProcessingbuffer;
        int *mSpeakerChannelProcessingBuffer;

        // mlds interface
        mlds_task_config_t mmlds_task_config;

        // IV data Process
        AudioALSAPcmDataCaptureIn *mAudioAlsaPcmIn;
        int *mDsmiData, *mDsmvData , *mDsmIvReadData;
        struct pcm_config mPcmIvConfig;

        //mlds_interface pointer pointer
        mlds_interface mMlds_Interace_pointer;
};

} // end namespace android

#endif // end of ANDROID_AUDIO_ALSA_PLAYBACK_HANDLER_SPEAKERPROTECTION_H
