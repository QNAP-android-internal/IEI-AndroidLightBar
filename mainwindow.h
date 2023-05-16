#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ledhandler.h"
#include "ledthread.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  QWidget *showUserControlTab();
  QWidget *showFeatureTab();
  QWidget *showPowerSuspendTab();
  QWidget *showPowerOffTab();
  ~MainWindow();

signals:
  void trr(ledHandler *handler);

private:
  Ui::MainWindow *ui;
  ledThread *thread;
  QThread *qThread;
  ledHandler *handler;
};

#endif // MAINWINDOW_H
