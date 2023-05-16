#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QButtonGroup>
#include <QComboBox>
#include <QDebug>
#include <QFontComboBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QSlider>
#include <QTextEdit>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QTabWidget *tabWidget = new QTabWidget(); // ui->tabWidget;
  // tabWidget->setStyleSheet("QTabBar::tab { height: 50px; width: 300px; }");
  // tabWidget->showFullScreen();
  tabWidget->showMaximized();
  //     tabWidget->resize(2048, 2048);
  tabWidget->setWindowState(Qt::WindowMaximized);
  tabWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  tabWidget->setMinimumSize(640, 480);

  QWidget *userControlTab = showUserControlTab();
  QWidget *userFeatureTab = showFeatureTab();
  QWidget *powerSuspendTab = showPowerSuspendTab();
  QWidget *powerOffTab = showPowerOffTab();

  tabWidget->setWindowTitle("LightBar Example");

  tabWidget->addTab(userControlTab,
                    QIcon(":/settings.png"),
                    "UserControl");

  tabWidget->addTab(userFeatureTab,
                    QIcon(":/wave.png"),
                    "UserFeature");

  tabWidget->addTab(powerSuspendTab,
                    QIcon(":/sleep.png"),
                    "PowerSuspend");

  tabWidget->addTab(powerOffTab,
                    QIcon(":/onoff.png"),
                    "PoweOff");
}

MainWindow::~MainWindow() {
  delete ui;
  delete thread;
  delete qThread;
  delete handler;
}

QWidget *MainWindow::showUserControlTab() {

  QComboBox *lightBarComboBox = new QComboBox();
  lightBarComboBox->addItem("1", 1);
  lightBarComboBox->addItem("2", 2);
  lightBarComboBox->setCurrentIndex(0);

  QComboBox *ledNumComboBox = new QComboBox();
  ledNumComboBox->addItem("1", 1);
  ledNumComboBox->addItem("2", 2);
  ledNumComboBox->addItem("3", 3);
  ledNumComboBox->addItem("4", 4);
  ledNumComboBox->setCurrentIndex(0);

  QSlider *redSlider = new QSlider(Qt::Horizontal, this);
  redSlider->setGeometry(10, 10, 100, 20);
  redSlider->setRange(0, 100);

  redSlider->setStyleSheet(
      "QSlider::handle:horizontal {background: qlineargradient(x1:0, y1:0, "
      "x2:1, y2:1, stop:0 #FF0000, stop:1 #FF0000);}");
  connect(redSlider, &QSlider::sliderMoved, [=](int value) {
    qDebug() << "red value: " << QString::number(value);
    qDebug() << "Lightbar Number: " << lightBarComboBox->currentIndex();
    qDebug() << "Led Number" << ledNumComboBox->currentIndex();
  });

  QSlider *greenSlider = new QSlider(Qt::Horizontal, this);
  greenSlider->setGeometry(10, 10, 100, 20);
  greenSlider->setStyleSheet(
      "QSlider::handle:horizontal {background: qlineargradient(x1:0, y1:0, "
      "x2:1, y2:1, stop:0 #008000, stop:1 #008000);}");
/*
  connect(GreenSlider, &QSlider::sliderMoved, [=](int value) {
    qDebug() << "green value: " << QString::number(value);
    qDebug() << "Lightbar Number: " << LightBarComboBox->currentIndex();
    qDebug() << "Led Number" << LedNumComboBox->currentIndex();
  });
*/
  connect(greenSlider, &QSlider::sliderReleased, [=]() {
      qDebug() << "green value: " << QString::number(greenSlider->value());
      qDebug() << "Lightbar Number: " << lightBarComboBox->currentIndex();
      qDebug() << "Led Number" << ledNumComboBox->currentIndex();
  });
  QSlider *blueSlider = new QSlider(Qt::Horizontal, this);
  blueSlider->setGeometry(10, 10, 100, 20);
  blueSlider->setStyleSheet(
      "QSlider::handle:horizontal {background: qlineargradient(x1:0, y1:0, "
      "x2:1, y2:1, stop:0 #0000FF, stop:1 #0000FF);}");
  connect(blueSlider, &QSlider::sliderMoved, [=](int value) {
    qDebug() << "blue value: " << QString::number(value);
    qDebug() << "Lightbar Number: " << lightBarComboBox->currentIndex();
    qDebug() << "Led Number" << ledNumComboBox->currentIndex();
  });

  QPushButton *clearBtn = new QPushButton("Clear");
  connect(clearBtn, &QPushButton::clicked, clearBtn, [=]() {
    lightBarComboBox->setCurrentIndex(0);
    ledNumComboBox->setCurrentIndex(0);
    redSlider->setValue(0);
    greenSlider->setValue(0);
    blueSlider->setValue(0);
  });

  QWidget *tab = new QWidget();
  QFormLayout *formLayout = new QFormLayout();
  formLayout->addRow("Light Bar", lightBarComboBox);
  formLayout->addRow("LED Number", ledNumComboBox);
  formLayout->addRow("Red", redSlider);
  formLayout->addRow("Green", greenSlider);
  formLayout->addRow("Blue", blueSlider);
  formLayout->addRow(clearBtn);
  tab->setLayout(formLayout);

  return tab;
}

QWidget *MainWindow::showFeatureTab() {

  QRadioButton *breathMode = new QRadioButton("Breath Mode", this);
  QRadioButton *waveMode = new QRadioButton("Wave Mode", this);
  breathMode->setChecked(true);

  QComboBox *colorComboBox = new QComboBox();
  colorComboBox->addItem("red", 1);
  colorComboBox->addItem("green", 2);
  colorComboBox->addItem("blue", 3);
  colorComboBox->addItem("yellow", 4);
  colorComboBox->addItem("cyan", 5);
  colorComboBox->addItem("magenta", 6);
  colorComboBox->addItem("white", 7);
  colorComboBox->setCurrentIndex(0);

  handler = new ledHandler();
  thread = new ledThread();
  qThread = new QThread(this);
  thread->moveToThread(qThread);

  connect(this, &MainWindow::trr, thread, &ledThread::triggerFunc);

  QPushButton *runBtn = new QPushButton("Run");
  connect(runBtn, &QPushButton::clicked, runBtn, [=]() {
    if (breathMode->isChecked()) {
      qDebug() << "breathMode btn is checked!";
    } else if (waveMode->isChecked()) {
      qDebug() << "waveMode btn is checked!";
    }
    qDebug() << "color value: " << colorComboBox->currentIndex();
    if (!qThread->isRunning()) {
      handler->setFlag(false);
      qThread->start();

      emit trr(handler);
    }
  });

  QPushButton *stopBtn = new QPushButton("Stop");
  connect(stopBtn, &QPushButton::clicked, stopBtn, [=]() {
    if (qThread->isRunning()) {
      handler->setFlag(true);
      qThread->quit();
      qThread->wait();
    }
  });

  QWidget *tab = new QWidget();
  QFormLayout *formLayout = new QFormLayout();
  formLayout->addRow(breathMode);
  formLayout->addRow(waveMode);
  formLayout->addRow("Color", colorComboBox);
  formLayout->addRow(runBtn);
  formLayout->addRow(stopBtn);
  tab->setLayout(formLayout);

  return tab;
}

QWidget *MainWindow::showPowerSuspendTab() {
  QComboBox *colorComboBox = new QComboBox();
  colorComboBox->addItem("red", 1);
  colorComboBox->addItem("green", 2);
  colorComboBox->addItem("blue", 3);
  colorComboBox->addItem("yellow", 4);
  colorComboBox->addItem("cyan", 5);
  colorComboBox->addItem("magenta", 6);
  colorComboBox->addItem("white", 7);
  colorComboBox->setCurrentIndex(0);

  QPushButton *saveBtn = new QPushButton("Save");
  connect(saveBtn, &QPushButton::clicked, saveBtn, [=]() {});

  QWidget *tab = new QWidget();
  QFormLayout *formLayout = new QFormLayout();
  formLayout->addRow("Color", colorComboBox);
  formLayout->addRow(saveBtn);
  tab->setLayout(formLayout);

  return tab;
}

QWidget *MainWindow::showPowerOffTab() {
  QComboBox *switchComboBox = new QComboBox();
  switchComboBox->addItem("on", 1);
  switchComboBox->addItem("off", 2);
  switchComboBox->setCurrentIndex(0);

  QPushButton *saveBtn = new QPushButton("Save");
  connect(saveBtn, &QPushButton::clicked, saveBtn, [=]() {});

  QWidget *tab = new QWidget();
  QFormLayout *formLayout = new QFormLayout();
  formLayout->addRow("Switch", switchComboBox);
  formLayout->addRow(saveBtn);
  tab->setLayout(formLayout);

  return tab;
}
