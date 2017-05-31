#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainwindow_userselectedbed.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    MainWindow_UserSelectedBed *mainwindowUserSelectedBed;
    ~MainWindow();

private slots:

    void on_pushButton_UCIBed1_clicked(bool checked);

    void on_pushButton_UCIBed2_clicked(bool checked);

    void on_pushButton_UCIBed3_clicked(bool checked);

    void on_pushButton_UCIBed4_clicked(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
