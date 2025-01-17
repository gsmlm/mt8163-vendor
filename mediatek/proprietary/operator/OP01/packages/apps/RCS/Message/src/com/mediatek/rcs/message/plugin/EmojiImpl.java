package com.mediatek.rcs.message.plugin;

import java.util.HashMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.Drawable;
import android.text.Spannable;
import android.text.SpannableString;
import android.text.SpannableStringBuilder;
import android.text.style.ImageSpan;
import android.text.TextUtils;
import android.util.Log;

import com.mediatek.rcs.message.R;

public class EmojiImpl {

    private static final String TAG = "EmojiImpl";
    private static EmojiImpl mInstance = null;
    private final Context mContext;
    private final Pattern mPattern;
    private final HashMap<String, Integer> mEmojisIconMap;
    private final HashMap<String, Integer> mEmojisTextMap;

    private EmojiImpl(Context context) {
        mContext = context;
        mEmojisIconMap = initEmojiIconRes();
        mEmojisTextMap = initEmojiTextRes();
        mPattern = buildPattern();
    }

    private static void init(Context context) {
        mInstance = new EmojiImpl(context);
    }

    public static EmojiImpl getInstance(Context context) {
        if (mInstance == null) {
            init(context);
        }
        return mInstance;
    }

    private HashMap<String, Integer> initEmojiIconRes() {
        int count = EmojiConstants.emojiUnicodes.length;
        HashMap<String, Integer> emojiRes = new HashMap<String, Integer>();
        for (int i=0; i<count; i++) {
            emojiRes.put(EmojiConstants.emojiUnicodes[i], EmojiConstants.emojiImags[i]);
        }
        return emojiRes;
    }

    private HashMap<String, Integer> initEmojiTextRes() {
        int count = EmojiConstants.emojiUnicodes.length;
        HashMap<String, Integer> emojiRes = new HashMap<String, Integer>();
        for (int i=0; i<count; i++) {
        emojiRes.put(EmojiConstants.emojiUnicodes[i], EmojiConstants.emojiText[i]);
        }
        return emojiRes;
    }

    private Pattern buildPattern() {
        StringBuilder patternString = new StringBuilder();

        patternString.append("(");
        for (String i : EmojiConstants.emojiUnicodes) {
            patternString.append(new String(Character.toChars(Integer.parseInt(i, 16))));
            patternString.append('|');
        }
          // Replace the extra '|' with a ')'
        patternString.replace(patternString.length()-1, patternString.length(), ")");
        Log.d(TAG, "buildPattern is " + patternString);
        return Pattern.compile(patternString.toString());
    }

    private void parseEmojiIcon(Context context, SpannableString input, Pattern patten, int size)
                                                                        throws Exception {
        Matcher matcher = patten.matcher(input);
        int matchCount = 0;
        // remove old span first
        ImageSpan[] old = input.getSpans(0, input.length(), ImageSpan.class);
        for (int i = old.length - 1; i >= 0; i--) {
            input.removeSpan(old[i]);
        }

        // most parse 100 emoticons
        while (matcher.find() && matchCount <= 100) {
            String key = string2unicode(matcher.group());
            Log.d(TAG, "parseEmojiIcon Key="+ key);
            int resId = mEmojisIconMap.get(key);
            matchCount++;
            if (resId != 0) {
                ImageSpan imageSpan = null;
                if (false) {
                    Bitmap bitmap = EmojiCacheManager.getEmBitmapFromCache(resId);
                    if (bitmap == null) {
                        bitmap = BitmapFactory.decodeResource(context.getResources(), resId);
                        EmojiCacheManager.addEmBitmapToCache(resId, bitmap);
                    }
                    imageSpan = new ImageSpan(bitmap);
                } else {
                    Drawable drawable = EmojiCacheManager.getEmDrawableFromCache(resId);
                    if (drawable == null) {
                        drawable = context.getResources().getDrawable(resId);
                        int width = (int)(drawable.getIntrinsicWidth()*2/3);
                        int height = (int)(drawable.getIntrinsicHeight()*2/3);
                        drawable.setBounds(0,0,width,height);
                        EmojiCacheManager.addEmDrawableToCache(resId, drawable);
                    }
                    imageSpan = new ImageSpan(drawable);
                }
                Log.d(TAG, "matcher.start=" + matcher.start() + ", matcher.end=" +  matcher.end());
                input.setSpan(imageSpan, matcher.start(), matcher.end(),
                        Spannable.SPAN_INCLUSIVE_EXCLUSIVE);
            }
        }
    }

    private void parseEmojiString(Context context, StringBuilder input, Pattern patten)
                                                                        throws Exception {
        Matcher matcher = patten.matcher(input);
        while (matcher.find()) {
            String key = string2unicode(matcher.group());
            Log.d(TAG, "parseEmojiString Key="+ key);
            int resId = mEmojisTextMap.get(key);
            if (resId != 0) {
                String emojiStr = context.getResources().getString(resId);
                input.replace(matcher.start(), matcher.end(), emojiStr);
                matcher = patten.matcher(input);
            }
        }
    }

    public CharSequence getEmojiExpression(CharSequence chars, boolean showIcon) {
        return getEmojiExpression(chars, showIcon, 0, chars.length(), -1);
    }


    public CharSequence getEmojiExpression(CharSequence chars, boolean showIcon, int textSize) {
        return getEmojiExpression(chars, showIcon, 0, chars.length(), textSize);
    }

    /**
     * Whether has emoticon.
     * @param chars CharSequence
     * @return return true is has, alse return false.
     */
    public boolean hasAnyEmojiExpression(CharSequence chars) {
        Matcher matcher = mPattern.matcher(chars);
        if (matcher.find()) {
            return true;
        } else {
            return false;
        }
    }

    //
    public CharSequence getEmojiExpression(CharSequence chars, boolean showIcon,
                              int start, int length, int size) {
        Log.d(TAG, "getEmojiExpression enter, chars=" + chars + " showIcon=" + showIcon +
                " start=" + start + " length="+ length);
        if (TextUtils.isEmpty(chars)) {
            return "";
        }
        CharSequence cs = " ";
        try {
            if (showIcon) {
                CharSequence subSchars = chars.subSequence(start, start+length);
                SpannableString subString = new SpannableString(subSchars);
                parseEmojiIcon(mContext, subString, mPattern, size);
                SpannableStringBuilder builder = new SpannableStringBuilder(chars);
                // remove old span
                ImageSpan[] old = builder.getSpans(start, start+length, ImageSpan.class);
                for (int i = old.length - 1; i >= 0; i--) {
                    builder.removeSpan(old[i]);
                }
                builder.replace(start, start+length, subString);
                cs = builder.subSequence(0, builder.length());
            } else {
                StringBuilder stringBuilder = new StringBuilder(chars);
                parseEmojiString(mContext, stringBuilder, mPattern);
                cs = stringBuilder.subSequence(0, stringBuilder.length());
            }
        } catch (Exception e) {
            Log.e("getEmojiExpression Exception", e.getMessage());
        }
        Log.d(TAG, "getEmojiExpression end, cs="+cs);
        return cs;
    }

   // convert string to it's unicode
    private String string2unicode(String input) {
        StringBuilder result = new StringBuilder();
        StringBuilder emojicode = new StringBuilder();
        int[] codes =toCodePointArray(input);

        for (int i=0; i<codes.length; i++) {
            emojicode.append(Integer.toHexString(codes[i]));
            result.append(Character.toChars(codes[i]));
        }
        return emojicode.toString().toUpperCase();
    }

    private int[] toCodePointArray(String str) {
        char[] ach = str.toCharArray();
        int len = ach.length;
        int[] acp = new int[Character.codePointCount(ach, 0, len)];

        int j=0;
        for (int i=0, cp; i<len; i+=Character.charCount(cp)) {
            cp = Character.codePointAt(ach, i);
            acp[j++] = cp;
        }
        return acp;
    }

    // no use now
    public String string2utf16(String str) {
        str = (str == null ? "" : str);
        String tmp;
        StringBuffer sb = new StringBuffer(1000);
        char c;
        int i, j;
        sb.setLength(0);
        for (i = 0; i < str.length(); i++) {
            c = str.charAt(i);
            sb.append("\\u");
            j = (c >>> 8);
            tmp = Integer.toHexString(j);
            if (tmp.length() == 1)
                sb.append("0");
            sb.append(tmp);
            j = (c & 0xFF);
            tmp = Integer.toHexString(j);
            if (tmp.length() == 1)
                sb.append("0");
            sb.append(tmp);
        }
        return (new String(sb));
    }

/*    public CharSequence formatEmojiString(CharSequence chars) {
        if (chars == null) {
            return null;
        }
        String str = chars.toString();
        SpannableString string = getExpressionString(str);
        SpannableStringBuilder mBuf = new SpannableStringBuilder();
        mBuf.append(string);
        CharSequence cs = mBuf;
        return cs;
    }*/
}
