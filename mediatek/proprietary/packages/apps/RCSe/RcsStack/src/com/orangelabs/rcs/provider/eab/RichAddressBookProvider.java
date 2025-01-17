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

package com.orangelabs.rcs.provider.eab;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;

import android.content.ContentProvider;
import android.content.ContentUris;
import android.content.ContentValues;
import android.content.Context;
import android.content.UriMatcher;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.database.sqlite.SQLiteQueryBuilder;
import android.net.Uri;
import android.os.Environment;
import android.os.ParcelFileDescriptor;
import android.text.TextUtils;

import com.orangelabs.rcs.core.ims.service.ContactInfo;
import com.orangelabs.rcs.provider.ipcall.IPCallProvider;
import com.orangelabs.rcs.provider.settings.RcsSettingsProvider;
import com.orangelabs.rcs.utils.logger.Logger;

/**
 * Rich address book provider
 *
 * <br>This provider contains the list of the RCS contacts and their status
 * <br>It is used by the AddressBookManager to keep the synchronization between the native address book and the RCS contacts.
 * 
 * <br>It also contains the list of aggregations between native raw contacts and rcs raw contacts
 */
public class RichAddressBookProvider extends ContentProvider {
    // Database table
    public static final String EAB_TABLE = "eab_contacts";
    public static final String AGGREGATION_TABLE = "aggregation";
    
    // Create the constants used to differentiate between the different URI requests
    private static final int CONTACTS = 1;
    private static final int CONTACT_ID = 2;
    private static final int AGGREGATIONS = 3;
    private static final int AGGREGATION_ID = 4;
    private static final int RCSAPI = 5;
    private static final int RCSAPI_ID = 6;
    
    // Allocate the UriMatcher object
    private static final UriMatcher uriMatcher;
    static {
        uriMatcher = new UriMatcher(UriMatcher.NO_MATCH);
        uriMatcher.addURI("com.orangelabs.rcs.eab", "eab", CONTACTS);
        uriMatcher.addURI("com.orangelabs.rcs.eab", "eab/#", CONTACT_ID);
        uriMatcher.addURI("com.orangelabs.rcs.eab", "aggregation", AGGREGATIONS);
        uriMatcher.addURI("com.orangelabs.rcs.eab", "aggregation/#", AGGREGATION_ID);
        uriMatcher.addURI("org.gsma.joyn.provider.capabilities", "capabilities", RCSAPI);
        uriMatcher.addURI("org.gsma.joyn.provider.capabilities", "capabilities/#", RCSAPI_ID);
    }

    /**
     * Database helper class
     */
    private DatabaseHelper openHelper;
    
    /**
     * The logger
     */
    private Logger logger = Logger.getLogger(this.getClass().getName());
    
    /**
     * Helper class for opening, creating and managing database version control
     */
    private static class DatabaseHelper extends SQLiteOpenHelper{
        private static final String DATABASE_NAME = "eab.db";
        private static final int DATABASE_VERSION = 21;
        
        public DatabaseHelper(Context context) {
            super(context, DATABASE_NAME, null, DATABASE_VERSION);
        }
            
        @Override
        public void onCreate(SQLiteDatabase db) {
            // Create the eab_contacts table
            createDb(db);
        }

        @Override
        public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
            db.execSQL("DROP TABLE IF EXISTS " + EAB_TABLE);
            db.execSQL("DROP TABLE IF EXISTS " + AGGREGATION_TABLE);
            onCreate(db);
        }

        private void createDb(SQLiteDatabase db) {
            db.execSQL("CREATE TABLE IF NOT EXISTS " + EAB_TABLE + " ("
                    + RichAddressBookData.KEY_ID + " integer primary key autoincrement, "
                    + RichAddressBookData.KEY_CONTACT_NUMBER + " TEXT, "
                    + RichAddressBookData.KEY_RCS_STATUS + " TEXT, "
                    + RichAddressBookData.KEY_RCS_STATUS_TIMESTAMP + " long, "
                    + RichAddressBookData.KEY_REGISTRATION_STATE + " integer, "
                    + RichAddressBookData.KEY_PRESENCE_SHARING_STATUS + " TEXT, "
                    + RichAddressBookData.KEY_PRESENCE_FREE_TEXT + " TEXT, "
                    + RichAddressBookData.KEY_PRESENCE_WEBLINK_NAME + " TEXT, "
                    + RichAddressBookData.KEY_PRESENCE_WEBLINK_URL + " TEXT, "
                    + RichAddressBookData.KEY_PRESENCE_PHOTO_EXIST_FLAG + " TEXT, "
                    + RichAddressBookData.KEY_PRESENCE_PHOTO_ETAG + " TEXT, "
                    + RichAddressBookData.KEY_PRESENCE_PHOTO_DATA + " TEXT, "
                    + RichAddressBookData.KEY_PRESENCE_GEOLOC_EXIST_FLAG + " TEXT, "
                    + RichAddressBookData.KEY_PRESENCE_GEOLOC_LATITUDE + " double, "
                    + RichAddressBookData.KEY_PRESENCE_GEOLOC_LONGITUDE + " double, "
                    + RichAddressBookData.KEY_PRESENCE_GEOLOC_ALTITUDE + " double, "
                    + RichAddressBookData.KEY_PRESENCE_TIMESTAMP + " long, "
                    + RichAddressBookData.KEY_CAPABILITY_TIMESTAMP + " long, "
                    + RichAddressBookData.KEY_CAPABILITY_CS_VIDEO + " integer, "
                    + RichAddressBookData.KEY_CAPABILITY_IMAGE_SHARING + " integer, "
                    + RichAddressBookData.KEY_CAPABILITY_VIDEO_SHARING + " integer, "
                    + RichAddressBookData.KEY_CAPABILITY_IM_SESSION + " integer, "
                    + RichAddressBookData.KEY_CAPABILITY_FILE_TRANSFER + " integer, "
                    + RichAddressBookData.KEY_CAPABILITY_PRESENCE_DISCOVERY + " integer, "
                    + RichAddressBookData.KEY_CAPABILITY_SOCIAL_PRESENCE + " integer, "
                    + RichAddressBookData.KEY_CAPABILITY_GEOLOCATION_PUSH + " integer, "
                    + RichAddressBookData.KEY_CAPABILITY_FILE_TRANSFER_HTTP + " integer, "
                    + RichAddressBookData.KEY_CAPABILITY_FILE_TRANSFER_THUMBNAIL + " integer, "
                    + RichAddressBookData.KEY_CAPABILITY_IP_VOICE_CALL + " integer, "
                    + RichAddressBookData.KEY_CAPABILITY_IP_VIDEO_CALL + " integer, "
                    + RichAddressBookData.KEY_CAPABILITY_IR94_VOICE_CALL + " integer, "
                    + RichAddressBookData.KEY_CAPABILITY_IR94_VIDEO_CALL + " integer, "
                    + RichAddressBookData.KEY_CAPABILITY_IR94_DUPLEX_MODE + " integer, "
                    + RichAddressBookData.KEY_CAPABILITY_FILE_TRANSFER_SF + " integer, "
                    + RichAddressBookData.KEY_CAPABILITY_GROUP_CHAT_SF + " integer, "                    
                    + RichAddressBookData.KEY_CAPABILITY_BURN_AFTER_READING + " integer, "
                    + RichAddressBookData.KEY_CAPABILITY_EXTENSIONS + " TEXT, "
                    + RichAddressBookData.KEY_IM_BLOCKED + " TEXT, "
                    + RichAddressBookData.KEY_CAPABILITY_IM_BLOCKED_TIMESTAMP + " long, "
                    + RichAddressBookData.KEY_TIMESTAMP + " long)");
            db.execSQL("CREATE TABLE IF NOT EXISTS " + AGGREGATION_TABLE + " ("
                    + AggregationData.KEY_ID + " integer primary key autoincrement, "
                    + AggregationData.KEY_RCS_NUMBER + " TEXT, "
                    + AggregationData.KEY_RAW_CONTACT_ID + " long, "
                    + AggregationData.KEY_RCS_RAW_CONTACT_ID + " long)");
        }
    }

    @Override 
    public boolean onCreate() {
        openHelper = new DatabaseHelper(getContext());
        return true;
    }

    @Override
    public int delete(Uri uri, String where, String[] whereArgs) {
        int count = 0;

        SQLiteDatabase db = openHelper.getWritableDatabase();
        switch(uriMatcher.match(uri)){
            case CONTACTS:
                count = db.delete(EAB_TABLE, where, whereArgs);
                break;

            case CONTACT_ID:
                String segment = uri.getPathSegments().get(1);
                count = db.delete(EAB_TABLE, RichAddressBookData.KEY_ID + "="
                        + segment
                        + (!TextUtils.isEmpty(where) ? " AND ("    + where + ')' : ""),
                        whereArgs);
                break;
                
            case AGGREGATIONS:
                count = db.delete(AGGREGATION_TABLE, where, whereArgs);
                break;

            case AGGREGATION_ID:
                segment = uri.getPathSegments().get(1);
                count = db.delete(AGGREGATION_TABLE, AggregationData.KEY_ID + "="
                        + segment
                        + (!TextUtils.isEmpty(where) ? " AND ("    + where + ')' : ""),
                        whereArgs);
                break;

            default:
                throw new IllegalArgumentException("Unsupported URI: " + uri);
        }

        getContext().getContentResolver().notifyChange(uri, null);
        return count;
    }

    @Override
    public String getType(Uri uri) {
        switch(uriMatcher.match(uri)){
            case CONTACTS:
            case RCSAPI:
                return "vnd.android.cursor.dir/eab";
            case CONTACT_ID:
            case RCSAPI_ID:
                return "vnd.android.cursor.item/eab";
            case AGGREGATIONS:
                return "vnd.android.cursor.dir/aggregation";
            case AGGREGATION_ID:
                return "vnd.android.cursor.item/aggregation";
            default:
                throw new IllegalArgumentException("Unsupported URI " + uri);
        }
    }

    @Override
    public Uri insert(Uri uri, ContentValues initialValues) {
        SQLiteDatabase db = openHelper.getWritableDatabase();
        switch(uriMatcher.match(uri)){
            case CONTACTS:
            case CONTACT_ID:
                // Insert the new row, will return the row number if successful
                long rowID = db.insert(EAB_TABLE, null, initialValues);

                // Return a URI to the newly inserted row on success
                if (rowID > 0) {
                    if (!initialValues.containsKey(RichAddressBookData.KEY_PRESENCE_PHOTO_DATA)) {
                        try {
                            String filename = "photoData" + rowID;
                            getContext().openFileOutput(filename, Context.MODE_PRIVATE).close();
                            String path = getContext().getFileStreamPath(filename).getAbsolutePath();
                            initialValues.put(RichAddressBookData.KEY_PRESENCE_PHOTO_DATA, path);
                            initialValues.put(RichAddressBookData.KEY_PRESENCE_PHOTO_EXIST_FLAG, RichAddressBookData.FALSE_VALUE);
                        } catch(Exception e) {
                            if (logger.isActivated()) {
                                logger.error("Problem while creating photoData", e);
                            }
                        }
                    }
                    rowID = db.update(EAB_TABLE, initialValues, RichAddressBookData.KEY_ID + "=" + rowID, null);

                    Uri newUri = ContentUris.withAppendedId(RichAddressBookData.CONTENT_URI, rowID);
                    getContext().getContentResolver().notifyChange(newUri, null);
                    return newUri;
                }
                break;
            case AGGREGATIONS:
            case AGGREGATION_ID:
                // Insert the new row, will return the row number if successful
                rowID = db.insert(AGGREGATION_TABLE, null, initialValues);

                // Return a URI to the newly inserted row on success
                if (rowID > 0) {
                    Uri newUri = ContentUris.withAppendedId(AggregationData.CONTENT_URI, rowID);
                    getContext().getContentResolver().notifyChange(newUri, null);
                    return newUri;
                }
                
                break;
            
        }
        
        throw new SQLException("Failed to insert row into " + uri);
    }

    @Override
    public Cursor query(Uri uri, String[] projection, String selection, String[] selectionArgs, String sort) {
        SQLiteQueryBuilder qb = new SQLiteQueryBuilder();

        String orderBy = sort;
        
        // Generate the body of the query
        int match = uriMatcher.match(uri);
        switch(match) {
            case CONTACTS:
                qb.setTables(EAB_TABLE);
                if (TextUtils.isEmpty(sort)){
                    orderBy = RichAddressBookData.KEY_CONTACT_NUMBER;
                }
                break;
            case CONTACT_ID:
                qb.setTables(EAB_TABLE);
                qb.appendWhere(RichAddressBookData.KEY_ID + "=" + uri.getPathSegments().get(1));
                if (TextUtils.isEmpty(sort)){
                    orderBy = RichAddressBookData.KEY_CONTACT_NUMBER;
                }
                break;
            case AGGREGATIONS:
                qb.setTables(AGGREGATION_TABLE);
                if (TextUtils.isEmpty(sort)){
                    orderBy = AggregationData.KEY_RCS_NUMBER;
                }
                break;
            case AGGREGATION_ID:
                qb.setTables(AGGREGATION_TABLE);
                qb.appendWhere(AggregationData.KEY_ID + "=" + uri.getPathSegments().get(1));
                if (TextUtils.isEmpty(sort)){
                    orderBy = AggregationData.KEY_RCS_NUMBER;
                }
                break;
            case RCSAPI:
                qb.setTables(EAB_TABLE);
                qb.appendWhere("(" + RichAddressBookData.KEY_RCS_STATUS + "<>" + ContactInfo.NO_INFO +
                        ") AND (" + RichAddressBookData.KEY_RCS_STATUS + "<>" + ContactInfo.NOT_RCS + ")");
                break;
            case RCSAPI_ID:
                qb.setTables(EAB_TABLE);
                qb.appendWhere(RichAddressBookData.KEY_ID + "=" + uri.getPathSegments().get(1));
                if (TextUtils.isEmpty(sort)){
                    orderBy = RichAddressBookData.KEY_CONTACT_NUMBER;
                }
                break;
            default:
                throw new IllegalArgumentException("Unknown URI " + uri);
        }

        // Apply the query to the underlying database.
        SQLiteDatabase db = openHelper.getWritableDatabase();
        Cursor c = qb.query(db, 
                projection, 
                selection, selectionArgs, 
                null, null,
                orderBy);

        // Register the contexts ContentResolver to be notified if
        // the cursor result set changes.
        if (c != null) {
            c.setNotificationUri(getContext().getContentResolver(), uri);
        }
        
        // Return a cursor to the query result
        return c;
    }

    @Override
    public int update(Uri uri, ContentValues values, String where, String[] whereArgs) {
        int count = 0;
        SQLiteDatabase db = openHelper.getWritableDatabase();

        int match = uriMatcher.match(uri);
        switch (match) {
            case CONTACTS:
                count = db.update(EAB_TABLE, values, where, whereArgs);
                break;
            case CONTACT_ID:
                String segment = uri.getPathSegments().get(1);
                count = db.update(EAB_TABLE, values, RichAddressBookData.KEY_ID + "="
                        + segment
                        + (!TextUtils.isEmpty(where) ? " AND (" + where + ')' : ""),
                        whereArgs);
                break;
            case AGGREGATIONS:
                count = db.update(AGGREGATION_TABLE, values, where, whereArgs);
                break;
            case AGGREGATION_ID:
                segment = uri.getPathSegments().get(1);
                count = db.update(AGGREGATION_TABLE, values, AggregationData.KEY_ID + "="
                        + segment
                        + (!TextUtils.isEmpty(where) ? " AND (" + where + ')' : ""),
                        whereArgs);
                break;
            default:
                throw new IllegalArgumentException("Unknown URI " + uri);
        }

        getContext().getContentResolver().notifyChange(uri, null);
        return count;
    }

    @Override
    public ParcelFileDescriptor openFile(Uri uri, String mode) throws FileNotFoundException {
        if (uriMatcher.match(uri) != CONTACT_ID) {
            throw new IllegalArgumentException("URI not supported for directories");
        }
        
        try {
            return this.openFileHelper(uri, mode);
        } catch (FileNotFoundException e) {
            if (logger.isActivated()) {
                logger.error("File not found exception", e);
            }
            throw new FileNotFoundException();
        }
    } 
    
     public static void backupAddressBookDatabase(String account) {
         
            try {
                String packageName = "com.orangelabs.rcs";
                String dbFile = Environment.getDataDirectory() + "/data/" + packageName + "/databases/" + RichAddressBookProvider.DatabaseHelper.DATABASE_NAME;
                File file = new File(dbFile);
                if (file.exists())
                {
                File backupFileRoot =new File( Environment.getExternalStorageDirectory()+"/Rcs" + "/data/" + packageName + "/databases/");
                backupFileRoot.mkdirs();
                File backupFile = new File(backupFileRoot, RichAddressBookProvider.DatabaseHelper.DATABASE_NAME +"_"+ account +".db");
                
                OutputStream outStream = new FileOutputStream(backupFile, false);
                InputStream inStream = new FileInputStream(dbFile);
                 byte[] buffer = new byte[1024];
                int length;
                while ((length = inStream.read(buffer))>0) {
                    outStream.write(buffer, 0, length);
                }
                outStream.flush();
                outStream.close();
                inStream.close();                
                }
            } catch(Exception e) {
                e.printStackTrace();
            }
        }
     public static void backupAddressBookDatabase(String account, String path) {
         
            try {
                String packageName = "com.orangelabs.rcs";
                String dbFile = Environment.getDataDirectory() + "/data/" + packageName + "/databases/" + RichAddressBookProvider.DatabaseHelper.DATABASE_NAME;
                File file = new File(dbFile);
                if (file.exists())
                {
                File backupFileRoot =new File(path);
                backupFileRoot.mkdirs();
                File backupFile = new File(backupFileRoot, RichAddressBookProvider.DatabaseHelper.DATABASE_NAME +"_"+ account +".db");
                
                OutputStream outStream = new FileOutputStream(backupFile, false);
                InputStream inStream = new FileInputStream(dbFile);
                 byte[] buffer = new byte[1024];
                int length;
                while ((length = inStream.read(buffer))>0) {
                    outStream.write(buffer, 0, length);
                }
                outStream.flush();
                outStream.close();
                inStream.close();                
                }
            } catch(Exception e) {
                e.printStackTrace();
            }
        }
     
     public static void restoreAddressBookDatabase(String account)
        {
            
            try {
                
                 /* if (logger.isActivated()) {
                   logger.debug("restoreAccountMessages : account:"+account);
                }*/
                
                String packageName = "com.orangelabs.rcs";
                String dbFile = Environment.getDataDirectory() + "/data/" + packageName + "/databases/" + RichAddressBookProvider.DatabaseHelper.DATABASE_NAME;
                File backupFileRoot =new File( Environment.getExternalStorageDirectory()+"/Rcs" + "/data/" + packageName + "/databases/");
                String restoreFile = backupFileRoot+"/" + RichAddressBookProvider.DatabaseHelper.DATABASE_NAME +"_"+ account +".db";

               // if(restoreFile.)

                File file = new File(restoreFile);
                if (!file.exists()) {
                //    if (logger.isActivated()) {
                         //logger.debug("error in restoreAccountMessages : account:"+account + "; "+restoreFile+" :file cant be created");
               //      }
                    return;
                }
                

                   //delete the original file 
                    File dbOriginalFile = new File(dbFile);
                  if (!dbOriginalFile.exists()) {
                              //     dbOriginalFile.delete();
                    dbOriginalFile.createNewFile();
                  } 

                  new FileOutputStream(dbFile,false).close();
                 // dbOriginalFile.createNewFile();
                OutputStream outStream = new FileOutputStream(dbFile, false);
                InputStream inStream = new FileInputStream(file);
                byte[] buffer = new byte[1024];
                int length;
                while ((length = inStream.read(buffer))>0) {
                    outStream.write(buffer, 0, length);
                }
                outStream.flush();
                outStream.close();
                inStream.close();                
           } catch(Exception e) {

     // if (logger.isActivated()) {
      //             logger.debug("exception in restoreAccountMessages");
      //         }
               e.printStackTrace();

           }
        }
     
     
     public static boolean restoreAddressBookDatabase(String account, String path)
        {
            
            try {
                
                 /* if (logger.isActivated()) {
                   logger.debug("restoreAccountMessages : account:"+account);
                }*/
                
                String packageName = "com.orangelabs.rcs";
                String dbFile = Environment.getDataDirectory() + "/data/" + packageName + "/databases/" + RichAddressBookProvider.DatabaseHelper.DATABASE_NAME;
                File backupFileRoot =new File( path);
                String restoreFile = backupFileRoot+"/" + RichAddressBookProvider.DatabaseHelper.DATABASE_NAME +"_"+ account +".db";

            // if(restoreFile.)

                File file = new File(restoreFile);
                if (!file.exists()) {
                //    if (logger.isActivated()) {
                         //logger.debug("error in restoreAccountMessages : account:"+account + "; "+restoreFile+" :file cant be created");
               //      }
                    return false;
                }
                

                   //delete the original file 
                    File dbOriginalFile = new File(dbFile);
                  if (!dbOriginalFile.exists()) {
                              //     dbOriginalFile.delete();
                    dbOriginalFile.createNewFile();
                  } 

                  new FileOutputStream(dbFile,false).close();
                 // dbOriginalFile.createNewFile();
                OutputStream outStream = new FileOutputStream(dbFile, false);
                InputStream inStream = new FileInputStream(file);
                byte[] buffer = new byte[1024];
                int length;
                while ((length = inStream.read(buffer))>0) {
                    outStream.write(buffer, 0, length);
                }
                outStream.flush();
                outStream.close();
                inStream.close();                
           } catch(Exception e) {

     // if (logger.isActivated()) {
      //             logger.debug("exception in restoreAccountMessages");
      //         }
               e.printStackTrace();
            return false;
           }
           return true;
     }
     
     
     
}
