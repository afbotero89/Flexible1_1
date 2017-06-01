#include "mainwindow_userselectedbed.h"
#include "ui_mainwindow_userselectedbed.h"
#include <QDebug>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QSqlQuery>

QTimer *timer;
QTimer *timerExpositionTimes;

int stateMachine = 0;   //0:Distribucion presion sin tiempos, 1:Distribucion presion con tiempos, 2:Estadisticas 1, 3: Estadisticas 2
int userSelectedBed_int = 1;

bool open = false;
QSqlDatabase db;

MainWindow_UserSelectedBed::MainWindow_UserSelectedBed(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_UserSelectedBed)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timerExpositionTimes = new QTimer(this);

    QString path = "/Applications/XAMPP/xamppfiles/htdocs/sensorFlexible_UDP_Protocol/sensorFlexibleSQLiteDB/estadisticas.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    open = db.open();
    //ui->label_zona1_1->setStyleSheet("background: yellow");
    initActionsConnections();
}

MainWindow_UserSelectedBed::~MainWindow_UserSelectedBed()
{
    delete ui;

}

void MainWindow_UserSelectedBed::on_pushButton_4_clicked(bool checked)
{
    timer->stop();
    timerExpositionTimes->stop();
    this->close();
}

void MainWindow_UserSelectedBed::initActionsConnections(){
    connect(timer,SIGNAL(timeout()),this,SLOT(reloadStadisticsImage()));
    connect(timerExpositionTimes,SIGNAL(timeout()),this,SLOT(reloadExpositionTimes()));
}

void MainWindow_UserSelectedBed::reloadStadisticsImage(){

    QPixmap pixmapSensor1("/Users/FING156561/Developer/Flexible1_1/GraficoPresion.png");
    QPixmap pixmapSensor2("/Users/FING156561/Developer/Flexible1_1/GraficoPresion.png");
    QPixmap historicGraphs("/Users/FING156561/Developer/Flexible1_1/GraficoPresion.png");

     if(stateMachine == 0 || stateMachine == 1 || stateMachine == 2){
         pixmapSensor1 = QPixmap("/Applications/XAMPP/xamppfiles/htdocs/sensorFlexible_UDP_Protocol/appSensorFlexibleWebLocalMatplotlib/img/sensor1SinTiempos.jpeg");
         pixmapSensor2 = QPixmap("/Applications/XAMPP/xamppfiles/htdocs/sensorFlexible_UDP_Protocol/appSensorFlexibleWebLocalMatplotlib/img/sensor2SinTiempos.jpeg");
     }

     if(stateMachine == 0){

        ui->label_stadisticWindow->setFixedWidth(651);
        ui->label_stadisticWindow2->setFixedWidth(651);

        historicGraphs = QPixmap("/Applications/XAMPP/xamppfiles/htdocs/flexible1.1/img/historial_main.png");

        if (historicGraphs.width() == 0 || historicGraphs.height() == 0){

        }else{
            ui->label_historicRegisters->setPixmap(historicGraphs);
        }

    }else if (stateMachine == 1){

        ui->label_stadisticWindow->setFixedWidth(651);
        ui->label_stadisticWindow2->setFixedWidth(651);

        historicGraphs = QPixmap("/Applications/XAMPP/xamppfiles/htdocs/flexible1.1/img/historial_main.png");

        if (historicGraphs.width() == 0 || historicGraphs.height() == 0){

        }else{
            ui->label_historicRegisters->setPixmap(historicGraphs);
        }

    }else if(stateMachine==2){

         ui->label_stadisticWindow->setFixedWidth(651);
         ui->label_stadisticWindow2->setFixedWidth(651);

         historicGraphs = QPixmap("/Applications/XAMPP/xamppfiles/htdocs/sensorFlexible_UDP_Protocol/appSensorFlexibleWebLocalMatplotlib/img/GraficoPresion.png");

         if (historicGraphs.width() == 0 || historicGraphs.height() == 0){

         }else{
             ui->label_historicRegisters->setPixmap(historicGraphs);
         }

     }else if(stateMachine == 3){

        ui->label_stadisticWindow->setFixedWidth(1301);
        ui->label_stadisticWindow2->setFixedWidth(1);
        pixmapSensor1 = QPixmap("/Applications/XAMPP/xamppfiles/htdocs/sensorFlexible_UDP_Protocol/sensorFlexibleSQLiteDB/GraficoPresion1.png");
        if(pixmapSensor1.width() == 0 || pixmapSensor1.width() == 0){
            ui->label_historicRegisters->setPixmap(pixmapSensor1);
        }

        historicGraphs = QPixmap("/Applications/XAMPP/xamppfiles/htdocs/flexible1.1/img/historial_main.png");

        if (historicGraphs.width() == 0 || historicGraphs.height() == 0){

        }else{
            ui->label_historicRegisters->setPixmap(historicGraphs);
        }
    }

    if(pixmapSensor1.size().width()==0 & pixmapSensor1.size().height()==0){

    }else{
        ui->label_stadisticWindow->setPixmap(pixmapSensor1);
    }

    if(pixmapSensor2.size().width()==0 & pixmapSensor2.size().height()==0){

    }else{
        ui->label_stadisticWindow2->setPixmap(pixmapSensor2);
    }

}

void MainWindow_UserSelectedBed::on_pushButtonPressureButton_clicked(bool checked)
{
    stateMachine = 0;

    qDebug()<<"distribucion";
    timer->start(100);

    timerExpositionTimes->stop();
    hidenLabelesExpositionTimes();
    hidenHorizontalVerticalLabels();
}


void MainWindow_UserSelectedBed::on_pushButtonExpositionTimes_clicked(bool checked)
{
    stateMachine = 1;
    timerExpositionTimes->start(1500);
    hidenHorizontalVerticalLabels();
}

void MainWindow_UserSelectedBed::on_pushButtonStadistics_clicked(bool checked)
{
    stateMachine = 2;
    //timerExpositionTimes->stop();
    hidenLabelesExpositionTimes();
    hidenHorizontalVerticalLabels();
}

void MainWindow_UserSelectedBed::on_pushButtonStadistics_2_clicked(bool checked)
{
    stateMachine = 3;
    timerExpositionTimes->stop();
    hidenLabelesExpositionTimes();
    hidenHorizontalVerticalLabels();
}

void MainWindow_UserSelectedBed::userSelectedBed(int bed){
 userSelectedBed_int = bed;

 if(userSelectedBed_int == 1){
     QPixmap pixmapFourBedsImage("/Users/FING156561/Developer/Flexible1_1/UCI1.png");
    ui->label_fourBedsImage->setPixmap(pixmapFourBedsImage);
 }else if (userSelectedBed_int == 2){
    QPixmap pixmapFourBedsImage("/Users/FING156561/Developer/Flexible1_1/UCI2.png");
    ui->label_fourBedsImage->setPixmap(pixmapFourBedsImage);
 }else if (userSelectedBed_int == 3){
     QPixmap pixmapFourBedsImage("/Users/FING156561/Developer/Flexible1_1/UCI3.png");
     ui->label_fourBedsImage->setPixmap(pixmapFourBedsImage);
  }else if (userSelectedBed_int == 4){
     QPixmap pixmapFourBedsImage("/Users/FING156561/Developer/Flexible1_1/UCI4.png");
     ui->label_fourBedsImage->setPixmap(pixmapFourBedsImage);
  }
}

void MainWindow_UserSelectedBed::reloadExpositionTimes(){
    qDebug()<< "open db=" << open;
    if(open){
        QSqlQuery query(db);
        query.prepare("SELECT * FROM  tiemposExposicion WHERE 1");
        query.exec();
        while (query.next()){
            QString sensorID = query.value(0).toString();
            if (sensorID == "1"){
                QString expositionTimesSensor1 = query.value(1).toString();
                qDebug()<< "datos sensor 1" << expositionTimesSensor1;
                reloadExpositionTimesSensor1(expositionTimesSensor1, 1);
            }
            if (sensorID == "2"){
                QString expositionTimesSensor2 = query.value(1).toString();
                qDebug()<< "datos sensor 2" << expositionTimesSensor2;
                reloadExpositionTimesSensor2(expositionTimesSensor2, 2);
            }
        }
        db.commit();
        qDebug()<<query.next();
    }
}

void MainWindow_UserSelectedBed::reloadExpositionTimesSensor1(QString expositionTimes, int sensorID){
    QStringList vectorExpositionTimes = expositionTimes.split(",");

    if (vectorExpositionTimes[0]  == "00:00:00"){
        ui->label_zona1_3->setHidden(true);
    }else{
        ui->label_zona1_3->setHidden(false);
    }

    if (vectorExpositionTimes[1]  == "00:00:00"){
        ui->label_zona1_2->setHidden(true);
    }else{
        ui->label_zona1_2->setHidden(false);
    }

    if (vectorExpositionTimes[2]  == "00:00:00"){
        ui->label_zona1_1->setHidden(true);
    }else{
        ui->label_zona1_1->setHidden(false);
    }

    if (vectorExpositionTimes[3]  == "00:00:00"){
        ui->label_zona1_6->setHidden(true);
    }else{
        ui->label_zona1_6->setHidden(false);
    }
    if (vectorExpositionTimes[4]  == "00:00:00"){
        ui->label_zona1_5->setHidden(true);
    }else{
        ui->label_zona1_5->setHidden(false);
    }
    if (vectorExpositionTimes[5]  == "00:00:00"){
        ui->label_zona1_4->setHidden(true);
    }else{
        ui->label_zona1_4->setHidden(false);
    }

    if (vectorExpositionTimes[6]  == "00:00:00"){
        ui->label_zona1_9->setHidden(true);
    }else{
        ui->label_zona1_9->setHidden(false);
    }

    if (vectorExpositionTimes[7]  == "00:00:00"){
        ui->label_zona1_8->setHidden(true);
    }else{
        ui->label_zona1_8->setHidden(false);
    }

    if (vectorExpositionTimes[8]  == "00:00:00"){
        ui->label_zona1_7->setHidden(true);
    }else{
        ui->label_zona1_7->setHidden(false);
    }

    QString timeZone1_1 = vectorExpositionTimes[2];
    QString timeZone1_2 = vectorExpositionTimes[1];
    QString timeZone1_3 = vectorExpositionTimes[0];

    QString timeZone2_1 = vectorExpositionTimes[5];
    QString timeZone2_2 = vectorExpositionTimes[4];
    QString timeZone2_3 = vectorExpositionTimes[3];

    QString timeZone3_1 = vectorExpositionTimes[8];
    QString timeZone3_2 = vectorExpositionTimes[7];
    QString timeZone3_3 = vectorExpositionTimes[6];

    ui->label_zona1_1->setText(timeZone1_1);
    ui->label_zona1_2->setText(timeZone1_2);
    ui->label_zona1_3->setText(timeZone1_3);

    ui->label_zona1_4->setText(timeZone2_1);
    ui->label_zona1_5->setText(timeZone2_2);
    ui->label_zona1_6->setText(timeZone2_3);

    ui->label_zona1_7->setText(timeZone3_1);
    ui->label_zona1_8->setText(timeZone3_2);
    ui->label_zona1_9->setText(timeZone3_3);

}

void MainWindow_UserSelectedBed::reloadExpositionTimesSensor2(QString expositionTimes, int sensorID){
    QStringList vectorExpositionTimes = expositionTimes.split(",");

    if (vectorExpositionTimes[0]  == "00:00:00"){
        ui->label_zona2_9->setHidden(true);
    }else{
        ui->label_zona2_9->setHidden(false);
    }

    if (vectorExpositionTimes[1]  == "00:00:00"){
        ui->label_zona2_6->setHidden(true);
    }else{
        ui->label_zona2_6->setHidden(false);
    }

    if (vectorExpositionTimes[2]  == "00:00:00"){
        ui->label_zona2_3->setHidden(true);
    }else{
        ui->label_zona2_3->setHidden(false);
    }

    if (vectorExpositionTimes[3]  == "00:00:00"){
        ui->label_zona2_8->setHidden(true);
    }else{
        ui->label_zona2_8->setHidden(false);
    }
    if (vectorExpositionTimes[4]  == "00:00:00"){
        ui->label_zona2_5->setHidden(true);
    }else{
        ui->label_zona2_5->setHidden(false);
    }
    if (vectorExpositionTimes[5]  == "00:00:00"){
        ui->label_zona2_2->setHidden(true);
    }else{
        ui->label_zona2_2->setHidden(false);
    }

    if (vectorExpositionTimes[6]  == "00:00:00"){
        ui->label_zona2_7->setHidden(true);
    }else{
        ui->label_zona2_7->setHidden(false);
    }

    if (vectorExpositionTimes[7]  == "00:00:00"){
        ui->label_zona2_4->setHidden(true);
    }else{
        ui->label_zona2_4->setHidden(false);
    }

    if (vectorExpositionTimes[8]  == "00:00:00"){
        ui->label_zona2_1->setHidden(true);
    }else{
        ui->label_zona2_1->setHidden(false);
    }

    QString timeZone1_1 = vectorExpositionTimes[0];
    QString timeZone1_2 = vectorExpositionTimes[1];
    QString timeZone1_3 = vectorExpositionTimes[2];

    QString timeZone2_1 = vectorExpositionTimes[3];
    QString timeZone2_2 = vectorExpositionTimes[4];
    QString timeZone2_3 = vectorExpositionTimes[5];

    QString timeZone3_1 = vectorExpositionTimes[6];
    QString timeZone3_2 = vectorExpositionTimes[7];
    QString timeZone3_3 = vectorExpositionTimes[8];

    ui->label_zona2_1->setText(timeZone3_3);
    ui->label_zona2_2->setText(timeZone2_3);
    ui->label_zona2_3->setText(timeZone1_3);

    ui->label_zona2_4->setText(timeZone3_2);
    ui->label_zona2_5->setText(timeZone2_2);
    ui->label_zona2_6->setText(timeZone1_2);

    ui->label_zona2_7->setText(timeZone3_1);
    ui->label_zona2_8->setText(timeZone2_1);
    ui->label_zona2_9->setText(timeZone1_1);
}

void MainWindow_UserSelectedBed::hidenLabelesExpositionTimes(){

        ui->label_zona1_1->setHidden(true);
        ui->label_zona1_2->setHidden(true);
        ui->label_zona1_3->setHidden(true);

        ui->label_zona1_4->setHidden(true);
        ui->label_zona1_5->setHidden(true);
        ui->label_zona1_6->setHidden(true);

        ui->label_zona1_7->setHidden(true);
        ui->label_zona1_8->setHidden(true);
        ui->label_zona1_9->setHidden(true);

        ui->label_zona2_1->setHidden(true);
        ui->label_zona2_2->setHidden(true);
        ui->label_zona2_3->setHidden(true);

        ui->label_zona2_4->setHidden(true);
        ui->label_zona2_5->setHidden(true);
        ui->label_zona2_6->setHidden(true);

        ui->label_zona2_7->setHidden(true);
        ui->label_zona2_8->setHidden(true);
        ui->label_zona2_9->setHidden(true);

}
void MainWindow_UserSelectedBed::hidenHorizontalVerticalLabels(){
    if(stateMachine == 0 || stateMachine == 3){
        ui->label_VerticalDivision1->setHidden(true);
        ui->label_VerticalDivision2->setHidden(true);
        ui->label_VerticalDivision3->setHidden(true);
        ui->label_VerticalDivision4->setHidden(true);
        ui->label_VerticalDivision5->setHidden(true);
        ui->label_HorizontalDivision1->setHidden(true);
        ui->label_HorizontalDivision2->setHidden(true);
    }else{
        ui->label_VerticalDivision1->setHidden(false);
        ui->label_VerticalDivision2->setHidden(false);
        ui->label_VerticalDivision3->setHidden(false);
        ui->label_VerticalDivision4->setHidden(false);
        ui->label_VerticalDivision5->setHidden(false);
        ui->label_HorizontalDivision1->setHidden(false);
        ui->label_HorizontalDivision2->setHidden(false);
    }
}

