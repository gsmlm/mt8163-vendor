package com.mediatek.crossmountsettings.util;

import android.text.InputFilter;
import android.text.Spanned;

/**
 * This filter will constrain edits so that the text length is not
 * greater than the specified number of bytes using UTF-8 encoding.
 * <p>The JNI method used by {@link android.server.BluetoothService}
 * to convert UTF-16 to UTF-8 doesn't support surrogate pairs,
 * therefore code points outside of the basic multilingual plane
 * (0000-FFFF) will be encoded as a pair of 3-byte UTF-8 characters,
 * rather than a single 4-byte UTF-8 encoding. Dalvik implements this
 * conversion in {@code convertUtf16ToUtf8()} in
 * {@code dalvik/vm/UtfString.c}.
 * <p>This JNI method is unlikely to change in the future due to
 * backwards compatibility requirements. It's also unclear whether
 * the installed base of Bluetooth devices would correctly handle the
 * encoding of surrogate pairs in UTF-8 as 4 bytes rather than 6.
 * However, this filter will still work in scenarios where surrogate
 * pairs are encoded as 4 bytes, with the caveat that the maximum
 * length will be constrained more conservatively than necessary.
 */
public class Utf8ByteLengthFilter implements InputFilter {
    public final int mMaxBytes;

   public  Utf8ByteLengthFilter(int maxBytes) {
        mMaxBytes = maxBytes;
    }

    public CharSequence filter(CharSequence source, int start, int end,
                               Spanned dest, int dstart, int dend) {
        int srcByteCount = 0;
        // count UTF-8 bytes in source substring
        for (int i = start; i < end; i++) {
            char c = source.charAt(i);
            srcByteCount += (c < (char) 0x0080) ? 1 : (c < (char) 0x0800 ? 2 : 3);
        }
        int destLen = dest.length();
        int destByteCount = 0;
        // count UTF-8 bytes in destination excluding replaced section
        for (int i = 0; i < destLen; i++) {
            if (i < dstart || i >= dend) {
                char c = dest.charAt(i);
                destByteCount += (c < (char) 0x0080) ? 1 : (c < (char) 0x0800 ? 2 : 3);
            }
        }
        int keepBytes = mMaxBytes - destByteCount;
        if (keepBytes <= 0) {
            return "";
        } else if (keepBytes >= srcByteCount) {
            return null; // use original dest string
        } else {
            // find end position of largest sequence that fits in keepBytes
            for (int i = start; i < end; i++) {
                char c = source.charAt(i);
                keepBytes -= (c < (char) 0x0080) ? 1 : (c < (char) 0x0800 ? 2 : 3);
                if (keepBytes < 0) {
                    return source.subSequence(start, i);
                }
            }
            // If the entire substring fits, we should have returned null
            // above, so this line should not be reached. If for some
            // reason it is, return null to use the original dest string.
            return null;
        }
    }
}
