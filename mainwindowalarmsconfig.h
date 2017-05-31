#ifndef MAINWINDOWALARMSCONFIG_H
#define MAINWINDOWALARMSCONFIG_H

#include <QMainWindow>


namespace Ui {
class MainWindowAlarmsConfig;
}

class MainWindowAlarmsConfig : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowAlarmsConfig(QWidget *parent = 0);

    ~MainWindowAlarmsConfig();

private:
    Ui::MainWindowAlarmsConfig *ui;
};

#endif // MAINWINDOWALARMSCONFIG_H
