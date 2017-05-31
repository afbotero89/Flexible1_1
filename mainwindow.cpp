#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "mainwindow_userselectedbed.h"
#include <QTimer>
#include <QProcess>


int userSelectedBed = 1;
QStringList argo,list;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainwindowUserSelectedBed = new MainWindow_UserSelectedBed;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_UCIBed1_clicked(bool checked)
{
    mainwindowUserSelectedBed->show();
    mainwindowUserSelectedBed->userSelectedBed(1);
    qDebug()<< "muestra cama 1";
    argo.clear();
    list.clear();
    QProcess * exec;
    exec =new QProcess(this);
    exec->start("sh /Applications/XAMPP/xamppfiles/htdocs/sensorFlexible_UDP_Protocol/sensorFlexibleSQLiteDB/mainPlots.sh");
}

void MainWindow::on_pushButton_UCIBed2_clicked(bool checked)
{
    mainwindowUserSelectedBed->show();
    mainwindowUserSelectedBed->userSelectedBed(2);
    qDebug()<< "muestra cama 2";
    //this->close();
}

void MainWindow::on_pushButton_UCIBed3_clicked(bool checked)
{
    mainwindowUserSelectedBed->show();
    mainwindowUserSelectedBed->userSelectedBed(3);
    qDebug()<< "muestra cama 3";
    //this->close();
}

void MainWindow::on_pushButton_UCIBed4_clicked(bool checked)
{
    mainwindowUserSelectedBed->show();
    mainwindowUserSelectedBed->userSelectedBed(4);
    qDebug()<< "muestra cama 4";
    //this->close();
}

