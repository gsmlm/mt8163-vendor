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

package com.mediatek.engineermode.io;

import android.content.res.Resources;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;

import com.mediatek.engineermode.ChipSupport;
import com.mediatek.engineermode.R;
import com.mediatek.engineermode.ShellExe;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * Class for MSDC driving set
 *
 */
public class MsdcDrivSet extends MsdcTest implements OnClickListener {

    private static final String TAG = "MSDC_IOCTL";

    private static final int DATA_BIT = 0xF;
    private static final int OFFSET_FOUR_BIT = 4;
    private static final int OFFSET_EIGHT_BIT = 8;
    private static final int OFFSET_TWELVE_BIT = 12;
    private static final int OFFSET_SIXTEEN_BIT = 16;
    private static final int OFFSET_TWENTY_BIT = 20;
    private static final int OFFSET_RST_BIT = 24;
    private static final int OFFSET_DS_BIT = 28;
    private static final String CMD_GET_PRE = "echo 6 0 ";
    private static final String CMD_SET_PRE = "echo 6 1 ";
    private static final String CMD_SPACE = " ";
    private static final String CMD_WRITE_TO = ">";
    private static final String CMD_TAR_FILE = "/proc/msdc_debug";
    private static final String CMD_READ_RESULT = "cat /proc/msdc_debug";

    private Spinner mHostSpinner;
    private int mHostIndex = 0;

    private Spinner mClkPuSpinner;
    private int mClkPuIndex = 0;

    private Spinner mClkPdSpinner;
    private int mClkPdIndex = 0;

    private Spinner mCmdPuSpinner;
    private int mCmdPuIndex = 0;

    private Spinner mCmdPdSpinner;
    private int mCmdPdIndex = 0;

    private Spinner mDataPuSpinner;
    private int mDataPuIndex = 0;

    private Spinner mDataPdSpinner;
    private int mDataPdIndex = 0;

    private Spinner mRstPuSpinner;
    private int mRstPuIndex = 0;

    private int mRstPdIndex = 0;

    private Spinner mDsPuSpinner;
    private int mDsPuIndex = 0;

    private int mDsPdIndex = 0;

    private Spinner mVoltageSpinner;
    private int mVoltageIndex = 0;

    private Button mBtnGet;
    private Button mBtnSet;

    private TextView mTvResult;

    private int mChipId;

    @Override
    public void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.msdc_driving_set);
        mChipId = ChipSupport.getChip();
        Log.i("@M_" + TAG, "Chip ID " + mChipId);
        mBtnGet = (Button) findViewById(R.id.NEW_MSDC_Get);
        mBtnSet = (Button) findViewById(R.id.NEW_MSDC_Set);
        mTvResult = (TextView) findViewById(R.id.MSDC_result_text);

        mHostSpinner = (Spinner) findViewById(R.id.NEW_MSDC_HOST_sppiner);

        mClkPuSpinner = (Spinner) findViewById(R.id.MSDC_Clk_pu_spinner);
        mClkPdSpinner = (Spinner) findViewById(R.id.MSDC_clk_pd_spinner);

        mCmdPuSpinner = (Spinner) findViewById(R.id.MSDC_cmd_pu_spinner);
        mCmdPdSpinner = (Spinner) findViewById(R.id.MSDC_cmd_pd_spinner);

        mDataPuSpinner = (Spinner) findViewById(R.id.MSDC_data_pu_spinner);
        mDataPdSpinner = (Spinner) findViewById(R.id.MSDC_data_pd_spinner);

        mRstPuSpinner = (Spinner) findViewById(R.id.MSDC_rst_pu_spinner);
        mDsPuSpinner = (Spinner) findViewById(R.id.MSDC_ds_pu_spinner);

        mVoltageSpinner = (Spinner) findViewById(R.id.MSDC_voltage_pu_spinner);
        mBtnGet.setOnClickListener(this);
        mBtnSet.setOnClickListener(this);
        Resources res = getResources();
        String[] itemArray = res.getStringArray(R.array.host_type);
        ArrayList<String> itemList = new ArrayList<String>();
        for (int i = 0; i < itemArray.length - 1; i++) {
            itemList.add(itemArray[i]);
        }


        if (ChipSupport.MTK_6589_SUPPORT <= mChipId) {
            itemList.add(itemArray[itemArray.length - 1]);

            TextView tempView = null;
            tempView = (TextView) findViewById(R.id.MSDC_Clk_pu_text);
            tempView.setText(R.string.NEW_MSDC_CLK);
            tempView = (TextView) findViewById(R.id.MSDC_Cmd_pu_text);
            tempView.setText(R.string.NEW_MSDC_CMD);
            tempView = (TextView) findViewById(R.id.MSDC_Data_pu_text);
            tempView.setText(R.string.NEW_MSDC_DATA);
            findViewById(R.id.MSDC_Clk_pd_text).setVisibility(View.GONE);
            findViewById(R.id.MSDC_Cmd_pd_text).setVisibility(View.GONE);
            findViewById(R.id.MSDC_Data_pd_text).setVisibility(View.GONE);
            mClkPdSpinner.setVisibility(View.GONE);
            mCmdPdSpinner.setVisibility(View.GONE);
            mDataPdSpinner.setVisibility(View.GONE);
        }
        if (ChipSupport.MTK_6595_SUPPORT > mChipId) {
            findViewById(R.id.MSDC_Rst_pu_text).setVisibility(View.GONE);
            findViewById(R.id.MSDC_Ds_pu_text).setVisibility(View.GONE);
            mRstPuSpinner.setVisibility(View.GONE);
            mDsPuSpinner.setVisibility(View.GONE);
        }

        if (ChipSupport.isChipInSet(ChipSupport.CHIP_657X_SERIES_NEW)) {
            // 72 series only have host 0 & 1
            for (int j = itemList.size() - 1; itemList.size() > 2; j--) {
                itemList.remove(j);
            }
            if (ChipSupport.isCurrentChipEquals(ChipSupport.MTK_6572_SUPPORT)) {
                ((TextView) findViewById(R.id.MSDC_Cmd_pu_text)).setVisibility(View.GONE);
                mCmdPuSpinner.setVisibility(View.GONE);
                ((TextView) findViewById(R.id.MSDC_Data_pu_text)).setVisibility(View.GONE);
                mDataPuSpinner.setVisibility(View.GONE);
                ((TextView) findViewById(R.id.MSDC_Clk_pu_text)).setText(
                        getString(R.string.NEW_MSDC_CLK) + " / " +
                        getString(R.string.NEW_MSDC_CMD) + " / " +
                        getString(R.string.NEW_MSDC_DATA));
            }
        }

        ArrayAdapter<String> hostAdapter;
        if (mChipId != ChipSupport.MTK_6797_SUPPORT) {
            ((TextView) findViewById(R.id.MSDC_Voltage_pu_text)).setVisibility(View.GONE);
            mVoltageSpinner.setVisibility(View.GONE);
            ((TextView) findViewById(R.id.MSDC_result_title)).setVisibility(View.GONE);
            mTvResult.setVisibility(View.GONE);
            hostAdapter = new ArrayAdapter<String>(this,
                    android.R.layout.simple_spinner_item, itemList);

        } else {
            hostAdapter = new ArrayAdapter<String>(this,
                    android.R.layout.simple_spinner_item, res
                    .getStringArray(R.array.host_id_number));
        }

        hostAdapter
                .setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        mHostSpinner.setAdapter(hostAdapter);

        mHostSpinner.setOnItemSelectedListener(mSpinnerListener);

        ArrayAdapter<String> commonAdapter = new ArrayAdapter<String>(this,
                android.R.layout.simple_spinner_item, res
                        .getStringArray(R.array.command_data));
        commonAdapter
                .setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        mClkPuSpinner.setAdapter(commonAdapter);
        mClkPuSpinner.setOnItemSelectedListener(mSpinnerListener);

        mClkPdSpinner.setAdapter(commonAdapter);
        mClkPdSpinner.setOnItemSelectedListener(mSpinnerListener);

        mCmdPuSpinner.setAdapter(commonAdapter);
        mCmdPuSpinner.setOnItemSelectedListener(mSpinnerListener);

        mCmdPdSpinner.setAdapter(commonAdapter);
        mCmdPdSpinner.setOnItemSelectedListener(mSpinnerListener);

        mDataPuSpinner.setAdapter(commonAdapter);
        mDataPuSpinner.setOnItemSelectedListener(mSpinnerListener);

        mDataPdSpinner.setAdapter(commonAdapter);
        mDataPdSpinner.setOnItemSelectedListener(mSpinnerListener);

        mRstPuSpinner.setAdapter(commonAdapter);
        mRstPuSpinner.setOnItemSelectedListener(mSpinnerListener);

        mDsPuSpinner.setAdapter(commonAdapter);
        mDsPuSpinner.setOnItemSelectedListener(mSpinnerListener);

        mHostSpinner.setSelection(0);

        ArrayAdapter<String> voltageAdapter = new ArrayAdapter<String>(this,
                android.R.layout.simple_spinner_item, res
                        .getStringArray(R.array.msdc_voltage));
        voltageAdapter
                .setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        mVoltageSpinner.setAdapter(voltageAdapter);
        mVoltageSpinner.setOnItemSelectedListener(mSpinnerListener);
    }


    @SuppressWarnings("deprecation")
    @Override
    public void onClick(View arg0) {

        if (mChipId == ChipSupport.MTK_6797_SUPPORT) {
            if (arg0.getId() == mBtnGet.getId()) {
                StringBuilder strCmd = new StringBuilder(CMD_GET_PRE);
                strCmd.append(mHostIndex).append(CMD_SPACE).append(CMD_WRITE_TO)
                .append(CMD_SPACE).append(CMD_TAR_FILE);
                Log.i(TAG, "Get CMD: " + strCmd);
                try {
                    if (ShellExe.execCommand(strCmd.toString()) != ShellExe.RESULT_SUCCESS) {
                        showDialog(EVENT_GET_FAIL_ID);
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }

            } else if (arg0.getId() == mBtnSet.getId()) {
                StringBuilder strCmd = new StringBuilder(CMD_SET_PRE);
                strCmd.append(mHostIndex).append(CMD_SPACE).append(mClkPuIndex).
                append(CMD_SPACE).append(mCmdPuIndex).append(CMD_SPACE).append(mDataPuIndex)
                .append(CMD_SPACE).append(mRstPuIndex).append(CMD_SPACE).append(mDsPuIndex)
                .append(CMD_SPACE).append(mVoltageIndex).append(CMD_SPACE)
                .append(CMD_WRITE_TO).append(CMD_SPACE).append(CMD_TAR_FILE);
                Log.i(TAG, "Set CMD: " + strCmd);
                try {
                    if (ShellExe.execCommand(strCmd.toString()) != ShellExe.RESULT_SUCCESS) {
                        showDialog(EVENT_SET_FAIL_ID);
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }

            } else {
                return;
            }

            try {
                if (ShellExe.execCommand(CMD_READ_RESULT) == ShellExe.RESULT_SUCCESS) {
                    String result = ShellExe.getOutput().trim();
                    mTvResult.setText(result);
                } else {
                    showDialog(EVENT_READ_RESULT_FAIL_ID);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }


        } else {
            if (arg0.getId() == mBtnGet.getId()) {
                Log.i("@M_" + TAG, "SD_IOCTL: click GetCurrent");
                int idx = EmGpio.newGetCurrent(mHostIndex, 0);
                if (idx != -1) {
                    int clkpuIdx = idx & DATA_BIT;
                    int clkpdIdx = (idx >> OFFSET_FOUR_BIT) & DATA_BIT;
                    int cmdpuIdx = (idx >> OFFSET_EIGHT_BIT) & DATA_BIT;
                    int cmdpdIdx = (idx >> OFFSET_TWELVE_BIT) & DATA_BIT;
                    int datapuIdx = (idx >> OFFSET_SIXTEEN_BIT) & DATA_BIT;
                    int datapdIdx = (idx >> OFFSET_TWENTY_BIT) & DATA_BIT;
                    int rstpuIdx = (idx >> OFFSET_RST_BIT) & DATA_BIT;
                    int dspuIdx = (idx >> OFFSET_DS_BIT) & DATA_BIT;

                    mClkPuSpinner.setSelection(clkpuIdx);
                    mCmdPuSpinner.setSelection(cmdpuIdx);
                    mDataPuSpinner.setSelection(datapuIdx);
                    mRstPuSpinner.setSelection(rstpuIdx);
                    mDsPuSpinner.setSelection(dspuIdx);
                    if (ChipSupport.MTK_6589_SUPPORT > mChipId) {
                        mClkPdSpinner.setSelection(clkpdIdx);
                        mCmdPdSpinner.setSelection(cmdpdIdx);
                        mDataPdSpinner.setSelection(datapdIdx);
                    }
                } else {
                    showDialog(EVENT_GET_FAIL_ID);
                }

            } else if (arg0.getId() == mBtnSet.getId()) {

                boolean ret = EmGpio.newSetCurrent(mHostIndex, mClkPuIndex,
                        mClkPdIndex, mCmdPuIndex, mCmdPdIndex, mDataPuIndex,
                        mDataPdIndex, mRstPuIndex, mRstPdIndex, mDsPuIndex, mDsPdIndex, 0, 0, 0);
                if (ret) {
                    showDialog(EVENT_SET_OK_ID);
                } else {
                    showDialog(EVENT_SET_FAIL_ID);
                }
            }
        }



    }

    private void handleHostSelected(int position) {
        if (ChipSupport.isCurrentChipEquals(ChipSupport.MTK_6571_SUPPORT)) {
            List<String> valList = new ArrayList<String>();
            int maxVal = 7;
            if (position == 1) {
                maxVal = 3;
            }
            for (int i = 0; i <= maxVal; i++) {
                valList.add(String.valueOf(i));
            }
            ArrayAdapter<String> commonAdapter = new ArrayAdapter<String>(this,
                    android.R.layout.simple_spinner_item, valList);
            commonAdapter
                    .setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

            mClkPuSpinner.setAdapter(commonAdapter);
            mClkPuSpinner.setOnItemSelectedListener(mSpinnerListener);

            mCmdPuSpinner.setAdapter(commonAdapter);
            mCmdPuSpinner.setOnItemSelectedListener(mSpinnerListener);

            mDataPuSpinner.setAdapter(commonAdapter);
            mDataPuSpinner.setOnItemSelectedListener(mSpinnerListener);
        }
    }

    private final OnItemSelectedListener mSpinnerListener = new OnItemSelectedListener() {

        public void onItemSelected(AdapterView<?> arg0, View arg1, int arg2,
                long arg3) {
            switch (arg0.getId()) {
            case R.id.NEW_MSDC_HOST_sppiner:
                mHostIndex = arg2;
                handleHostSelected(mHostIndex);
                break;
            case R.id.MSDC_Clk_pu_spinner:
                mClkPuIndex = arg2;
                break;
            case R.id.MSDC_clk_pd_spinner:
                mClkPdIndex = arg2;
                break;
            case R.id.MSDC_cmd_pu_spinner:
                mCmdPuIndex = arg2;
                break;
            case R.id.MSDC_cmd_pd_spinner:
                mCmdPdIndex = arg2;
                break;
            case R.id.MSDC_data_pu_spinner:
                mDataPuIndex = arg2;
                break;
            case R.id.MSDC_data_pd_spinner:
                mDataPdIndex = arg2;
                break;
            case R.id.MSDC_rst_pu_spinner:
                mRstPuIndex = arg2;
                break;
            case R.id.MSDC_ds_pu_spinner:
                mDsPuIndex = arg2;
                break;
            case R.id.MSDC_voltage_pu_spinner: {
                mVoltageIndex = (arg2 == 0) ? 1 : 0;
                break;
            }
            default:
                break;
            }
        }

        public void onNothingSelected(AdapterView<?> arg0) {
            Log.v("@M_" + TAG, "Spinner nothing selected");
        }

    };
}
