/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein is
 * confidential and proprietary to MediaTek Inc. and/or its licensors. Without
 * the prior written permission of MediaTek inc. and/o r its licensors, any
 * reproduction, modification, use or disclosure of MediaTek Software, and
 * information contained herein, in whole or in part, shall be strictly
 * prohibited.
 *
 * MediaTek Inc. (C) 2010. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER
 * ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 * NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH
 * RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 * INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES
 * TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.
 * RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO
 * OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES CONTAINED IN MEDIATEK
 * SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE
 * RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S
 * ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE
 * RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE
 * MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE
 * CHARGE PAID BY RECEIVER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek
 * Software") have been modified by MediaTek Inc. All revisions are subject to
 * any receiver's applicable license agreements with MediaTek Inc.
 */

//#ifndef _MTK_CUSTOM_PROJECT_HAL_IMGSENSOR_SRC_CONFIGFTBL__H_
//#define _MTK_CUSTOM_PROJECT_HAL_IMGSENSOR_SRC_CONFIGFTBL__H_
#if 1
//


/*******************************************************************************
 *
 ******************************************************************************/
FTABLE_DEFINITION(SENSOR_DRVNAME_SP2518_YUV)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
FTABLE_SCENE_INDEP()
    //==========================================================================
#if 1
    //  Scene Mode
    FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_VALUES(
        KEY_AS_(MtkCameraParameters::KEY_SCENE_MODE),
        SCENE_AS_DEFAULT_SCENE(
            ITEM_AS_DEFAULT_(MtkCameraParameters::SCENE_MODE_AUTO),
            ITEM_AS_VALUES_(
                MtkCameraParameters::SCENE_MODE_AUTO,
//                MtkCameraParameters::SCENE_MODE_NORMAL,
                MtkCameraParameters::SCENE_MODE_PORTRAIT,
                MtkCameraParameters::SCENE_MODE_LANDSCAPE,
                MtkCameraParameters::SCENE_MODE_NIGHT,
                MtkCameraParameters::SCENE_MODE_NIGHT_PORTRAIT,
                MtkCameraParameters::SCENE_MODE_THEATRE,
                MtkCameraParameters::SCENE_MODE_BEACH,
                MtkCameraParameters::SCENE_MODE_SNOW,
                MtkCameraParameters::SCENE_MODE_SUNSET,
                MtkCameraParameters::SCENE_MODE_STEADYPHOTO,
                MtkCameraParameters::SCENE_MODE_FIREWORKS,
                MtkCameraParameters::SCENE_MODE_SPORTS,
                MtkCameraParameters::SCENE_MODE_PARTY,
                MtkCameraParameters::SCENE_MODE_CANDLELIGHT,
//                MtkCameraParameters::SCENE_MODE_HDR,
            )
        ),
    )
#endif
    //==========================================================================
#if 1
    //  Effect
    FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_VALUES(
        KEY_AS_(MtkCameraParameters::KEY_EFFECT),
        SCENE_AS_DEFAULT_SCENE(
            ITEM_AS_DEFAULT_(MtkCameraParameters::EFFECT_NONE),
            ITEM_AS_VALUES_(
                MtkCameraParameters::EFFECT_NONE,
                MtkCameraParameters::EFFECT_MONO,
                MtkCameraParameters::EFFECT_NEGATIVE,
                MtkCameraParameters::EFFECT_SEPIA,
                MtkCameraParameters::EFFECT_SEPIA_BLUE,
                MtkCameraParameters::EFFECT_SEPIA_GREEN,

                /*
                MtkCameraParameters::EFFECT_AQUA,
                MtkCameraParameters::EFFECT_WHITEBOARD,
                MtkCameraParameters::EFFECT_BLACKBOARD,
                MtkCameraParameters::EFFECT_POSTERIZE,
                MtkCameraParameters::EFFECT_NASHVILLE,
                MtkCameraParameters::EFFECT_HEFE,
                MtkCameraParameters::EFFECT_VALENCIA ,
                MtkCameraParameters::EFFECT_XPROII ,
                MtkCameraParameters::EFFECT_LOFI,
                MtkCameraParameters::EFFECT_SIERRA ,
                MtkCameraParameters::EFFECT_KELVIN ,
                MtkCameraParameters::EFFECT_WALDEN ,
                MtkCameraParameters::EFFECT_F1977 ,
                */
            )
        ),
    )
#endif
    //==========================================================================
#if 0
    //  Picture Size (Both width & height must be 16-aligned)
    FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_VALUES(
        KEY_AS_(MtkCameraParameters::KEY_PICTURE_SIZE),
        SCENE_AS_DEFAULT_SCENE(
            ITEM_AS_DEFAULT_("1600x1200"),
            ITEM_AS_VALUES_(
                "320x240",    "640x480",    "1024x688",    "1024x768",    "1280x720",    "1280x768",    "1280x960",
                "1440x960",   "1600x1200",
                "1840x1104",    // max picture size 5:3
            )
        ),
    )
#else
    //  Dynamic Feature Table
    //  Picture Size (Both width & height must be 16-aligned)
    //  **Not for android M: For CTS: the largest preview-size must have same aspect ratio  as the largest picture-size
#warning "Use  Dynamic Feature Table Algorithm: Picture Sizes..."
    FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_VALUES(
        KEY_AS_(MtkCameraParameters::KEY_PICTURE_SIZE), 
        SCENE_AS_DEFAULT_PICTURE_SIZE_SCENE(
            ITEM_AS_DEFAULT_("1600x1200"),
            ITEM_AS_MAX_("1600x1200"),		
            ITEM_AS_EXTRA_VALUES_(
		//"1504x1504",		// for test
            )
        ), 
    )      
#endif
    //==========================================================================
#if 0
    //  Preview Size
    FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_VALUES(
        KEY_AS_(MtkCameraParameters::KEY_PREVIEW_SIZE),
        SCENE_AS_DEFAULT_SCENE(
            ITEM_AS_DEFAULT_("640x480"),
            ITEM_AS_VALUES_(
                "176x144",      "320x240",      "352x288",      "480x320",      "480x368",
                "640x480",      "720x480",      "800x480",      "800x600",      "864x480",      "960x540",
                "1024x688",     "1280x720",
                "1280x768",     // max preview size 5:3
                //"1440x960",     "1600x960",
                //"1600x1200",
            )
        ),
    )
#else
    // Dynamic Feature Table
    //	Preview Size
    //	**Not for android M: For CTS: the largest preview-size must have same aspect ratio  as the largest picture-size
#warning "Use  Dynamic Feature Table Algorithm: Preview Sizes..."
    FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_VALUES(
	KEY_AS_(MtkCameraParameters::KEY_PREVIEW_SIZE),
	SCENE_AS_DEFAULT_PREVIEW_SIZE_SCENE(
	    ITEM_AS_DEFAULT_("640x480"), 
	    ITEM_AS_MAX_("1280x800"),
	    ITEM_AS_EXTRA_VALUES_(
	    	// "720x200", "400x400",		// for test
	    )
	), 
    )    
#endif
    //==========================================================================
#if 0
    //  Video Size
    FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_VALUES(
        KEY_AS_(MtkCameraParameters::KEY_VIDEO_SIZE),
        SCENE_AS_DEFAULT_SCENE(
            ITEM_AS_DEFAULT_("640x480"),
            ITEM_AS_VALUES_(
                "176x144",      "320x240",      "352x288",      "480x320",      "640x480",    "720x480",
                "864x480",      "1280x720",     "1920x1080",
            )
        ),
    )
#else
	// Dynamic Feature Table
	//	Video Size
#warning "Use  Dynamic Feature Table Algorithm: Video Sizes..."    
	FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_VALUES(
		KEY_AS_(MtkCameraParameters::KEY_VIDEO_SIZE), 
		SCENE_AS_DEFAULT_VIDEO_SIZE_SCENE(
		    ITEM_AS_DEFAULT_("640x480"), 
		    ITEM_AS_MAX_("1920x1088"),
		    ITEM_AS_EXTRA_VALUES_(
		    	//"1000x1000",		// for test
		    )
		), 
	)	   
#endif

    //==========================================================================
#if 1
    //  Preview Frame Rate Range
    FTABLE_CONFIG_AS_TYPE_OF_USER(
        KEY_AS_(MtkCameraParameters::KEY_PREVIEW_FPS_RANGE),
        SCENE_AS_DEFAULT_SCENE(
            ITEM_AS_DEFAULT_("30000,30000"),
            ITEM_AS_USER_LIST_(
                "(5000,30000)",
                "(5000,15000)",
#if 0
                "(60000,60000)",
                "(120000,120000)",
#endif
            )
        ),
    )
#endif
    //==========================================================================
#if 1
    //  Exposure Compensation
    FTABLE_CONFIG_AS_TYPE_OF_USER(
        KEY_AS_(MtkCameraParameters::KEY_EXPOSURE_COMPENSATION),
        SCENE_AS_DEFAULT_SCENE(
            ITEM_AS_DEFAULT_("0"),
            ITEM_AS_USER_LIST_(
                "-3",       //min exposure compensation index
                "3",        //max exposure compensation index
                "1.0",      //exposure compensation step; EV = step x index
            )
        ),
        //......................................................................
        #if 1   //  SCENE HDR
        SCENE_AS_(MtkCameraParameters::SCENE_MODE_HDR,
            ITEM_AS_DEFAULT_("0"),
            ITEM_AS_USER_LIST_(
                "0",        //min exposure compensation index
                "0",        //max exposure compensation index
                "1.0",      //exposure compensation step; EV = step x index
            )
        )
        #endif
        //......................................................................
    )
#endif
    //==========================================================================
#if 1
    //  Anti-banding (Flicker)
    FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_VALUES(
        KEY_AS_(MtkCameraParameters::KEY_ANTIBANDING),
        SCENE_AS_DEFAULT_SCENE(
            ITEM_AS_DEFAULT_(MtkCameraParameters::ANTIBANDING_OFF),
            ITEM_AS_VALUES_(
                MtkCameraParameters::ANTIBANDING_OFF,
                MtkCameraParameters::ANTIBANDING_50HZ,
                MtkCameraParameters::ANTIBANDING_60HZ,
                MtkCameraParameters::ANTIBANDING_AUTO,
            )
        ),
    )
#endif
    //==========================================================================
#if 1
    //  Video Snapshot
    FTABLE_CONFIG_AS_TYPE_OF_USER(
        KEY_AS_(MtkCameraParameters::KEY_VIDEO_SNAPSHOT_SUPPORTED),
        SCENE_AS_DEFAULT_SCENE(
            ITEM_AS_DEFAULT_(MtkCameraParameters::TRUE),
        ),
    )
#endif
    //==========================================================================
#if 1
    //  Video Stabilization (EIS)
    FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_SUPPORTED(
        KEY_AS_(MtkCameraParameters::KEY_VIDEO_STABILIZATION),
        SCENE_AS_DEFAULT_SCENE(
            ITEM_AS_DEFAULT_(MtkCameraParameters::FALSE),
            ITEM_AS_SUPPORTED_(
            #if 0
                MtkCameraParameters::FALSE
            #else
                MtkCameraParameters::TRUE
            #endif
            )
        ),
    )
#endif
    //==========================================================================
#if 1
    //  Zoom
    FTABLE_CONFIG_AS_TYPE_OF_USER(
        KEY_AS_(MtkCameraParameters::KEY_ZOOM),
        SCENE_AS_DEFAULT_SCENE(
            ITEM_AS_DEFAULT_("0"),  //Zoom Index
            ITEM_AS_USER_LIST_(
                //Zoom Ratio
                "100", "114", "132", "151", "174",
                "200", "229", "263", "303", "348",
                "400",
            )
        ),
    )
#endif
    //==========================================================================
#if 1
    //  Zsd
    FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_VALUES(
        KEY_AS_(MtkCameraParameters::KEY_ZSD_MODE),
        SCENE_AS_DEFAULT_SCENE(
            ITEM_AS_DEFAULT_(MtkCameraParameters::OFF),
            ITEM_AS_VALUES_(
                MtkCameraParameters::OFF,
                MtkCameraParameters::ON
            )
        ),
    )
#endif
    //==========================================================================
#if 1
    //  (Shot) Capture Mode
    FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_VALUES(
        KEY_AS_(MtkCameraParameters::KEY_CAPTURE_MODE),
        SCENE_AS_DEFAULT_SCENE(
            ITEM_AS_DEFAULT_(MtkCameraParameters::CAPTURE_MODE_NORMAL),
            ITEM_AS_VALUES_(
                MtkCameraParameters::CAPTURE_MODE_NORMAL,
                MtkCameraParameters::CAPTURE_MODE_FACE_BEAUTY,
                //MtkCameraParameters::CAPTURE_MODE_CONTINUOUS_SHOT,
//                MtkCameraParameters::CAPTURE_MODE_AUTO_PANORAMA_SHOT,
//                MtkCameraParameters::CAPTURE_MODE_MAV_SHOT,
                MtkCameraParameters::CAPTURE_MODE_SMILE_SHOT,
                MtkCameraParameters::CAPTURE_MODE_BEST_SHOT,
                MtkCameraParameters::CAPTURE_MODE_EV_BRACKET_SHOT,
            )
        ),
    )
#endif
    //==========================================================================
#if 0
    //	Video Hdr
    FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_VALUES(
        KEY_AS_(MtkCameraParameters::KEY_VIDEO_HDR),
        SCENE_AS_DEFAULT_SCENE(
            ITEM_AS_DEFAULT_(MtkCameraParameters::OFF),
            ITEM_AS_VALUES_(
                MtkCameraParameters::OFF,
                MtkCameraParameters::ON,
            )
        ),
    )
#endif
    //==========================================================================
END_FTABLE_SCENE_INDEP()
//------------------------------------------------------------------------------
/*******************************************************************************
 *
 ******************************************************************************/
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
FTABLE_SCENE_DEP()
    //==========================================================================
#if 1
    //  Focus Mode
    FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_VALUES(
        KEY_AS_(MtkCameraParameters::KEY_FOCUS_MODE),
        SCENE_AS_DEFAULT_SCENE(
            ITEM_AS_DEFAULT_(MtkCameraParameters::FOCUS_MODE_FIXED),
            ITEM_AS_VALUES_(
                //MtkCameraParameters::FOCUS_MODE_AUTO,
                //MtkCameraParameters::FOCUS_MODE_MACRO,
                MtkCameraParameters::FOCUS_MODE_FIXED,
                //MtkCameraParameters::FOCUS_MODE_CONTINUOUS_PICTURE,
                //MtkCameraParameters::FOCUS_MODE_CONTINUOUS_VIDEO,
                //"manual",   "fullscan",
            )
        ),
        //......................................................................
    )
#endif
    //==========================================================================
#if 1
    //  ISO
    FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_VALUES(
        KEY_AS_(MtkCameraParameters::KEY_ISO_SPEED),
        SCENE_AS_DEFAULT_SCENE(
            ITEM_AS_DEFAULT_("auto"),
            ITEM_AS_VALUES_(
                "auto",
            )
        ),
        //......................................................................
        #if 1   //  SCENE AUTO
        SCENE_AS_(MtkCameraParameters::SCENE_MODE_AUTO,
            ITEM_AS_DEFAULT_("auto"),
            ITEM_AS_VALUES_(
                "auto", "100", "200", "400",
            )
        )
        #endif
        //......................................................................
        #if 1   //  SCENE NORMAL
        SCENE_AS_(MtkCameraParameters::SCENE_MODE_NORMAL,
            ITEM_AS_DEFAULT_("auto"),
            ITEM_AS_VALUES_(
                "auto", "100", "200", "400",
            )
        )
        #endif
        //......................................................................
    )
#endif
    //==========================================================================
#if 1
    //  White Balance.
    FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_VALUES(
        KEY_AS_(MtkCameraParameters::KEY_WHITE_BALANCE),
        SCENE_AS_DEFAULT_SCENE(
            ITEM_AS_DEFAULT_(MtkCameraParameters::WHITE_BALANCE_AUTO),
            ITEM_AS_VALUES_(
                MtkCameraParameters::WHITE_BALANCE_AUTO,            	MtkCameraParameters::WHITE_BALANCE_INCANDESCENT,
                MtkCameraParameters::WHITE_BALANCE_FLUORESCENT,     	MtkCameraParameters::WHITE_BALANCE_DAYLIGHT,
                MtkCameraParameters::WHITE_BALANCE_CLOUDY_DAYLIGHT, 
                // MtkCameraParameters::WHITE_BALANCE_TWILIGHT,
            )
        ),
        //......................................................................
        #if 1   //  SCENE LANDSCAPE
        SCENE_AS_(MtkCameraParameters::SCENE_MODE_LANDSCAPE,
            ITEM_AS_DEFAULT_(MtkCameraParameters::WHITE_BALANCE_DAYLIGHT),
            ITEM_AS_VALUES_(
		MtkCameraParameters::WHITE_BALANCE_AUTO,		MtkCameraParameters::WHITE_BALANCE_INCANDESCENT,
		MtkCameraParameters::WHITE_BALANCE_FLUORESCENT, 	MtkCameraParameters::WHITE_BALANCE_DAYLIGHT,
		MtkCameraParameters::WHITE_BALANCE_CLOUDY_DAYLIGHT, 
		// MtkCameraParameters::WHITE_BALANCE_TWILIGHT,
            )
        )
        #endif
        //......................................................................
        #if 1   //  SCENE SUNSET
        SCENE_AS_(MtkCameraParameters::SCENE_MODE_SUNSET,
            ITEM_AS_DEFAULT_(MtkCameraParameters::WHITE_BALANCE_DAYLIGHT),
            ITEM_AS_VALUES_(
		MtkCameraParameters::WHITE_BALANCE_AUTO,		MtkCameraParameters::WHITE_BALANCE_INCANDESCENT,
		MtkCameraParameters::WHITE_BALANCE_FLUORESCENT, 	MtkCameraParameters::WHITE_BALANCE_DAYLIGHT,
		MtkCameraParameters::WHITE_BALANCE_CLOUDY_DAYLIGHT, 
		// MtkCameraParameters::WHITE_BALANCE_TWILIGHT,
            )
        )
        #endif
        //......................................................................
        #if 1   //  SCENE CANDLELIGHT
        SCENE_AS_(MtkCameraParameters::SCENE_MODE_CANDLELIGHT,
            ITEM_AS_DEFAULT_(MtkCameraParameters::WHITE_BALANCE_INCANDESCENT),
            ITEM_AS_VALUES_(
		MtkCameraParameters::WHITE_BALANCE_AUTO,		MtkCameraParameters::WHITE_BALANCE_INCANDESCENT,
		MtkCameraParameters::WHITE_BALANCE_FLUORESCENT, 	MtkCameraParameters::WHITE_BALANCE_DAYLIGHT,
		MtkCameraParameters::WHITE_BALANCE_CLOUDY_DAYLIGHT, 
		// MtkCameraParameters::WHITE_BALANCE_TWILIGHT,
            )
        )
        #endif
        //......................................................................
    )
#endif
    //==========================================================================
#if 0
    //  ISP Edge
    FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_VALUES(
        KEY_AS_(MtkCameraParameters::KEY_EDGE),
        SCENE_AS_DEFAULT_SCENE(
            ITEM_AS_DEFAULT_(MtkCameraParameters::MIDDLE),
            ITEM_AS_VALUES_(
                MtkCameraParameters::LOW, MtkCameraParameters::MIDDLE, MtkCameraParameters::HIGH,
            )
        ),
        //......................................................................
        //......................................................................
    )
#endif
    //==========================================================================
#if 0
    //  ISP Hue
    FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_VALUES(
        KEY_AS_(MtkCameraParameters::KEY_HUE),
        SCENE_AS_DEFAULT_SCENE(
            ITEM_AS_DEFAULT_(MtkCameraParameters::MIDDLE),
            ITEM_AS_VALUES_(
                MtkCameraParameters::LOW, MtkCameraParameters::MIDDLE, MtkCameraParameters::HIGH,
            )
        ),
        //......................................................................
        //......................................................................
    )
#endif
    //==========================================================================
#if 0
    //  ISP Saturation
    FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_VALUES(
        KEY_AS_(MtkCameraParameters::KEY_SATURATION),
        SCENE_AS_DEFAULT_SCENE(
            ITEM_AS_DEFAULT_(MtkCameraParameters::MIDDLE),
            ITEM_AS_VALUES_(
                MtkCameraParameters::LOW, MtkCameraParameters::MIDDLE, MtkCameraParameters::HIGH,
            )
        ),
        //......................................................................
        //......................................................................
    )
#endif
    //==========================================================================
#if 0
    //  ISP Brightness
    FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_VALUES(
        KEY_AS_(MtkCameraParameters::KEY_BRIGHTNESS),
        SCENE_AS_DEFAULT_SCENE(
            ITEM_AS_DEFAULT_(MtkCameraParameters::MIDDLE),
            ITEM_AS_VALUES_(
                MtkCameraParameters::LOW, MtkCameraParameters::MIDDLE, MtkCameraParameters::HIGH,
            )
        ),
        //......................................................................
        //......................................................................
    )
#endif
    //==========================================================================
#if 0
    //  ISP Contrast
    FTABLE_CONFIG_AS_TYPE_OF_DEFAULT_VALUES(
        KEY_AS_(MtkCameraParameters::KEY_CONTRAST),
        SCENE_AS_DEFAULT_SCENE(
            ITEM_AS_DEFAULT_(MtkCameraParameters::MIDDLE),
            ITEM_AS_VALUES_(
                MtkCameraParameters::LOW, MtkCameraParameters::MIDDLE, MtkCameraParameters::HIGH,
            )
        ),
        //......................................................................
        //......................................................................
    )
#endif
    //==========================================================================
END_FTABLE_SCENE_DEP()
//------------------------------------------------------------------------------
END_FTABLE_DEFINITION()


/*******************************************************************************
 *
 ******************************************************************************/
#endif
//#endif //_MTK_CUSTOM_PROJECT_HAL_IMGSENSOR_SRC_CONFIGFTBL__H_

