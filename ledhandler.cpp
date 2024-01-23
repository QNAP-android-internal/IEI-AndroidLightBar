#include "ledhandler.h"
#include <QByteArray>
#include <QDebug>
#include <unistd.h>

ledHandler::ledHandler() {
  flag = false;
  color = new char[10];
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
    qDebug() << "ledHandler::run"
             << " color: " << color;
  }
  lightBarController->clearLightBarLED();
}

void ledHandler::setFlag(bool new_flag) { flag = new_flag; }
void ledHandler::setColor(const char *new_color) { qstrcpy(color, new_color); }
void ledHandler::setMode(int new_mode) { mode = new_mode; }
