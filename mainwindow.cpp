#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "mainwindow_userselectedbed.h"
#include <QTimer>
#include <QProcess>
#include <QTimer>
#include <QDesktopWidget>

int userSelectedBed = 1;
// Variables clock 1
int contadorSegundosClock1 = 0;
int contadorMinutosClock1 = 0;
int contadorHorasClock1 = 0;
int contadorImagenesClock1 = 0;

QString segundosClock1;
QString minutosClock1;
QString horasClock1;

// variables clock 2
int contadorSegundosClock2 = 0;
int contadorMinutosClock2 = 10;
int contadorHorasClock2 = 0;
int contadorImagenesClock2 = 10;

QString segundosClock2;
QString minutosClock2;
QString horasClock2;

// variables clock 3
int contadorSegundosClock3 = 0;
int contadorMinutosClock3 = 20;
int contadorHorasClock3 = 0;
int contadorImagenesClock3 = 20;

QString segundosClock3;
QString minutosClock3;
QString horasClock3;

// variables clock 4
int contadorSegundosClock4 = 0;
int contadorMinutosClock4 = 30;
int contadorHorasClock4 = 0;
int contadorImagenesClock4 = 30;

QString segundosClock4;
QString minutosClock4;
QString horasClock4;

QString principalPath = "/Users/FING156561/Developer/Flexible1_1/timer/";

QStringList argo,list;
QTimer *timerReloadClockImages;

int screenWith;
int screenHeight;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainwindowUserSelectedBed = new MainWindow_UserSelectedBed;

    QDesktopWidget wid;
    screenWith = wid.screen()->width();
    screenHeight = wid.screen()->height();

    timerReloadClockImages = new QTimer(this);
    connect(timerReloadClockImages,SIGNAL(timeout()),this,SLOT(reloadImagesAndTimers()));
    timerReloadClockImages->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_UCIBed1_clicked(bool checked)
{
    timerReloadClockImages->stop();
    mainwindowUserSelectedBed->setGeometry((screenWith/2)- (1694/2), (screenHeight/2) - (1000/2), 1694, 1000);
    mainwindowUserSelectedBed->show();
    mainwindowUserSelectedBed->userSelectedBed(1);

}

void MainWindow::on_pushButton_UCIBed2_clicked(bool checked)
{
    timerReloadClockImages->stop();
    mainwindowUserSelectedBed->setGeometry((screenWith/2)- (1694/2), (screenHeight/2) - (1000/2), 1694, 1000);
    mainwindowUserSelectedBed->show();
    mainwindowUserSelectedBed->userSelectedBed(2);
    qDebug()<< "muestra cama 2";

    //this->close();
}

void MainWindow::on_pushButton_UCIBed3_clicked(bool checked)
{
    timerReloadClockImages->stop();
    mainwindowUserSelectedBed->setGeometry((screenWith/2)- (1694/2), (screenHeight/2) - (1000/2), 1694, 1000);
    mainwindowUserSelectedBed->show();
    mainwindowUserSelectedBed->userSelectedBed(3);
    qDebug()<< "muestra cama 3";
    //this->close();
}

void MainWindow::on_pushButton_UCIBed4_clicked(bool checked)
{
    timerReloadClockImages->stop();
    mainwindowUserSelectedBed->setGeometry((screenWith/2)- (1694/2), (screenHeight/2) - (1000/2), 1694, 1000);
    mainwindowUserSelectedBed->show();
    mainwindowUserSelectedBed->userSelectedBed(4);
    qDebug()<< "muestra cama 4";
    //this->close();
}
void MainWindow::reloadImagesAndTimers(){

    // Clock 1
    contadorSegundosClock1 = contadorSegundosClock1 + 1;
    if(contadorSegundosClock1 == 60){
        contadorMinutosClock1 = contadorMinutosClock1 + 1;
        contadorSegundosClock1 = 0;

        if(contadorMinutosClock1==60){
            contadorHorasClock1 = contadorHorasClock1 + 1;
            contadorMinutosClock1 = 0;
        }
    }
    if(contadorSegundosClock1<10){
        segundosClock1 = "0" + QString::number(contadorSegundosClock1);
    }else{
        segundosClock1 = QString::number(contadorSegundosClock1);
    }

    if(contadorMinutosClock1<10){
        minutosClock1 = "0" + QString::number(contadorMinutosClock1);
    }else{
        minutosClock1 = QString::number(contadorMinutosClock1);
    }

    if(contadorHorasClock1<10){
        horasClock1 = "0" + QString::number(contadorHorasClock1);
    }else{
        horasClock1 = QString::number(contadorHorasClock1);
    }
    contadorImagenesClock1 = contadorImagenesClock1 + 1;
    if(contadorImagenesClock1 == 100){
        contadorImagenesClock1 = 0;
    }

    QPixmap clock1(principalPath + "TimerV2.00000.png");
    if(contadorImagenesClock1 < 10){
        clock1 = QPixmap(principalPath + "TimerV2.0000" + QString::number(contadorImagenesClock1) + ".png");
    }else{
        clock1 = QPixmap(principalPath + "TimerV2.000" + QString::number(contadorImagenesClock1) + ".png");
    }
    ui->pushButton_TimerImage1->setIcon(clock1);
    ui->pushButton_Timer1->setText(horasClock1 + ":" + minutosClock1 + ":" + segundosClock1);


    // Clock 2
    contadorSegundosClock2 = contadorSegundosClock2 + 1;
    if(contadorSegundosClock2 == 60){
        contadorMinutosClock2 = contadorMinutosClock2 + 1;
        contadorSegundosClock2 = 0;

        if(contadorMinutosClock2==60){
            contadorHorasClock2 = contadorHorasClock2 + 1;
            contadorMinutosClock2 = 0;
        }
    }
    if(contadorSegundosClock2<10){
        segundosClock2 = "0" + QString::number(contadorSegundosClock2);
    }else{
        segundosClock2 = QString::number(contadorSegundosClock2);
    }

    if(contadorMinutosClock2<10){
        minutosClock2 = "0" + QString::number(contadorMinutosClock2);
    }else{
        minutosClock2 = QString::number(contadorMinutosClock2);
    }

    if(contadorHorasClock2<10){
        horasClock2 = "0" + QString::number(contadorHorasClock2);
    }else{
        horasClock2 = QString::number(contadorHorasClock2);
    }
    contadorImagenesClock2 = contadorImagenesClock2 + 1;
    if(contadorImagenesClock2 == 99){
        contadorImagenesClock2 = 0;
    }
    QPixmap clock2(principalPath + "TimerV2.00000.png");
    if(contadorImagenesClock2 < 10){
        clock2 = QPixmap(principalPath + "TimerV2.0000" + QString::number(contadorImagenesClock2) + ".png");
    }else{
        clock2 = QPixmap(principalPath + "TimerV2.000" + QString::number(contadorImagenesClock2) + ".png");
    }
    ui->pushButton_TimerImage2->setIcon(clock2);
    ui->pushButton_Timer2->setText(horasClock2 + ":" + minutosClock2 + ":" + segundosClock2);

    // Clock 3
    contadorSegundosClock3 = contadorSegundosClock3 + 1;
    if(contadorSegundosClock3 == 60){
        contadorMinutosClock3 = contadorMinutosClock3 + 1;
        contadorSegundosClock3 = 0;

        if(contadorMinutosClock3==60){
            contadorHorasClock3 = contadorHorasClock3 + 1;
            contadorMinutosClock3 = 0;
        }
    }
    if(contadorSegundosClock3<10){
        segundosClock3 = "0" + QString::number(contadorSegundosClock3);
    }else{
        segundosClock3 = QString::number(contadorSegundosClock3);
    }

    if(contadorMinutosClock3<10){
        minutosClock3 = "0" + QString::number(contadorMinutosClock3);
    }else{
        minutosClock3 = QString::number(contadorMinutosClock3);
    }

    if(contadorHorasClock3<10){
        horasClock3 = "0" + QString::number(contadorHorasClock3);
    }else{
        horasClock3 = QString::number(contadorHorasClock3);
    }
    contadorImagenesClock3 = contadorImagenesClock3 + 1;
    if(contadorImagenesClock3 == 99){
        contadorImagenesClock3 = 0;
    }
    QPixmap clock3(principalPath + "TimerV2.00000.png");
    if(contadorImagenesClock3 < 10){
        clock3 = QPixmap(principalPath + "TimerV2.0000" + QString::number(contadorImagenesClock3) + ".png");
    }else{
        clock3 = QPixmap(principalPath + "TimerV2.000" + QString::number(contadorImagenesClock3) + ".png");
    }
    ui->pushButton_TimerImage3->setIcon(clock3);
    ui->pushButton_Timer3->setText(horasClock3 + ":" + minutosClock3 + ":" + segundosClock3);

    // Clock 4
    contadorSegundosClock4 = contadorSegundosClock4 + 1;
    if(contadorSegundosClock4 == 60){
        contadorMinutosClock4 = contadorMinutosClock4 + 1;
        contadorSegundosClock4 = 0;

        if(contadorMinutosClock4==60){
            contadorHorasClock4 = contadorHorasClock4 + 1;
            contadorMinutosClock4 = 0;
        }
    }
    if(contadorSegundosClock4<10){
        segundosClock4 = "0" + QString::number(contadorSegundosClock4);
    }else{
        segundosClock4 = QString::number(contadorSegundosClock4);
    }

    if(contadorMinutosClock4<10){
        minutosClock4 = "0" + QString::number(contadorMinutosClock4);
    }else{
        minutosClock4 = QString::number(contadorMinutosClock4);
    }

    if(contadorHorasClock4<10){
        horasClock4 = "0" + QString::number(contadorHorasClock4);
    }else{
        horasClock4 = QString::number(contadorHorasClock4);
    }
    contadorImagenesClock4 = contadorImagenesClock4 + 1;
    if(contadorImagenesClock4 > 99){
        contadorImagenesClock4 = 0;
    }
    QPixmap clock4(principalPath + "TimerV2.00000.png");
    if(contadorImagenesClock4 < 10){
        clock4 = QPixmap(principalPath + "TimerV2.0000" + QString::number(contadorImagenesClock4) + ".png");
    }else{
        clock4 = QPixmap(principalPath + "TimerV2.000" + QString::number(contadorImagenesClock4) + ".png");
    }
    ui->pushButton_TimerImage4->setIcon(clock4);
    ui->pushButton_Timer4->setText(horasClock4 + ":" + minutosClock4 + ":" + segundosClock4);
}
