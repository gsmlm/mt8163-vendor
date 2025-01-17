/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein is
 * confidential and proprietary to MediaTek Inc. and/or its licensors. Without
 * the prior written permission of MediaTek inc. and/or its licensors, any
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

#include "CallbackUTNode.h"

namespace NSCam{
namespace NSCamFeature{
namespace NSFeaturePipe{

CallbackUTNode::CallbackUTNode(const char* name, UTNodeCallback CB)
:DepthMapPipeNode(name, NULL)
{
    mpCB = CB;
}

CallbackUTNode::~CallbackUTNode()
{}

MVOID
CallbackUTNode::
setWaitingDataIDAndReqID(vector<DataID> vWaitIDs, vector<MUINT32> vWaitReqIDs)
{
    mvWaitIDs = vWaitIDs;

    mReqReadyMap.clear();
    for(auto ReqID : vWaitReqIDs)
    {
        DataIDValidPair waitIDPair;
        mReqReadyMap[ReqID] = waitIDPair;

        for(auto WaitID : mvWaitIDs)
        {
            mReqReadyMap[ReqID].mReadyMap[WaitID] = false;
            MY_LOGD("ReqID: %d set waiting ID : %d to false.", ReqID, WaitID);
        }
    }
}



MBOOL
CallbackUTNode::
onData(DataID id, ImgInfoMapPtr &data)
{
    MY_LOGD("CallbackUTNode onData:  Data ID:%d", id);
    markDataIDReady(data->getRequestPtr()->getRequestNo(), id);
    return MTRUE;
}

MBOOL
CallbackUTNode::
onData(DataID id, FrameInfoPtr &data)
{
    MY_LOGD("CallbackUTNode onData:  Data ID:%d", id);
    markDataIDReady(data->getRequestNo(), id);
    return MTRUE;
}

MBOOL
CallbackUTNode::onInit()
{
    return MTRUE;
}

MBOOL
CallbackUTNode::onUninit()
{
    return MTRUE;
}

MBOOL
CallbackUTNode::onThreadLoop()
{
    return MTRUE;
}

MBOOL
CallbackUTNode::onThreadStart()
{
    return MTRUE;
}

MBOOL
CallbackUTNode::onThreadStop()
{
    return MTRUE;
}

MVOID
CallbackUTNode::
markDataIDReady(MUINT32 ReqID, DataID id)
{
    map<MUINT32, DataIDValidPair>::iterator itr = mReqReadyMap.find(ReqID);
    if(itr != mReqReadyMap.end())
    {
        mReqReadyMap[ReqID].mReadyMap[id] = true;
        bool bAllReady=true;

        map<DataID, bool>::iterator data_itr;
        for(data_itr=mReqReadyMap[ReqID].mReadyMap.begin();data_itr!=mReqReadyMap[ReqID].mReadyMap.end();data_itr++)
        {
            if(data_itr->second==false)
            {
                MY_LOGD("Not ready dataID:%d", data_itr->first);
                bAllReady = false;
                break;
            }
        }

        // if all ready, callback true
        if(bAllReady)
        {
            MY_LOGD("CallbackUTNode callback: Req=%d All ready!", ReqID);
            mpCB(true);
        }
    }
}

}; // NSFeaturePipe
}; // NSCamFeature
}; // NSCam