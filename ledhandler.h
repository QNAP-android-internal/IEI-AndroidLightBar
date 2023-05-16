#pragma once

#ifndef LEDHANDLER_H
#define LEDHANDLER_H

#endif // LEDHANDLER_H

#include <QWidget>

class ledHandler : public QWidget {
  Q_OBJECT

public:
  ledHandler();
  ~ledHandler();

  void run();

  void setFlag(bool b);

private:
  bool flag;
};
