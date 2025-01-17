package com.mediatek.crossmountsettings.util;

import android.app.Dialog;

/**
 * Letting the class, assumed to be Fragment, create a Dialog on it. Should be
 * useful you want to utilize some capability in
 * {@link SettingsPreferenceFragment} but don't want the class inherit the class
 * itself (See {@link ProxySelector} for example).
 */
public interface DialogCreatable {

    public Dialog onCreateDialog(int dialogId);
}
