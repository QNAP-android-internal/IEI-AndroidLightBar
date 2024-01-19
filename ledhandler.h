#pragma once

#ifndef LEDHANDLER_H
#define LEDHANDLER_H

#endif // LEDHANDLER_H

#include "LightBar.h"
#include <QWidget>

class ledHandler : public QWidget {
  Q_OBJECT

public:
  ledHandler();
  ~ledHandler();

  void run();

  void setFlag(bool flag);
  void setColor(const char *color);
  void setMode(int mode);

private:
  LightBar *lightBarController;
  bool flag;
  const char *color;
  int mode;
};
