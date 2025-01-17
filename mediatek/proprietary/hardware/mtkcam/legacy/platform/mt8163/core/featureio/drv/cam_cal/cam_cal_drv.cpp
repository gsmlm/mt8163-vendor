#define MTK_LOG_ENABLE 1
#define LOG_TAG "CamCalDrv"

#include <utils/Errors.h>
#include <cutils/properties.h>
#include <cutils/log.h>
#include <stdio.h>
#include <stdlib.h> //sl121106 for atoi()
#include <fcntl.h>
#include "cam_cal_drv.h"
#include "cam_cal_drv_imp.h"

#ifdef CAM_CAL_SUPPORT  //seanlin 120919 it's for compiling mt6589fpga_ca7_ldvt
#include "camera_custom_msdk.h"
#endif
//seanlin 121017 no need beacuse of cam_cal_drv.h?? #include "camera_custom_cam_cal.h"
#include "camera_custom_cam_cal.h"
#include "camera_common_calibration.h"
#include <mtkcam/hal/IHalSensor.h> // 95 sensor hal interface
using namespace NSCam;

/*******************************************************************************
*
********************************************************************************/

/*******************************************************************************
*
********************************************************************************/


//#define CAM_CAL_DRV_LOG(fmt, arg...)    LOGD(LOG_TAG " " fmt, ##arg)
//#define CAM_CAL_DRV_ERR(fmt, arg...)    LOGE(LOG_TAG "Err: %5d: " fmt, __LINE__, ##arg)

//#define CAM_CAL_DRV_LOG(fmt, arg...)    ALOGD(CAM_CAL_LOG_TAG " " fmt, ##arg)
//#define CAM_CAL_DRV_ERR(fmt, arg...)    ALOGE(CAM_CAL_LOG_TAG "Err: %5d: " fmt, __LINE__, ##arg)

#define CAM_CAL_DRV_LOG(fmt, arg...)    ALOGD(LOG_TAG " " fmt, ##arg)
#define CAM_CAL_DRV_ERR(fmt, arg...)    ALOGE(LOG_TAG "Err: %5d: " fmt, __LINE__, ##arg)

#define CAM_CAL_DRV_LOG_IF(cond, ...)      do { if ( (cond) ) { CAM_CAL_DRV_LOG(__VA_ARGS__); } }while(0)
//121016 for 658x     #define INVALID_HANDLE_VALUE (-1)

/*******************************************************************************
*
********************************************************************************/


/*******************************************************************************
*
********************************************************************************/
  CAM_CAL_DATA_STRUCT CamCalDrv::StCamCalCaldata;
MINT32 CamCalDrv::m32CamCalDataValidation=CAM_CAL_ERR_NO_DEVICE;
/*******************************************************************************
*
********************************************************************************/
CamCalDrvBase*
CamCalDrvBase::createInstance()
{
    return CamCalDrv::getInstance();
}

/*******************************************************************************
*
********************************************************************************/
CamCalDrvBase*
CamCalDrv::getInstance()
{
    static CamCalDrv singleton;
    return &singleton;
}

/*******************************************************************************
*
********************************************************************************/
void
CamCalDrv::destroyInstance()
{
}

/*******************************************************************************
*
********************************************************************************/
CamCalDrv::CamCalDrv()
    : CamCalDrvBase()
//    ,m32CamCalDataValidation() //seanlin 121017 initialization
{
    //CamCalDrv::m32CamCalDataValidation=CAM_CAL_ERR_NO_DEVICE;
}

/*******************************************************************************
*
********************************************************************************/
CamCalDrv::~CamCalDrv()
{

}

/*******************************************************************************
[i4SensorDevId]
typedef enum halSensorDev_s {
    SENSOR_DEV_NONE = 0x00,
    SENSOR_DEV_MAIN = 0x01,
    SENSOR_DEV_SUB  = 0x02,
    SENSOR_DEV_ATV  = 0x04,
    SENSOR_DEV_MAIN_2 = 0x08,
    SENSOR_DEV_MAIN_3D = 0x09,
} halSensorDev_e;
[a_eCamCalDataType]
typedef enum
{
    CAMERA_CAM_CAL_DATA_MODULE_VERSION=0,            //seanlin 121016 it's for user to get info. of single module or N3D module
    CAMERA_CAM_CAL_DATA_PART_NUMBER,                      //seanlin 121016 return 5x4 byes gulPartNumberRegCamCal[5]
    CAMERA_CAM_CAL_DATA_SHADING_TABLE,                  //seanlin 121016 return SingleLsc or N3DLsc
    CAMERA_CAM_CAL_DATA_3A_GAIN,                              //seanlin 121016 return Single2A or N3D3A
    CAMERA_CAM_CAL_DATA_3D_GEO,                               //seanlin 121016 return none or N3D3D
    CAMERA_CAM_CAL_DATA_LIST
}CAMERA_CAM_CAL_TYPE_ENUM; //CAMERA_CAM_CAL_TYPE_ENUM;
[a_pCamCalData]
    CAMERA_CAM_CAL_TYPE_ENUM Command;   //seanlin121016 it tells cam_cal driver to return what users want.
    CAM_CAL_DATA_VER_ENUM DataVer;
    MUINT8 PartNumber[24];
    CAM_CAL_SINGLE_LSC_STRUCT SingleLsc;
    CAM_CAL_SINGLE_2A_STRUCT Single2A;
    CAM_CAL_N3D_LSC_STRUCT N3DLsc;
    CAM_CAL_N3D_3A_STRUCT N3D3A;
    CAM_CAL_N3D_3D_STRUCT N3D3D;
********************************************************************************/
int CamCalDrv::GetCamCalCalData(unsigned long i4SensorDevId,
                          /*unsigned long u4SensorID,*/
                          CAMERA_CAM_CAL_TYPE_ENUM a_eCamCalDataType,
                          void *a_pCamCalData)
{
    int err = 0;

    MUINT32 locali4SensorDevId = i4SensorDevId;
    MUINT32 mulIdx;
    static BOOL bfFirstCalData = FALSE;
    PCAM_CAL_DATA_STRUCT la_pCamCalData = (PCAM_CAL_DATA_STRUCT)a_pCamCalData;
    PCAM_CAL_DATA_STRUCT pCamcalData = &StCamCalCaldata;
    //PCAM_CAL_DATA_STRUCT pCamcalData = (PCAM_CAL_DATA_STRUCT)a_pCamCalData;
    MINT32 i4CurrSensorId = 0xFF;

    //====== Get Property ======
    char value[PROPERTY_VALUE_MAX] = {'\0'};
    property_get("camcaldrv.log", value, "0");
    MINT32 dumpEnable = atoi(value);
    //====== Get Property ======

   // dumpEnable = 1; // Jessy add this, adb shell setprop camcaldrv.log cannot work

    CAM_CAL_DRV_LOG_IF(dumpEnable, "CamCalDrv::GetCamCalCalData(). \n");
    CAM_CAL_DRV_LOG_IF(dumpEnable, "i4SensorDevId0x%8x \n", i4SensorDevId);
    CAM_CAL_DRV_LOG_IF(dumpEnable, "CAMERA_CAM_CAL_TYPE_ENUM: %d\n", a_eCamCalDataType);

    if ( (i4SensorDevId & (!(SENSOR_DEV_MAIN_3D|SENSOR_DEV_SUB))) ||
        (a_eCamCalDataType > CAMERA_CAM_CAL_DATA_3D_GEO)||
        (a_pCamCalData == NULL) )
    {
        m32CamCalDataValidation = CAM_CAL_ERR_NO_DEVICE;
        CAM_CAL_DRV_LOG_IF(dumpEnable,"[CAM_CAL_ERR_NO_DEVICE]0x%x \n",m32CamCalDataValidation);
        CAM_CAL_DRV_LOG_IF(dumpEnable,"i4SensorDevId(0x%8x),a_eCamCalDataType(0x%8x),a_pCamCalData(0x%8x) \n", i4SensorDevId, a_eCamCalDataType, a_pCamCalData);

        return m32CamCalDataValidation;
    }
    //finish data extraction from CamCal
#if 0
    if(!bfFirstCalData)
    {
        Init(u4SensorID,a_pCamCalData);
        bfFirstCalData = TRUE;KK
    }
#endif

    CAM_CAL_DRV_LOG_IF(dumpEnable, "Get the sensor id of sensor dev: %d \n", i4SensorDevId);



    // Get the sensor id via IHalSenor
    MUINT32 sensorArray[1] = {0};
    IHalSensorList* const pSensorList = IHalSensorList::get();
    SensorStaticInfo senStaticInfo;


    //pSensorList->searchSensors(); // Must call search sensor before query sensor static info
#if 1

    switch (i4SensorDevId)
    {
        // Get the sensor id of senosr
        case SENSOR_DEV_MAIN:
        case SENSOR_DEV_SUB:
        case SENSOR_DEV_MAIN_2:
            pSensorList->querySensorStaticInfo(i4SensorDevId, &senStaticInfo);
            i4CurrSensorId = senStaticInfo.sensorDevID;
            CAM_CAL_DRV_LOG_IF(dumpEnable, "i4CurrSensorId 0x%x...", i4CurrSensorId);
            break;
        case SENSOR_DEV_MAIN_3D:
            pSensorList->querySensorStaticInfo(SENSOR_DEV_MAIN, &senStaticInfo);
            i4CurrSensorId = senStaticInfo.sensorDevID;
            CAM_CAL_DRV_LOG_IF(dumpEnable, "i4CurrSensorId 0x%x...", i4CurrSensorId);
            break;

        default:
            break;
    }

    CAM_CAL_DRV_LOG_IF(dumpEnable, "Start to get CamCal data!! CamCalDrv::GetCamCalCalData()..... \n");


    switch(a_eCamCalDataType) {
        case CAMERA_CAM_CAL_DATA_MODULE_VERSION:            //seanlin 121016 it's for user to get info. of single module or N3D module
        case CAMERA_CAM_CAL_DATA_PART_NUMBER:                      //seanlin 121016 return 5x4 byes gulPartNumberRegCamCal[5]
        case CAMERA_CAM_CAL_DATA_SHADING_TABLE:                  //seanlin 121016 return SingleLsc or N3DLsc
        case CAMERA_CAM_CAL_DATA_3A_GAIN:                              //seanlin 121016 return Single2A or N3D3A
        case CAMERA_CAM_CAL_DATA_3D_GEO:                               //seanlin 121016 return none or N3D3D
            pCamcalData->Command = a_eCamCalDataType;
            #ifdef CAM_CAL_SUPPORT  //seanlin 120919 it's for compiling mt6589fpga_ca7_ldvt
            m32CamCalDataValidation= GetCameraCalData(i4CurrSensorId, (MUINT32*)pCamcalData);
            #else
            m32CamCalDataValidation = CamCalReturnErr[a_eCamCalDataType];//CAM_CAL_ERR_NO_SHADING; //seanlin 120716 CamCal driver w.o. camera_custom_msdk.cpp
            #endif
        break;
        default:
            m32CamCalDataValidation = CAM_CAL_ERR_NO_CMD;
            CAM_CAL_DRV_ERR("Unknown cam_cal command 0x%x\n",a_eCamCalDataType);
        break;
    }

    // Dump error messages
    CAM_CAL_DRV_LOG_IF(dumpEnable,"All CAM_CAL ERROR if any .\n");
    for(mulIdx = 0; mulIdx < CAMERA_CAM_CAL_DATA_LIST; mulIdx++)
    {
        if(m32CamCalDataValidation & CamCalReturnErr[mulIdx])
            CAM_CAL_DRV_LOG_IF(dumpEnable,"Return ERROR %s\n",CamCalErrString[mulIdx]);
    }


    memcpy((UINT8*)la_pCamCalData, (UINT8*)pCamcalData, sizeof(CAM_CAL_DATA_STRUCT));
    CAM_CAL_DRV_LOG_IF(dumpEnable, "Done get CamCal data!! CamCalDrv::GetCamCalCalData()..... \n");

    return m32CamCalDataValidation;
#else
    return CAM_CAL_ERR_NO_DEVICE;
#endif
}

/*******************************************************************************
*
********************************************************************************/

int
CamCalDrv::Init(unsigned long u4SensorID,void *a_pCamCalData)
{
#if 0
    PCAM_CAL_DATA_STRUCT pCamcalData = &StCamCalCaldata;
    PGET_SENSOR_CALIBRATION_DATA_STRUCT la_pCamCalData = (PGET_SENSOR_CALIBRATION_DATA_STRUCT)a_pCamCalData;
    MUINT32 i;
    CAM_CAL_DRV_LOG("CamCalDrv::Init \n");

#ifdef CAM_CAL_SUPPORT  //seanlin 120919 it's for compiling mt6589fpga_ca7_ldvt
    m32CamCalDataValidation= GetCameraCalData(u4SensorID,(MUINT32*)pCamcalData);
#else
    m32CamCalDataValidation = CAM_CAL_ERR_NO_DATA|CAM_CAL_UNKNOWN; //seanlin 120716 CamCal driver w.o. camera_custom_msdk.cpp
#endif

    if((&pCamcalData->Shading!=NULL&&(pCamcalData->Shading.ISPComm.CommReg[CAM_CAL_INFO_IN_COMM_LOAD]!=CAL_DATA_LOAD))&&(!(m32CamCalDataValidation&CAM_CAL_ERR_NO_SHADING)))
    {
        CAM_CAL_DRV_LOG("CamCommShadingTableConvert()add= 0x%x\n", (unsigned int)&pCamcalData->Shading);
        CamCommShadingTableConvert((PCAM_CAL_SHADING_STRUCT)&pCamcalData->Shading);
    }
    if(m32CamCalDataValidation == 0xFF)
    {
        m32CamCalDataValidation =CAM_CAL_ERR_NO_DATA|CAM_CAL_UNKNOWN;
        CAM_CAL_DRV_LOG("m32CamCalDataValidation= 0x%x\n", m32CamCalDataValidation);
    }
    la_pCamCalData->pCameraPara->ISPComm.CommReg[CAM_CAL_INFO_IN_COMM_LOAD] = pCamcalData->Shading.ISPComm.CommReg[CAM_CAL_INFO_IN_COMM_LOAD] ; //sync the ISP data
#endif
    return m32CamCalDataValidation;
}



