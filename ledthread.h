#pragma once

#ifndef LEDTHREAD_H
#define LEDTHREAD_H

#endif // LEDTHREAD_H

#include <QObject>
//#include "ledhandler.h"
class ledHandler;

class ledThread : public QObject {
  Q_OBJECT

public:
  ledThread();
  ~ledThread();

  void triggerFunc(ledHandler *handler);
};
