#include "mainwindowalarmsconfig.h"
#include "ui_mainwindowalarmsconfig.h"

MainWindowAlarmsConfig::MainWindowAlarmsConfig(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowAlarmsConfig)
{
    ui->setupUi(this);
}

MainWindowAlarmsConfig::~MainWindowAlarmsConfig()
{
    delete ui;
}
