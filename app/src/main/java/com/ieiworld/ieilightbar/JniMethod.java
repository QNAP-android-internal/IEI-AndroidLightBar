package com.ieiworld.ieilightbar;

public class JniMethod {
    {
        System.loadLibrary("ieilightbar");
    }

    private static JniMethod instance;

    public static JniMethod getInstance() {
        if (instance == null) {
            instance = new JniMethod();
        }
        return instance;
    }

    public native void setLightBarUserLED(int barNum, int ledNum, int redBrightness, int greenBrightness, int blueBrightness);

    public native void clearLightBarLED();

    public native void setLightBarBreathMode(String color);

    public native void setLightBarWaveMode(String color);

    public native int setLightBarPowerLedSuspendColor(String color);

    public native int setLightBarPowerLedPoweroffState(String flag);

    public native String getLightBarPowerLedStatus(String mode);
}
