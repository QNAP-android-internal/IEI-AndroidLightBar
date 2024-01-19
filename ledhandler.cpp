#include "ledhandler.h"
#include <QDebug>
#include <unistd.h>

ledHandler::ledHandler() {
  flag = false;
  lightBarController = new LightBar();
}

ledHandler::~ledHandler() {}

void ledHandler::run() {
  while (!flag) {
    usleep(150000);
    if (mode == 0)
      lightBarController->setLightBarBreathMode(color);
    else
      lightBarController->setLightBarWaveMode(color);
  }
  lightBarController->clearLightBarLED();
}

void ledHandler::setFlag(bool new_flag) { flag = new_flag; }
void ledHandler::setColor(const char *new_color) { color = new_color; }
void ledHandler::setMode(int new_mode) { mode = new_mode; }
