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
 * MediaTek Inc. (C) 2014. All rights reserved.
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
package com.mediatek.camera.v2.stream.multicamera.renderer;

import android.app.Activity;
import android.opengl.EGL14;
import android.opengl.EGLContext;
import android.opengl.GLES20;
import android.opengl.Matrix;
import android.os.ConditionVariable;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.view.Surface;

import java.nio.FloatBuffer;

/**
 * RecorderRenderer.
 *
 */
public class RecorderRenderer extends Renderer implements Runnable {
    private static final String TAG = "RecorderRenderer";
    private static final int BLOCK_SHORT_TIME = 200;
    private static final int BLOCK_LONG_TIME = 3000;
    private static final int TEMP_SIZE_NUM32 = 32;
    private static final int ROTATE_DEGREE_90 = 90;
    private static final int ROTATE_DEGREE_270 = 270;
    private static final float TRANSLATE_LEN = .5f;

    private FloatBuffer mVtxBuf;
    private FloatBuffer mTexCoordBuf;
    // transform matrix
    private float[] mPosMtx = GLUtil.createIdentityMtx();
    private float[] mPMtx = GLUtil.createIdentityMtx();
    private float[] mVMtx = GLUtil.createIdentityMtx();
    private float[] mMMtx = GLUtil.createIdentityMtx();
    private float[] mRotateMtx = GLUtil.createIdentityMtx();

    private EglCore mEglCore;
    private Surface mRecordingSurface;
    private WindowSurface mRecordingEGLSurface;

    private int mProgram = -1;
    private int mPositionHandle = -1;
    private int mTexCoordHandle = -1;
    private int mTexRotateMtxHandle = -1;
    private int mPosMtxHandle = -1;
    private int mSamplerHandle = -1;

    private EncoderHandler mEncoderHandler;
    private EGLContext mSharedEGLContext;
    private final Object mReadyFence = new Object(); // guards ready/running
    private boolean mReady;
    private boolean mRunning;
    private boolean mIsCanRecordFirstFrame = false;
    private boolean mIsStopRecrodingReceived = false;
    private int mSwapVideoBufferCount = 0;
    private final ConditionVariable mStartConditaionVariable = new ConditionVariable();
    private final ConditionVariable mStopConditionVariable = new ConditionVariable();
    private final ConditionVariable mRenderThreadBlockVar = new ConditionVariable();
    private final ConditionVariable mUpdateEGLSurfaceSync = new ConditionVariable();

    /**
     * constructor.
     *
     * @param activity
     *            activity
     */
    public RecorderRenderer(Activity activity) {
        super(activity, null);
        new Thread(this, "RecorderRenderer").start();
    }

    /**
     * init, should be called in GL Thread.
     */
    public void init() {
        Log.i(TAG, "init");
        initGL();
        mSharedEGLContext = EGL14.eglGetCurrentContext();
        mTexCoordBuf = createFloatBuffer(mTexCoordBuf, GLUtil.createTexCoord());
    }

    /**
     * setRecrodingSurface.
     *
     * @param surface
     *            surface
     * @param bottomIsMainCam
     *            is main camera
     */
    public void setRecrodingSurface(Surface surface, boolean bottomIsMainCam) {
        Log.i(TAG, "setRecrodingSurface surface = " + surface);
        if (surface == null) {
            throw new NullPointerException("setRecrodingSurface, but surface is null!!!");
        }
        mRecordingSurface = surface;
        synchronized (mReadyFence) {
            if (mRunning) {
                Log.w(TAG, "Encoder thread already running");
                return;
            }
            mRunning = true;
            while (!mReady) {
                try {
                    Log.i(TAG, "wait for recording thread ready, current mReady = " + mReady);
                    mReadyFence.wait();
                } catch (InterruptedException ie) {
                    Log.d(TAG, "InterruptedException ie:" + ie);
                }
            }
        }
        mUpdateEGLSurfaceSync.close();
        mEncoderHandler.obtainMessage(EncoderHandler.MSG_UPDATE_SHARED_CONTEXT).sendToTarget();
        mUpdateEGLSurfaceSync.block();
        int surfaceWidth = mRecordingEGLSurface.getWidth();
        int surfaceHeight = mRecordingEGLSurface.getHeight();
        updateRendererSize(surfaceWidth, surfaceHeight, bottomIsMainCam);
    }

    /**
     * Tells the video recorder to start recording. (Call from UI thread.)
     * <p>
     * Returns after the recorder thread has started and is ready to accept
     * Messages. The encoder may not yet be fully configured.
     */
    public void startRecording() {
        Log.i(TAG, "startRecording begin mEncoderHandler = " + mEncoderHandler);
        synchronized (mReadyFence) {
            // delay 200ms is for not record start voice to video
            mStartConditaionVariable.block(BLOCK_SHORT_TIME);
            if (mEncoderHandler != null) {
                mEncoderHandler.sendMessage(
                        mEncoderHandler.obtainMessage(EncoderHandler.MSG_START_RECORDING));
            }
        }
        Log.i(TAG, "startRecording end");
    }

    /**
     * when new frame is available, swap buffer to mediacodec (Call from GL
     * thread.).
     *
     * @param textureId
     *            texture id
     * @param timestamp
     *            time stamp
     */
    public void draw(int textureId, long timestamp) {
        synchronized (mReadyFence) {
            if (!mReady || !mIsCanRecordFirstFrame) {
                Log.i(TAG, "mReady = " + mReady + " mIsCanRecordFirstFrame = "
                        + mIsCanRecordFirstFrame);
                return;
            }
            long presentationTimeNs = timestamp;
            if (mEncoderHandler != null) {
                mRenderThreadBlockVar.close();
                mEncoderHandler.obtainMessage(EncoderHandler.MSG_FRAME_AVAILABLE,
                        (int) (presentationTimeNs >> TEMP_SIZE_NUM32), (int) presentationTimeNs,
                        textureId)
                        .sendToTarget();
                mRenderThreadBlockVar.block();
                if (mIsStopRecrodingReceived && (mSwapVideoBufferCount > 1)) {
                    // when stop received, do not receive framenext time
                    mReady = false;
                    mEncoderHandler.sendEmptyMessage(EncoderHandler.MSG_STOP_RECORDING);
                    mEncoderHandler.sendEmptyMessage(EncoderHandler.MSG_QUIT);
                    mStopConditionVariable.open();
                }
            }
        }
    }

    /**
     * Tells the video recorder to stop recording. (Call from UI.) Really stop
     * signal will occur at GL Thread (see details at draw())
     */
    public void stopRecording() {
        Log.i(TAG, "stopRecording mReady = " + mReady + " mIsStopRecrodingReceived = "
                + mIsStopRecrodingReceived);
        synchronized (mReadyFence) {
            // make mReady to true to ensure receive a frame
            mReady = true;
            mIsStopRecrodingReceived = true;
        }
        mStopConditionVariable.block(BLOCK_LONG_TIME);
    }

    /**
     * Encoder thread entry point. Establishes Looper/Handler and waits for
     * messages.
     */
    @Override
    public void run() {
        Log.i(TAG, "run");
        // Establish a Looper for this thread, and define a Handler for it.
        synchronized (mReadyFence) {
            Looper.prepare();
            Log.i(TAG, "new EncoderHandler()");
            mEncoderHandler = new EncoderHandler();
            mReady = true;
            mReadyFence.notify();
        }
        Looper.loop();

        Log.i(TAG, "Encoder thread exiting");
        synchronized (mReadyFence) {
            mReady = mRunning = false;
            mEncoderHandler = null;
        }
    }

    /**
     * releaseSurface.
     */
    public void releaseSurface() {
        Log.i(TAG, "releaseSurface");
    }

    private void updateRendererSize(int width, int height, boolean bottomIsMainCam) {
        Log.i(TAG, "updateRendererSize width = " + width + " height = " + height);
        int minLength = Math.min(width, height);
        int maxLength = Math.max(width, height);
        if (minLength == getRendererWidth() && maxLength == getRendererHeight()) {
            return;
        }
        super.setRendererSize(minLength, maxLength);
        resetMatrix();
        Matrix.orthoM(mPMtx, 0, 0, minLength, 0, maxLength, -1, 1);
        initVertexData(getRendererWidth(), getRendererHeight(), bottomIsMainCam);
    }

    private void initGL() {
        GLUtil.checkGlError("initGL_Start");
        if (mProgram != -1) {
            return;
        }
        final String vertexShader = "attribute vec4 aPosition;\n"
                + "attribute vec4 aTexCoord;\n"
                + "uniform   mat4 uPosMtx;\n"
                + "uniform   mat4 uTexRotateMtx;\n"
                + "varying   vec2 vTexCoord;\n"
                + "void main() {\n"
                + "  gl_Position = uPosMtx * aPosition;\n"
                + "  vTexCoord     = (uTexRotateMtx * aTexCoord).xy;\n" + "}\n";
        final String fragmentShader = "precision mediump float;\n"
                + "uniform sampler2D uSampler;\n"
                + "varying vec2      vTexCoord;\n"
                + "void main() {\n"
                + "  gl_FragColor = texture2D(uSampler, vTexCoord);\n"
                + "}\n";
        mProgram = GLUtil.createProgram(vertexShader, fragmentShader);
        mPositionHandle = GLES20.glGetAttribLocation(mProgram, "aPosition");
        mTexCoordHandle = GLES20.glGetAttribLocation(mProgram, "aTexCoord");
        mTexRotateMtxHandle = GLES20.glGetUniformLocation(mProgram, "uTexRotateMtx");
        // matrix
        mPosMtxHandle = GLES20.glGetUniformLocation(mProgram, "uPosMtx");
        // sampler
        mSamplerHandle = GLES20.glGetUniformLocation(mProgram, "uSampler");

        GLES20.glDisable(GLES20.GL_DEPTH_TEST);
        GLES20.glDisable(GLES20.GL_CULL_FACE);
        GLES20.glDisable(GLES20.GL_BLEND);

        GLUtil.checkGlError("initGL_E");
    }

    private void initVertexData(float width, float height, boolean bottomIsMainCam) {
        mVtxBuf = createFloatBuffer(mVtxBuf, GLUtil.createFullSquareVtx(width, height));
        Matrix.multiplyMM(mPosMtx, 0, mMMtx, 0, mVMtx, 0);
        Matrix.multiplyMM(mPosMtx, 0, mPMtx, 0, mPosMtx, 0);
        // force swap landscape buffer to MediaCodec
        if (width < height) {
            android.opengl.Matrix.translateM(mRotateMtx, 0, mRotateMtx, 0, TRANSLATE_LEN,
                    TRANSLATE_LEN, 0);
            android.opengl.Matrix.rotateM(mRotateMtx, 0, bottomIsMainCam ? -ROTATE_DEGREE_90
                    : -ROTATE_DEGREE_270, 0, 0, 1);
            android.opengl.Matrix.translateM(mRotateMtx, 0, -TRANSLATE_LEN, -TRANSLATE_LEN, 0);
        }
    }

    private void resetMatrix() {
        mPosMtx = GLUtil.createIdentityMtx();
        mPMtx = GLUtil.createIdentityMtx();
        mVMtx = GLUtil.createIdentityMtx();
        mMMtx = GLUtil.createIdentityMtx();
        mRotateMtx = GLUtil.createIdentityMtx();
    }

    private void pauseVideoRecording() {
        Log.i(TAG, "pauseVideoRecording");
        synchronized (mReadyFence) {
            mReady = false;
        }
    }

    private void resumeVideoRecording() {
        Log.i(TAG, "resumeVideoRecording has frame available message = "
                + mEncoderHandler.hasMessages(EncoderHandler.MSG_FRAME_AVAILABLE));
        synchronized (mReadyFence) {
            mReady = true;
        }
    }

    /**
     * EncoderHandler.
     *
     */
    private class EncoderHandler extends Handler {
        private static final int TEMP_SIZE_NUM2 = 2;
        private static final int TEMP_SIZE_NUM3 = 3;
        private static final int TEMP_SIZE_NUM4 = 4;
        private static final int TEMP_SIZE_NUM6 = 6;
        private static final int TEMP_SIZE_NUM32 = 32;
        private static final long TEMP_NUMBER = 0xffffffffL;
        private static final int MSG_START_RECORDING = 0;
        private static final int MSG_STOP_RECORDING = 1;
        private static final int MSG_FRAME_AVAILABLE = 2;
        private static final int MSG_SET_TEXTURE_ID = 3;
        private static final int MSG_UPDATE_SHARED_CONTEXT = 4;
        private static final int MSG_QUIT = 5;

        public EncoderHandler() {

        }

        @Override
        public void handleMessage(Message msg) {
            Log.i(TAG, "handleMessage(" + msg + ")");
            switch (msg.what) {
            case MSG_START_RECORDING:
                mIsCanRecordFirstFrame = true;
                break;
            case MSG_STOP_RECORDING:
                break;
            case MSG_FRAME_AVAILABLE:
                int textureId = (Integer) msg.obj;
                long timestamp = (((long) msg.arg1) << TEMP_SIZE_NUM32) |
                        (((long) msg.arg2) & TEMP_NUMBER);
                doDraw(textureId, timestamp);
                break;
            case MSG_SET_TEXTURE_ID:
                break;
            case MSG_UPDATE_SHARED_CONTEXT:
                doUpdateSharedContext();
                doStartVideoRecording(mRecordingSurface);
                mUpdateEGLSurfaceSync.open();
                break;
            case MSG_QUIT:
                if (mRecordingEGLSurface != null) {
                    mRecordingEGLSurface.makeNothingCurrent();
                    mRecordingEGLSurface.release();
                    mRecordingEGLSurface = null;
                    Log.i(TAG, "RecorderRendere swap buffer total count : "
                            + mSwapVideoBufferCount);
                }
                if (mEglCore != null) {
                    mEglCore.release();
                    mEglCore = null;
                }
                Looper looper = Looper.myLooper();
                if (looper != null) {
                    looper.quit();
                }
                break;
             default:
                break;
            }
        }

        private void doUpdateSharedContext() {
            Log.i(TAG, "doUpdateSharedContext");
            mEglCore = new EglCore(mSharedEGLContext, EglCore.FLAG_RECORDABLE);
        }

        private void doStartVideoRecording(Surface surface) {
            Log.i(TAG, "doStartVideoRecording");
            mRecordingEGLSurface = new WindowSurface(mEglCore, surface);
            mRecordingEGLSurface.makeCurrent();
        }

        private void doDraw(int textureId, long timestamp) {
            if (mRecordingEGLSurface == null) {
                mRenderThreadBlockVar.open();
                return;
            }
            GLUtil.checkGlError("RecordDraw_Start");
            GLES20.glClearColor(0f, 0f, 0f, 1f);
            GLES20.glClear(GLES20.GL_DEPTH_BUFFER_BIT | GLES20.GL_COLOR_BUFFER_BIT);
            // use program
            GLES20.glUseProgram(mProgram);
            // vertex
            mVtxBuf.position(0);
            GLES20.glVertexAttribPointer(mPositionHandle, TEMP_SIZE_NUM3, GLES20.GL_FLOAT, false,
                    TEMP_SIZE_NUM4 * TEMP_SIZE_NUM3,
                    mVtxBuf);
            mTexCoordBuf.position(0);
            GLES20.glVertexAttribPointer(mTexCoordHandle, TEMP_SIZE_NUM2, GLES20.GL_FLOAT, false,
                    TEMP_SIZE_NUM4 * TEMP_SIZE_NUM2,
                    mTexCoordBuf);
            GLES20.glEnableVertexAttribArray(mPositionHandle);
            GLES20.glEnableVertexAttribArray(mTexCoordHandle);
            // matrix
            GLES20.glUniformMatrix4fv(mPosMtxHandle, 1, false, mPosMtx, 0);
            GLES20.glUniformMatrix4fv(mTexRotateMtxHandle, 1, false, mRotateMtx, 0);
            // sampler
            GLES20.glUniform1i(mSamplerHandle, 0);
            // texture
            GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
            GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, textureId);
            // draw
            GLES20.glDrawArrays(GLES20.GL_TRIANGLE_STRIP, 0, TEMP_SIZE_NUM6);
            // swap buffer
            mRecordingEGLSurface.setPresentationTime(timestamp);
            mSwapVideoBufferCount++;
            mRenderThreadBlockVar.open();
            mRecordingEGLSurface.swapBuffers();
            GLUtil.checkGlError("RecordDraw_End");
            debugFrameRate(TAG);
        }
    }
}
