package com.example.lightbartest;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

import com.example.lightbartest.util.Constant;

public class LedModeService extends Service {
    private Boolean mServiceStart = false;
    private int mLedMode;
    private String mLedColor;

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        boolean serviceStart = intent.getExtras().getBoolean(Constant.IS_LED_SERVICE_START);
        if (serviceStart == mServiceStart) {
            return super.onStartCommand(intent, flags, startId);
        }
        mServiceStart = serviceStart;
        if (mServiceStart) {
            mLedMode = intent.getExtras().getInt(Constant.LED_MODE);
            mLedColor = intent.getExtras().getString(Constant.LED_COLOR);
        }
        new Thread(new Runnable() {
            @Override
            public void run() {
                while (mServiceStart) {
                    try {
                        Thread.sleep(1500);
                        if (mLedMode == Constant.LED_MODE_BREATH) {
                            JniMethod.getInstance().setLightBarBreathMode(mLedColor);
                        } else {
                            JniMethod.getInstance().setLightBarWaveMode(mLedColor);
                        }
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                JniMethod.getInstance().clearLightBarLED();
            }
        }).start();

        return super.onStartCommand(intent, flags, startId);
    }

    @Override
    public void onDestroy() {
        mServiceStart = false;
        super.onDestroy();
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }
}
