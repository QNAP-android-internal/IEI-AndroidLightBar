#ifndef LIGHTBAR_H
#define LIGHTBAR_H

#ifdef ANDROID_IMX8M
#include <jni.h>
#endif

#ifdef ANDROID_IMX8M
#include <android/log.h>
#endif

class LightBar {

public:
  LightBar();
#ifdef ANDROID_IMX8M
  extern "C" JNIEXPORT void JNICALL
  Java_com_ieiworld_testprogram_1prebuilt_1lightbar_NativeMethods_setLightBarUserLED(
      JNIEnv *env, jobject thiz, jint bar_num, jint led_num,
      jint red_brightness, jint green_brightness, jint blue_brightness);

  extern "C" JNIEXPORT void JNICALL
  Java_com_ieiworld_testprogram_1prebuilt_1lightbar_NativeMethods_clearLightBarLED(
      JNIEnv *env, jobject thiz);

  extern "C" JNIEXPORT void JNICALL
  Java_com_ieiworld_testprogram_1prebuilt_1lightbar_NativeMethods_setLightBarBreathMode(
      JNIEnv *env, jobject thiz, jstring specific_color);

  extern "C" JNIEXPORT void JNICALL
  Java_com_ieiworld_testprogram_1prebuilt_1lightbar_NativeMethods_setLightBarWaveMode(
      JNIEnv *env, jobject thiz, jstring specific_color);

  extern "C" JNIEXPORT jint JNICALL
  Java_com_ieiworld_testprogram_1prebuilt_1lightbar_NativeMethods_setLightBarPowerLedSuspendColor(
      JNIEnv *env, jobject thiz, jstring specific_color);

  extern "C" JNIEXPORT jint JNICALL
  Java_com_ieiworld_testprogram_1prebuilt_1lightbar_NativeMethods_setLightBarPowerLedPoweroffState(
      JNIEnv *env, jobject thiz, jstring on_flag);

  extern "C" JNIEXPORT jstring JNICALL
  Java_com_ieiworld_testprogram_1prebuilt_1lightbar_NativeMethods_getLightBarPowerLedStatus(
      JNIEnv *env, jobject thiz, jstring mode);
#endif
  void setLightBarUserLED(int bar_num, int led_num, int red_brightness,
                          int green_brightness, int blue_brightness);
  void clearLightBarLED();
  void setLightBarBreathMode(const char *color);
  void setLightBarWaveMode(const char *color);
  int setLightBarPowerLedSuspendColor(const char *color);
  int setLightBarPowerLedPoweroffState(const char *on_flag);
  const char *getLightBarPowerLedStatus(const char *mode, char *status);
  ~LightBar();
};

#endif
