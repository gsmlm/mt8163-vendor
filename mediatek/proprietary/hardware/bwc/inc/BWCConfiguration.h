#ifndef __BWC_CONFIGURATION_H__
#define __BWC_CONFIGURATION_H__

#include  "bandwidth_control.h"
#include "BWCProfileAdapter.h"
#include "mt_smi.h"

#ifdef  BWC_J
	BWCProfile profileSetting[]={
		BWCProfile(BWCPT_NONE, (char*)"BWCPT_NONE",SMI_BWC_SCEN_NORMAL,(char*)"CON_SCE_NORMAL"),
		BWCProfile(BWCPT_VIDEO_NORMAL,(char*)"BWCPT_VIDEO_NORMAL",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_CAMERA_PREVIEW,(char*)"BWCPT_CAMERA_PREVIEW",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_CAMERA_ZSD,(char*)"BWCPT_CAMERA_ZSD",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_CAMERA_CAPTURE,(char*)"BWCPT_CAMERA_CAPTURE",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_CAMERA_ICFP,(char*)"BWCPT_CAMERA_ICFP",SMI_BWC_SCEN_ICFP,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_VIDEO_SWDEC_PLAYBACK,(char*)"BWCPT_VIDEO_SWDEC_PLAYBACK",SMI_BWC_SCEN_SWDEC_VP,(char*)"CON_SCE_VPWFD"),
		BWCProfile(BWCPT_VIDEO_PLAYBACK,(char*)"BWCPT_VIDEO_PLAYBACK",SMI_BWC_SCEN_VP,(char*)"CON_SCE_VPWFD"),
		BWCProfile(BWCPT_VIDEO_TELEPHONY,(char*)"BWCPT_VIDEO_TELEPHONY",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_VIDEO_RECORD,(char*)"BWCPT_VIDEO_RECORD",SMI_BWC_SCEN_VENC,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_VIDEO_RECORD_CAMERA,(char*)"BWCPT_VIDEO_RECORD_CAMERA",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_VIDEO_RECORD_SLOWMOTION,(char*)"BWCPT_VIDEO_RECORD_SLOWMOTION",SMI_BWC_SCEN_VR_SLOW,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_VIDEO_SNAPSHOT,(char*)"BWCPT_VIDEO_SNAPSHOT",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_VIDEO_LIVE_PHOTO,(char*)"BWCPT_VIDEO_LIVE_PHOTO",SMI_BWC_SCEN_MM_GPU,(char*)"CON_SCE_NORMAL"),
		BWCProfile(BWCPT_VIDEO_WIFI_DISPLAY,(char*)"BWCPT_VIDEO_WIFI_DISPLAY",SMI_BWC_SCEN_WFD,(char*)"CON_SCE_NORMAL"),
		BWCProfile(BWCPT_FORCE_MMDVFS,(char*)"BWCPT_FORCE_MMDVFS",SMI_BWC_SCEN_FORCE_MMDVFS,NULL),
	};
	int total_bwc_profiles = 16;

#elif defined(BWC_D1)||defined(BWC_D3)
		BWCProfile profileSetting[]={
		BWCProfile(BWCPT_NONE,(char*)"BWCPT_NONE",SMI_BWC_SCEN_NORMAL,(char*)"CON_SCE_NORMAL"),
		BWCProfile(BWCPT_VIDEO_NORMAL,(char*)"BWCPT_VIDEO_NORMAL",SMI_BWC_SCEN_VR,(char*)"CON_SCE_NORMAL"),
		BWCProfile(BWCPT_CAMERA_PREVIEW,(char*)"BWCPT_CAMERA_PREVIEW",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_CAMERA_ZSD,(char*)"BWCPT_CAMERA_ZSD",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_CAMERA_CAPTURE,(char*)"BWCPT_CAMERA_CAPTURE",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_CAMERA_ICFP,(char*)"BWCPT_CAMERA_ICFP",SMI_BWC_SCEN_ICFP,(char*)"CON_SCE_NORMAL"),
		BWCProfile(BWCPT_VIDEO_SWDEC_PLAYBACK,(char*)"BWCPT_VIDEO_SWDEC_PLAYBACK",SMI_BWC_SCEN_SWDEC_VP,(char*)"CON_SCE_VPWFD"),
		BWCProfile(BWCPT_VIDEO_PLAYBACK,(char*)"BWCPT_VIDEO_PLAYBACK",SMI_BWC_SCEN_VP,(char*)"CON_SCE_VPWFD"),
		BWCProfile(BWCPT_VIDEO_TELEPHONY,(char*)"BWCPT_VIDEO_TELEPHONY",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_VIDEO_RECORD,(char*)"BWCPT_VIDEO_RECORD",SMI_BWC_SCEN_VENC,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_VIDEO_RECORD_CAMERA,(char*)"BWCPT_VIDEO_RECORD_CAMERA",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_VIDEO_RECORD_SLOWMOTION,(char*)"BWCPT_VIDEO_RECORD_SLOWMOTION",SMI_BWC_SCEN_VR_SLOW,(char*)"CON_SCE_VSS"),
		#ifdef BWC_D3
			BWCProfile(BWCPT_VIDEO_SNAPSHOT,(char*)"BWCPT_VIDEO_SNAPSHOT",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		#else
			BWCProfile(BWCPT_VIDEO_SNAPSHOT,(char*)"BWCPT_VIDEO_SNAPSHOT",SMI_BWC_SCEN_VSS,(char*)"CON_SCE_VSS"),
		#endif
		BWCProfile(BWCPT_VIDEO_LIVE_PHOTO,(char*)"BWCPT_VIDEO_LIVE_PHOTO",SMI_BWC_SCEN_MM_GPU,(char*)"CON_SCE_NORMAL"),
		BWCProfile(BWCPT_VIDEO_WIFI_DISPLAY,(char*)"BWCPT_VIDEO_WIFI_DISPLAY",SMI_BWC_SCEN_WFD,(char*)"CON_SCE_VPWFD"),
		BWCProfile(BWCPT_FORCE_MMDVFS,(char*)"BWCPT_FORCE_MMDVFS",SMI_BWC_SCEN_FORCE_MMDVFS,NULL)
	};
	int total_bwc_profiles = 16;
#elif defined(BWC_D2)
		BWCProfile profileSetting[]={
		BWCProfile(BWCPT_NONE,(char*)"BWCPT_NONE",SMI_BWC_SCEN_NORMAL,(char*)"CON_SCE_NORMAL"),
		BWCProfile(BWCPT_VIDEO_NORMAL,(char*)"BWCPT_VIDEO_NORMAL",SMI_BWC_SCEN_VR,(char*)"CON_SCE_NORMAL"),
		BWCProfile(BWCPT_CAMERA_PREVIEW,(char*)"BWCPT_CAMERA_PREVIEW",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_CAMERA_ZSD,(char*)"BWCPT_CAMERA_ZSD",SMI_BWC_SCEN_VR,(char*)"CON_SCE_ICFP"),
		BWCProfile(BWCPT_CAMERA_CAPTURE,(char*)"BWCPT_CAMERA_CAPTURE",SMI_BWC_SCEN_VR,(char*)"CON_SCE_ICFP"),
		BWCProfile(BWCPT_CAMERA_ICFP,(char*)"BWCPT_CAMERA_ICFP",SMI_BWC_SCEN_ICFP,(char*)"CON_SCE_ICFP"),
		BWCProfile(BWCPT_VIDEO_SWDEC_PLAYBACK,(char*)"BWCPT_VIDEO_SWDEC_PLAYBACK",SMI_BWC_SCEN_SWDEC_VP,(char*)"CON_SCE_NORMAL"),
		BWCProfile(BWCPT_VIDEO_PLAYBACK,(char*)"BWCPT_VIDEO_PLAYBACK",SMI_BWC_SCEN_VP,(char*)"CON_SCE_NORMAL"),
		BWCProfile(BWCPT_VIDEO_TELEPHONY,(char*)"BWCPT_VIDEO_TELEPHONY",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_VIDEO_RECORD,(char*)"BWCPT_VIDEO_RECORD",SMI_BWC_SCEN_VENC,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_VIDEO_RECORD_CAMERA,(char*)"BWCPT_VIDEO_RECORD_CAMERA",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_VIDEO_RECORD_SLOWMOTION,(char*)"BWCPT_VIDEO_RECORD_SLOWMOTION",SMI_BWC_SCEN_VR_SLOW,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_VIDEO_SNAPSHOT,(char*)"BWCPT_VIDEO_SNAPSHOT",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_VIDEO_LIVE_PHOTO,(char*)"BWCPT_VIDEO_LIVE_PHOTO",SMI_BWC_SCEN_MM_GPU,(char*)"CON_SCE_NORMAL"),
		BWCProfile(BWCPT_VIDEO_WIFI_DISPLAY,(char*)"BWCPT_VIDEO_WIFI_DISPLAY",SMI_BWC_SCEN_WFD,(char*)"CON_SCE_NORMAL"),
		BWCProfile(BWCPT_FORCE_MMDVFS,(char*)"BWCPT_FORCE_MMDVFS",SMI_BWC_SCEN_FORCE_MMDVFS,NULL)
	};
	int total_bwc_profiles = 16;
#elif defined(BWC_EV)
		BWCProfile profileSetting[]={
		BWCProfile(BWCPT_NONE, (char*)"BWCPT_NONE",SMI_BWC_SCEN_NORMAL,(char*)"CON_SCE_NORMAL"),
		BWCProfile(BWCPT_VIDEO_NORMAL,(char*)"BWCPT_VIDEO_NORMAL",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VP4K"),
		BWCProfile(BWCPT_CAMERA_PREVIEW,(char*)"BWCPT_CAMERA_PREVIEW",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VR4K"),
		BWCProfile(BWCPT_CAMERA_ZSD,(char*)"BWCPT_CAMERA_ZSD",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VR4K"),
		BWCProfile(BWCPT_CAMERA_CAPTURE,(char*)"BWCPT_CAMERA_CAPTURE",SMI_BWC_SCEN_VR,(char*)"CON_SCE_ICFP"),
		BWCProfile(BWCPT_CAMERA_ICFP,(char*)"BWCPT_CAMERA_ICFP",SMI_BWC_SCEN_ICFP,(char*)"CON_SCE_ICFP"),
		BWCProfile(BWCPT_VIDEO_SWDEC_PLAYBACK,(char*)"BWCPT_VIDEO_SWDEC_PLAYBACK",SMI_BWC_SCEN_SWDEC_VP,(char*)"CON_SCE_NORMAL"),
		BWCProfile(BWCPT_VIDEO_PLAYBACK,(char*)"BWCPT_VIDEO_PLAYBACK",SMI_BWC_SCEN_VP,(char*)"CON_SCE_VP4K"),
		BWCProfile(BWCPT_VIDEO_TELEPHONY,(char*)"BWCPT_VIDEO_TELEPHONY",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VR4K"),
		BWCProfile(BWCPT_VIDEO_RECORD,(char*)"BWCPT_VIDEO_RECORD",SMI_BWC_SCEN_VENC,(char*)"CON_SCE_VR4K"),
		BWCProfile(BWCPT_VIDEO_RECORD_CAMERA,(char*)"BWCPT_VIDEO_RECORD_CAMERA",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VR4K"),
		BWCProfile(BWCPT_VIDEO_RECORD_SLOWMOTION,(char*)"BWCPT_VIDEO_RECORD_SLOWMOTION",SMI_BWC_SCEN_VR_SLOW,(char*)"CON_SCE_SMVR120"),
		BWCProfile(BWCPT_VIDEO_SNAPSHOT,(char*)"BWCPT_VIDEO_SNAPSHOT",SMI_BWC_SCEN_VR,(char*)"CON_SCE_ICFP"),
		BWCProfile(BWCPT_VIDEO_LIVE_PHOTO,(char*)"BWCPT_VIDEO_LIVE_PHOTO",SMI_BWC_SCEN_MM_GPU,(char*)"CON_SCE_NORMAL"),
		BWCProfile(BWCPT_VIDEO_WIFI_DISPLAY,(char*)"BWCPT_VIDEO_WIFI_DISPLAY",SMI_BWC_SCEN_WFD,(char*)"CON_SCE_NORMAL"),
		BWCProfile(BWCPT_FORCE_MMDVFS,(char*)"BWCPT_FORCE_MMDVFS",SMI_BWC_SCEN_FORCE_MMDVFS,NULL),
	};
	int total_bwc_profiles = 16;
#elif defined(BWC_R)
		BWCProfile profileSetting[]={
		BWCProfile(BWCPT_NONE, (char*)"BWCPT_NONE",SMI_BWC_SCEN_NORMAL,(char*)"CON_SCE_NORMAL"),
		BWCProfile(BWCPT_VIDEO_NORMAL,(char*)"BWCPT_VIDEO_NORMAL",SMI_BWC_SCEN_VR,(char*)"CON_SCE_UI_6L"),
		BWCProfile(BWCPT_CAMERA_PREVIEW,(char*)"BWCPT_CAMERA_PREVIEW",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_CAMERA_ZSD,(char*)"BWCPT_CAMERA_ZSD",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_CAMERA_CAPTURE,(char*)"BWCPT_CAMERA_CAPTURE",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_CAMERA_ICFP,(char*)"BWCPT_CAMERA_ICFP",SMI_BWC_SCEN_ICFP,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_VIDEO_SWDEC_PLAYBACK,(char*)"BWCPT_VIDEO_SWDEC_PLAYBACK",SMI_BWC_SCEN_SWDEC_VP,(char*)"CON_SCE_UI_6L"),
		BWCProfile(BWCPT_VIDEO_PLAYBACK,(char*)"BWCPT_VIDEO_PLAYBACK",SMI_BWC_SCEN_VP,(char*)"CON_SCE_UI_6L"),
		BWCProfile(BWCPT_VIDEO_TELEPHONY,(char*)"BWCPT_VIDEO_TELEPHONY",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_VIDEO_RECORD,(char*)"BWCPT_VIDEO_RECORD",SMI_BWC_SCEN_VENC,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_VIDEO_RECORD_CAMERA,(char*)"BWCPT_VIDEO_RECORD_CAMERA",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_VIDEO_RECORD_SLOWMOTION,(char*)"BWCPT_VIDEO_RECORD_SLOWMOTION",SMI_BWC_SCEN_VR_SLOW,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_VIDEO_SNAPSHOT,(char*)"BWCPT_VIDEO_SNAPSHOT",SMI_BWC_SCEN_VR,(char*)"CON_SCE_VSS"),
		BWCProfile(BWCPT_VIDEO_LIVE_PHOTO,(char*)"BWCPT_VIDEO_LIVE_PHOTO",SMI_BWC_SCEN_MM_GPU,(char*)"CON_SCE_UI_6L"),
		BWCProfile(BWCPT_VIDEO_WIFI_DISPLAY,(char*)"BWCPT_VIDEO_WIFI_DISPLAY",SMI_BWC_SCEN_WFD,(char*)"CON_SCE_UI_6L"),
		BWCProfile(BWCPT_FORCE_MMDVFS,(char*)"BWCPT_FORCE_MMDVFS",SMI_BWC_SCEN_FORCE_MMDVFS,NULL),
	};
	int total_bwc_profiles = 16;
#else
	BWCProfile* profileSetting = NULL;
	int total_bwc_profiles = 0;
#endif

BWCProfile defaultProfileSetting[]={
	BWCProfile(BWCPT_NONE,(char*)"BWCPT_NONE",SMI_BWC_SCEN_NORMAL,(char*)"CON_SCE_NORMAL"),
	BWCProfile(BWCPT_VIDEO_NORMAL,(char*)"BWCPT_VIDEO_NORMAL",SMI_BWC_SCEN_VR,(char*)"CON_SCE_NORMAL"),
	BWCProfile(BWCPT_CAMERA_PREVIEW,(char*)"BWCPT_CAMERA_PREVIEW",SMI_BWC_SCEN_VR,(char*)"CON_SCE_NORMAL"),
	BWCProfile(BWCPT_CAMERA_ZSD,(char*)"BWCPT_CAMERA_ZSD",SMI_BWC_SCEN_VR,(char*)"CON_SCE_NORMAL"),
	BWCProfile(BWCPT_CAMERA_CAPTURE,(char*)"BWCPT_CAMERA_CAPTURE",SMI_BWC_SCEN_VR,(char*)"CON_SCE_NORMAL"),
	BWCProfile(BWCPT_CAMERA_ICFP,(char*)"BWCPT_CAMERA_ICFP",SMI_BWC_SCEN_VR,(char*)"CON_SCE_NORMAL"),
	BWCProfile(BWCPT_VIDEO_SWDEC_PLAYBACK,(char*)"BWCPT_VIDEO_SWDEC_PLAYBACK",SMI_BWC_SCEN_VP,(char*)"CON_SCE_NORMAL"),
	BWCProfile(BWCPT_VIDEO_PLAYBACK,(char*)"BWCPT_VIDEO_PLAYBACK",SMI_BWC_SCEN_VP,(char*)"CON_SCE_NORMAL"),
	BWCProfile(BWCPT_VIDEO_TELEPHONY,(char*)"BWCPT_VIDEO_TELEPHONY",SMI_BWC_SCEN_VR,(char*)"CON_SCE_NORMAL"),
	BWCProfile(BWCPT_VIDEO_RECORD,(char*)"BWCPT_VIDEO_RECORD",SMI_BWC_SCEN_VR,(char*)"CON_SCE_NORMAL"),
	BWCProfile(BWCPT_VIDEO_RECORD_CAMERA,(char*)"BWCPT_VIDEO_RECORD_CAMERA",SMI_BWC_SCEN_VR,(char*)"CON_SCE_NORMAL"),
	BWCProfile(BWCPT_VIDEO_RECORD_SLOWMOTION,(char*)"BWCPT_VIDEO_RECORD_SLOWMOTION",SMI_BWC_SCEN_VR,(char*)"CON_SCE_NORMAL"),
	BWCProfile(BWCPT_VIDEO_SNAPSHOT,(char*)"BWCPT_VIDEO_SNAPSHOT",SMI_BWC_SCEN_VR,(char*)"CON_SCE_NORMAL"),
	BWCProfile(BWCPT_VIDEO_LIVE_PHOTO,(char*)"BWCPT_VIDEO_LIVE_PHOTO",SMI_BWC_SCEN_NORMAL,(char*)"CON_SCE_NORMAL"),
	BWCProfile(BWCPT_VIDEO_WIFI_DISPLAY,(char*)"BWCPT_VIDEO_WIFI_DISPLAY",SMI_BWC_SCEN_NORMAL,(char*)"CON_SCE_NORMAL"),
	BWCProfile(BWCPT_FORCE_MMDVFS,(char*)"BWCPT_FORCE_MMDVFS",SMI_BWC_SCEN_NORMAL,NULL)
};
int total_default_bwc_profiles = 16;

#endif
