#include "ledhandler.h"
#include <QDebug>
#include <unistd.h>

ledHandler::ledHandler() { flag = false; }

ledHandler::~ledHandler() {}

void ledHandler::run() {
  int i = 0;
  while (!flag) {
    usleep(100000);
    qDebug() << i++;
  }
}

void ledHandler::setFlag(bool b) { flag = b; }
