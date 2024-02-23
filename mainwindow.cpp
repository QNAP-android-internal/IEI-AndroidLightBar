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
#include <QMessageBox>
#include <QPushButton>
#include <QRadioButton>
#include <QSlider>
#include <QTextEdit>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  QTabWidget *tabWidget = new QTabWidget();
  tabWidget->showMaximized();
  tabWidget->setWindowState(Qt::WindowMaximized);
  tabWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  tabWidget->setMinimumSize(640, 480);

  QWidget *userControlTab = showUserControlTab();
  QWidget *userFeatureTab = showFeatureTab();
  QWidget *powerSuspendTab = showPowerSuspendTab();
  QWidget *powerOffTab = showPowerOffTab();

  tabWidget->setWindowTitle("LightBar Example");

  tabWidget->addTab(userControlTab, QIcon(":/settings.png"), "UserControl");

  tabWidget->addTab(userFeatureTab, QIcon(":/wave.png"), "UserFeature");

  tabWidget->addTab(powerSuspendTab, QIcon(":/sleep.png"), "PowerSuspend");

  tabWidget->addTab(powerOffTab, QIcon(":/onoff.png"), "PoweOff");

  lightBarController = new LightBar();
}

MainWindow::~MainWindow() {
  delete ui;
  delete thread;
  delete qThread;
  delete handler;
  delete lightBarController;
}

QWidget *MainWindow::showUserControlTab() {

  QComboBox *lightBarComboBox = new QComboBox();
  lightBarComboBox->addItem("1", 1);
  lightBarComboBox->addItem("2", 2);
  lightBarComboBox->setCurrentIndex(0);

  QFont *lightBarComboBoxFont = new QFont();
  lightBarComboBoxFont->setPointSize(lightBarComboBoxFont->pointSize() + 10);
  lightBarComboBox->setFont(*lightBarComboBoxFont);

  QComboBox *ledNumComboBox = new QComboBox();
  ledNumComboBox->addItem("1", 1);
  ledNumComboBox->addItem("2", 2);
  ledNumComboBox->addItem("3", 3);
  ledNumComboBox->addItem("4", 4);
  ledNumComboBox->setCurrentIndex(0);

  QFont *ledNumComboBoxFont = new QFont();
  ledNumComboBoxFont->setPointSize(ledNumComboBoxFont->pointSize() + 10);
  ledNumComboBox->setFont(*ledNumComboBoxFont);

  QSlider *redSlider = new QSlider(Qt::Horizontal, this);
  redSlider->setGeometry(10, 10, 100, 20);
  redSlider->setRange(0, 100);
  redSlider->setStyleSheet("           QSlider {"
                           "                min-height: 68px;"
                           "                 max-height: 68px;"
                           "                border-radius: 10px;"
                           "            }"
                           "            QSlider::groove:horizontal {"
                           "                height: 40px;"
                           "                background: #000;"
                           "                margin: 0 20px;"
                           "            }"
                           "            QSlider::handle:horizontal{"
                           "                background: #f00;"
                           "                width: 40px;"
                           "                height: 40px;"
                           "                margin:-20px -20px;"
                           "                border-radius:8px;"
                           "            }"
                           "            QSlider::sub-page:horizontal{"
                           "                background:#f90;"
                           "            }");

  QSlider *greenSlider = new QSlider(Qt::Horizontal, this);
  greenSlider->setGeometry(10, 10, 100, 20);
  greenSlider->setRange(0, 100);
  greenSlider->setStyleSheet("           QSlider {"
                             "                min-height: 68px;"
                             "                max-height: 68px;"
                             "                border-radius: 10px;"
                             "            }"
                             "            QSlider::groove:horizontal {"
                             "                height: 40px;"
                             "                background: #000;"
                             "                margin: 0 20px;"
                             "            }"
                             "            QSlider::handle:horizontal{"
                             "                background: #008000;"
                             "                width: 40px;"
                             "                height: 40px;"
                             "                margin:-20px -20px;"
                             "                border-radius:8px;"
                             "            }"
                             "            QSlider::sub-page:horizontal{"
                             "                background:#f90;"
                             "            }");

  QSlider *blueSlider = new QSlider(Qt::Horizontal, this);
  blueSlider->setGeometry(10, 10, 100, 20);
  blueSlider->setRange(0, 100);
  blueSlider->setStyleSheet("           QSlider {"
                            "                min-height: 68px;"
                            "                max-height: 68px;"
                            "                border-radius: 10px;"
                            "            }"
                            "            QSlider::groove:horizontal {"
                            "                height: 40px;"
                            "                background: #000;"
                            "                margin: 0 20px;"
                            "            }"
                            "            QSlider::handle:horizontal{"
                            "                background: #0000FF;"
                            "                width: 40px;"
                            "                height: 40px;"
                            "                margin:-20px -20px;"
                            "                border-radius:8px;"
                            "            }"
                            "            QSlider::sub-page:horizontal{"
                            "                background:#f90;"
                            "            }");

  connect(redSlider, &QSlider::valueChanged, [=](int value) {
    qDebug() << "red value: " << QString::number(redSlider->value());
    qDebug() << "green value: " << QString::number(greenSlider->value());
    qDebug() << "blue value: " << QString::number(blueSlider->value());
    qDebug() << "Lightbar Number: " << lightBarComboBox->currentIndex();
    qDebug() << "Led Number" << ledNumComboBox->currentIndex();
    lightBarController->setLightBarUserLED(
        lightBarComboBox->currentIndex() + 1,
        ledNumComboBox->currentIndex() + 1, redSlider->value(),
        greenSlider->value(), blueSlider->value());
  });

  connect(greenSlider, &QSlider::valueChanged, [=](int value) {
    qDebug() << "red value: " << QString::number(redSlider->value());
    qDebug() << "green value: " << QString::number(greenSlider->value());
    qDebug() << "blue value: " << QString::number(blueSlider->value());
    qDebug() << "Lightbar Number: " << lightBarComboBox->currentIndex();
    qDebug() << "Led Number" << ledNumComboBox->currentIndex();
    lightBarController->setLightBarUserLED(
        lightBarComboBox->currentIndex() + 1,
        ledNumComboBox->currentIndex() + 1, redSlider->value(),
        greenSlider->value(), blueSlider->value());
  });

  connect(blueSlider, &QSlider::valueChanged, [=](int value) {
    qDebug() << "red value: " << QString::number(redSlider->value());
    qDebug() << "green value: " << QString::number(greenSlider->value());
    qDebug() << "blue value: " << QString::number(blueSlider->value());
    qDebug() << "Lightbar Number: " << lightBarComboBox->currentIndex();
    qDebug() << "Led Number" << ledNumComboBox->currentIndex();
    lightBarController->setLightBarUserLED(
        lightBarComboBox->currentIndex() + 1,
        ledNumComboBox->currentIndex() + 1, redSlider->value(),
        greenSlider->value(), blueSlider->value());
  });

  QPushButton *clearBtn = new QPushButton("Clear");
  QFont *clearBtnFont = new QFont();
  clearBtnFont->setPointSize(clearBtnFont->pointSize() + 10);
  clearBtn->setFont(*clearBtnFont);

  connect(clearBtn, &QPushButton::clicked, clearBtn, [=]() {
    lightBarComboBox->setCurrentIndex(0);
    ledNumComboBox->setCurrentIndex(0);
    redSlider->setValue(0);
    greenSlider->setValue(0);
    blueSlider->setValue(0);
    lightBarController->clearLightBarLED();
  });

  QWidget *tab = new QWidget();
  QFormLayout *formLayout = new QFormLayout();

  QLabel *lightBarlabel = new QLabel("Light Bar");
  lightBarlabel->setStyleSheet(".QLabel { font-size: 20pt; }");
  formLayout->addRow(lightBarlabel, lightBarComboBox);

  QLabel *ledLabel = new QLabel("LED Number");
  ledLabel->setStyleSheet(".QLabel { font-size: 20pt; }");
  formLayout->addRow(ledLabel, ledNumComboBox);

  QLabel *redLabel = new QLabel("Red");
  redLabel->setStyleSheet(".QLabel { font-size: 20pt; color : red; }");
  formLayout->addRow(redLabel, redSlider);

  QLabel *greenLabel = new QLabel("Green");
  greenLabel->setStyleSheet(".QLabel { font-size: 20pt; color : green; }");
  formLayout->addRow(greenLabel, greenSlider);

  QLabel *blueLabel = new QLabel("Blue");
  blueLabel->setStyleSheet(".QLabel { font-size: 20pt; color : blue; }");
  formLayout->addRow(blueLabel, blueSlider);

  formLayout->addRow(clearBtn);
  formLayout->setSpacing(50);
  tab->setLayout(formLayout);

  return tab;
}

QWidget *MainWindow::showFeatureTab() {
  QRadioButton *breathMode = new QRadioButton("Breath Mode", this);
  breathMode->setStyleSheet(".QRadioButton { font-size: 20pt; }");

  QRadioButton *waveMode = new QRadioButton("Wave Mode", this);
  waveMode->setStyleSheet(".QRadioButton { font-size: 20pt; }");
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

  QFont *colorFont = new QFont();
  colorFont->setPointSize(colorFont->pointSize() + 10);
  colorComboBox->setFont(*colorFont);

  handler = new ledHandler();
  thread = new ledThread();
  qThread = new QThread(this);
  thread->moveToThread(qThread);

  connect(this, &MainWindow::trr, thread, &ledThread::triggerFunc);

  QPushButton *runBtn = new QPushButton("Run");
  QFont *runBtnFont = new QFont();
  runBtnFont->setPointSize(runBtnFont->pointSize() + 10);
  runBtn->setFont(*runBtnFont);

  connect(runBtn, &QPushButton::clicked, runBtn, [=]() {
    if (breathMode->isChecked()) {
      handler->setMode(0);
    } else if (waveMode->isChecked()) {
      handler->setMode(1);
    }
    if (!qThread->isRunning()) {
      handler->setFlag(false);
      QByteArray colorArray = colorComboBox->currentText().toLocal8Bit();
      const char *colorString = colorArray.data();
      handler->setColor(colorString);
      qThread->start();

      emit trr(handler);
    }
  });

  QPushButton *stopBtn = new QPushButton("Stop");
  QFont *stopBtnFont = new QFont();
  stopBtnFont->setPointSize(stopBtnFont->pointSize() + 10);
  stopBtn->setFont(*stopBtnFont);

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

  QLabel *colorLabel = new QLabel("Color");
  colorLabel->setStyleSheet(".QLabel { font-size: 20pt; }");
  formLayout->addRow(colorLabel, colorComboBox);

  formLayout->addRow(runBtn);
  formLayout->addRow(stopBtn);
  formLayout->setSpacing(50);
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

  QFont *colorComboBoxFont = new QFont();
  colorComboBoxFont->setPointSize(colorComboBoxFont->pointSize() + 10);
  colorComboBox->setFont(*colorComboBoxFont);

  QPushButton *saveBtn = new QPushButton("Save");
  QFont *saveBtnFont = new QFont();
  saveBtnFont->setPointSize(saveBtnFont->pointSize() + 10);
  saveBtn->setFont(*saveBtnFont);

  connect(saveBtn, &QPushButton::clicked, saveBtn, [=]() {
    QByteArray colorArray = colorComboBox->currentText().toLocal8Bit();
    const char *colorString = colorArray.data();
    lightBarController->setLightBarPowerLedSuspendColor(colorString);
    const char *suspendString = "suspend";
    char *saveResult = (char *)malloc(sizeof(char) * 8);
    lightBarController->getLightBarPowerLedStatus(suspendString, saveResult);
    QMessageBox *msgBox = new QMessageBox();
    if (!qstrcmp(saveResult, colorString)) {
      msgBox->setText(
          "Save Success. Please reboot and configuration will take effect");
    } else {
      msgBox->setText("Save Fail");
    }
    qDebug() << "saveResult " << saveResult << "  colorString " << colorString;
    msgBox->show();
  });

  QWidget *tab = new QWidget();
  QFormLayout *formLayout = new QFormLayout();

  QLabel *colorLabel = new QLabel("Color");
  colorLabel->setStyleSheet(".QLabel { font-size: 20pt; }");
  formLayout->addRow(colorLabel, colorComboBox);
  formLayout->addRow(saveBtn);
  formLayout->setSpacing(50);
  tab->setLayout(formLayout);

  return tab;
}

QWidget *MainWindow::showPowerOffTab() {
  QComboBox *switchComboBox = new QComboBox();
  switchComboBox->addItem("on", 1);
  switchComboBox->addItem("off", 2);
  switchComboBox->setCurrentIndex(0);

  QFont *switchComboBoxFont = new QFont();
  switchComboBoxFont->setPointSize(switchComboBoxFont->pointSize() + 10);
  switchComboBox->setFont(*switchComboBoxFont);

  QPushButton *saveBtn = new QPushButton("Save");
  QFont *saveBtnFont = new QFont();
  saveBtnFont->setPointSize(saveBtnFont->pointSize() + 10);
  saveBtn->setFont(*saveBtnFont);

  connect(saveBtn, &QPushButton::clicked, saveBtn, [=]() {
    QByteArray switchArray = switchComboBox->currentText().toLocal8Bit();
    const char *switchString = switchArray.data();
    lightBarController->setLightBarPowerLedPoweroffState(switchString);
    const char *powerOffString = "poweroff";
    char *saveResult = (char *)malloc(sizeof(char) * 8);
    lightBarController->getLightBarPowerLedStatus(powerOffString, saveResult);
    QMessageBox *msgBox = new QMessageBox();
    if (!qstrcmp(saveResult, switchString)) {
      msgBox->setText(
          "Save Success. Please reboot and configuration will take effect");
    } else {
      msgBox->setText("Save Fail");
    }
    qDebug() << "saveResult " << saveResult << "  powerOffString "
             << switchString;
    msgBox->show();
  });

  QWidget *tab = new QWidget();
  QFormLayout *formLayout = new QFormLayout();
  QLabel *switchLabel = new QLabel("Switch");
  switchLabel->setStyleSheet(".QLabel { font-size: 20pt; }");
  formLayout->addRow(switchLabel, switchComboBox);
  formLayout->addRow(saveBtn);
  formLayout->setSpacing(50);
  tab->setLayout(formLayout);

  return tab;
}
