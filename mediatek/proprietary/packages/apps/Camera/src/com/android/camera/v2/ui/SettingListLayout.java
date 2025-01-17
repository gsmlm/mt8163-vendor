/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.android.camera.v2.ui;

import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AbsListView;
import android.widget.AbsListView.OnScrollListener;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.FrameLayout;
import android.widget.ListView;

import com.android.camera.R;
import com.android.camera.v2.uimanager.preference.ListPreference;
import com.android.camera.v2.util.CameraUtil;
import com.android.camera.v2.util.SettingKeys;
import com.mediatek.camera.debug.LogHelper;
import com.mediatek.camera.debug.LogHelper.Tag;


import java.util.ArrayList;

//import com.mediatek.common.featureoption.FeatureOption;

/* A popup window that contains several camera settings. */
public class SettingListLayout extends FrameLayout implements InLineSettingItem.Listener,
        AdapterView.OnItemClickListener, OnScrollListener {
    private static final Tag TAG = new Tag(SettingListLayout.class.getSimpleName());
    private Listener                            mListener;
    private ArrayList<ListPreference>           mListItem = new ArrayList<ListPreference>();
    private ArrayAdapter<ListPreference>        mListItemAdapter;
    private InLineSettingItem                   mLastItem;
    private ListView                            mSettingList;
    private ViewGroup                           mRootView;

    public interface Listener {
        void onSettingChanged(SettingListLayout settingList, ListPreference preference);
        public void onRestoreSetting();
    }

    @Override
    protected void onFinishInflate() {
        super.onFinishInflate();
        mSettingList = (ListView) findViewById(R.id.settingList);
    }

    public void setRootView(ViewGroup root) {
        mRootView = root;
    }

    private class SettingsListAdapter extends ArrayAdapter<ListPreference> {
        LayoutInflater mInflater;

        public SettingsListAdapter() {
            super(SettingListLayout.this.getContext(), 0, mListItem);
            mInflater = LayoutInflater.from(getContext());
        }

        private int getSettingLayoutId(ListPreference pref) {
            // If the preference is null, it will be the only item , i.e.
            // 'Restore setting' in the popup window.
            if (pref == null) {
                return R.layout.in_line_setting_restore_v2;
            }

            // Currently, the RecordLocationPreference is the only setting
            // which applies the on/off switch.
            if (isSwitchSettingItem(pref)) {
                return R.layout.in_line_setting_switch_v2;
            } else if (isVirtualSettingItem(pref)) {
                return R.layout.in_line_setting_virtual_v2;
            } else if (isSwitchVirtualItem(pref)) {
                return R.layout.in_line_setting_switch_virtual_v2;
            }
            return R.layout.in_line_setting_sublist_v2;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            ListPreference pref = mListItem.get(position);
            if (convertView != null) {
                if (pref == null) {
                    if (!(convertView instanceof InLineSettingRestore)) {
                        convertView = null;
                    }
                } else if (isSwitchSettingItem(pref)) {
                    if (!(convertView instanceof InLineSettingSwitch)) {
                        convertView = null;
                    }
                } else if (isVirtualSettingItem(pref)) {
                    if (!(convertView instanceof InLineSettingVirtual)) {
                        convertView = null;
                    }
                } else if (isSwitchVirtualItem(pref)) {
                    if (!(convertView instanceof InLineSettingSwitchVirtual)) {
                        convertView = null;
                    }
                } else {
                    if (!(convertView instanceof InLineSettingSublist)) {
                        convertView = null;
                    }
                }
                if (convertView != null) {
                    ((InLineSettingItem) convertView).initialize(pref);
                    CameraUtil.setEnabledState(convertView,
                            (pref == null ? true : pref.isEnabled()));
                    return convertView;
                }
            }

            int viewLayoutId = getSettingLayoutId(pref);
            InLineSettingItem view = (InLineSettingItem) mInflater.inflate(viewLayoutId, parent,
                    false);
            if (viewLayoutId == R.layout.in_line_setting_restore) {
                view.setId(R.id.restore_default);
            }
            view.setRootView(mRootView);
            view.initialize(pref); // no init for restore one
            view.setSettingChangedListener(SettingListLayout.this);
            CameraUtil.setEnabledState(convertView, (pref == null ? true : pref.isEnabled()));
            return view;
        }
    }

    private boolean isSwitchSettingItem(ListPreference pref) {
        return SettingKeys.KEY_RECORD_LOCATION.equals(pref.getKey())
                || SettingKeys.KEY_VIDEO_RECORD_AUDIO.equals(pref.getKey())
                || SettingKeys.KEY_VIDEO_EIS.equals(pref.getKey())
                || SettingKeys.KEY_VIDEO_3DNR.equals(pref.getKey())
                || SettingKeys.KEY_CAMERA_ZSD.equals(pref.getKey())
                || SettingKeys.KEY_VOICE.equals(pref.getKey())
                || SettingKeys.KEY_CAMERA_FACE_DETECT.equals(pref.getKey())
                || SettingKeys.KEY_HDR.equals(pref.getKey())
                || SettingKeys.KEY_GESTURE_SHOT.equals(pref.getKey())
                || SettingKeys.KEY_SMILE_SHOT.equals(pref.getKey())
                || SettingKeys.KEY_SLOW_MOTION.equals(pref.getKey())
                || SettingKeys.KEY_CAMERA_AIS.equals(pref.getKey())
                || SettingKeys.KEY_ASD.equals(pref.getKey())
                || SettingKeys.KEY_DNG.equals(pref.getKey());
    }

    private boolean isVirtualSettingItem(ListPreference pref) {
        return SettingKeys.KEY_IMAGE_PROPERTIES.equals(pref.getKey())
                || SettingKeys.KEY_FACE_BEAUTY_PROPERTIES.equals(pref.getKey());
    }

    private boolean isSwitchVirtualItem(ListPreference pref) {
        return SettingKeys.KEY_DUAL_CAMERA_MODE.equals(pref.getKey());
    }

    public void setSettingChangedListener(Listener listener) {
        mListener = listener;
    }

    public SettingListLayout(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public void initialize(ArrayList<ListPreference> listItems) {
        mListItem = listItems;

        mListItemAdapter = new SettingsListAdapter();
        mSettingList.setAdapter(mListItemAdapter);
        mSettingList.setOnItemClickListener(this);
        mSettingList.setSelector(android.R.color.transparent);
        mSettingList.setOnScrollListener(this);
    }

    @Override
    public void onSettingChanged(InLineSettingItem item, ListPreference preference) {
        if (mLastItem != null && mLastItem != item) {
            mLastItem.collapseChild();
        }
        if (mListener != null) {
            preference.setOverrideValue(null, false);
            mListener.onSettingChanged(this, preference);
        }
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        if ((position == mListItem.size() - 1) && (mListener != null)) {
            mListener.onRestoreSetting();
        }
    }

    public void reloadPreference() {
        int count = mSettingList.getChildCount();
        for (int i = 0; i < count; i++) {
            ListPreference pref = mListItem.get(i);
            if (pref != null) {
                InLineSettingItem settingItem = (InLineSettingItem) mSettingList.getChildAt(i);
                settingItem.reloadPreference();
            }
        }
    }

    @Override
    public void onDismiss(InLineSettingItem item) {
        LogHelper.v(TAG, "onDismiss(" + item + ") mLastItem=" + mLastItem);
        mLastItem = null;
    }

    @Override
    public void onShow(InLineSettingItem item) {
        LogHelper.d(TAG, "onShow(" + item + ") mLastItem=" + mLastItem);
        if (mLastItem != null && mLastItem != item) {
            mLastItem.collapseChild();
        }
        mLastItem = item;
    }

   /* @Override
    public void onVoiceCommandChanged(int index) {
        if (mListener != null) {
            mListener.onVoiceCommandChanged(index);
        }
    }

    @Override
    public void onStereoCameraSettingChanged(InLineSettingItem item,
         ListPreference preference, int index, boolean showing) {
        if (mLastItem != null && mLastItem != item) {
            mLastItem.collapseChild();
        }
        if (mListener != null) {
            mListener.onStereoCameraSettingChanged(this, preference, index, showing);
        }
    }*/

    public boolean collapseChild() {
        boolean collapse = false;
        if (mLastItem != null) {
            collapse = mLastItem.collapseChild();
        }
        LogHelper.d(TAG, "collapseChild() return " + collapse);
        return collapse;
    }

    @Override
    public void onScroll(AbsListView view, int firstVisibleItem, int visibleItemCount,
            int totalItemCount) {
        LogHelper.d(TAG, "onScroll(" + firstVisibleItem + ", "
            + visibleItemCount + ", " + totalItemCount + ")");
    }

    @Override
    public void onScrollStateChanged(AbsListView view, int scrollState) {
        LogHelper.d(TAG, "onScrollStateChanged(" + scrollState + ")");
        if (scrollState == SCROLL_STATE_TOUCH_SCROLL) {
            collapseChild();
        }
    }
}
