/*******************************************************************************
 * Software Name : RCS IMS Stack
 *
 * Copyright (C) 2010 France Telecom S.A.
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
 ******************************************************************************/

package com.orangelabs.rcs.addressbook;

import com.orangelabs.rcs.provider.eab.ContactsManager;
import com.orangelabs.rcs.utils.logger.Logger;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

/**
 * The device's locale has changed
 */
public class LocaleChangedReceiver extends BroadcastReceiver {
    
    /**
     * The logger
     */
    private Logger logger = Logger.getLogger(this.getClass().getName());

    @Override
    public void onReceive(Context context, Intent intent) {
        if (logger.isActivated()){
            logger.debug("The Locale has changed, we update the RCS strings in Contacts");
        }
        
        // We have to modify the strings that are used in contacts manager
        ContactsManager.createInstance(context);
        ContactsManager.getInstance().updateStrings();
    }
}
