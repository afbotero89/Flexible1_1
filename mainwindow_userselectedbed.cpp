#include "mainwindow_userselectedbed.h"
#include "ui_mainwindow_userselectedbed.h"
#include <QDebug>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QSqlQuery>

QTimer *timer;
QTimer *timerExpositionTimes;

int stateMachine = 0;   //0:Distribucion presion sin tiempos, 1:Distribucion presion con tiempos, 2:Estadisticas 1
int userSelectedBed_int = 1;

bool open = false;
QSqlDatabase db;

bool openPromedios = false;
QSqlDatabase dbPromedios;

int contador = 0;

QString promediosZona1;
QString promediosZona2;
QString promediosZona3;
QString promediosZona4;
QString promediosZona5;
QString promediosZona6;

int countImageControl = 0;

MainWindow_UserSelectedBed::MainWindow_UserSelectedBed(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_UserSelectedBed)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timerExpositionTimes = new QTimer(this);

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

    changeControlImage();
    QPixmap pixmapSensor1("/Users/FING156561/Developer/Flexible1_1/GraficoPresion.png");
    QPixmap pixmapSensor2("/Users/FING156561/Developer/Flexible1_1/GraficoPresion.png");
    QPixmap historicGraphs("/Users/FING156561/Developer/Flexible1_1/GraficoPresion.png");
    QImage imageSensor("/Applications/XAMPP/xamppfiles/htdocs/sensorFlexible_UDP_Protocol/appSensorFlexibleWebLocalMatplotlib/img/sensor1.jpeg");

     if(stateMachine == 0 || stateMachine == 1){
         imageSensor = QImage("/Applications/XAMPP/xamppfiles/htdocs/sensorFlexible_UDP_Protocol/appSensorFlexibleWebLocalMatplotlib/img/sensor1.jpeg");

         pixmapSensor1 = QPixmap("/Applications/XAMPP/xamppfiles/htdocs/sensorFlexible_UDP_Protocol/appSensorFlexibleWebLocalMatplotlib/img/sensor1.jpeg");
         qDebug()<< "size"<< pixmapSensor1.toImage().size();
         qDebug()<< "valor en pixel"<< pixmapSensor1.toImage().pixel(799,399);
         if (pixmapSensor1.toImage().pixel(799,399)==4278190334){
             if(pixmapSensor1.size().width()==0 & pixmapSensor1.size().height()==0){

             }else{
                 ui->label_stadisticWindow->setPixmap(pixmapSensor1);
             }

         }else{
            qDebug()<< "entra 2";
         }
     }

     if(stateMachine == 0){

        historicGraphs = QPixmap("/Applications/XAMPP/xamppfiles/htdocs/flexible1.1/img/historial_main.png");

        if (historicGraphs.width() == 0 || historicGraphs.height() == 0){

        }else{
            ui->label_historicRegisters->setPixmap(historicGraphs);
        }

    }else if (stateMachine == 1){

        historicGraphs = QPixmap("/Applications/XAMPP/xamppfiles/htdocs/flexible1.1/img/historial_main.png");

        if (historicGraphs.width() == 0 || historicGraphs.height() == 0){

        }else{
            ui->label_historicRegisters->setPixmap(historicGraphs);
        }

    }else if(stateMachine == 2){

        historicGraphs = QPixmap("/Applications/XAMPP/xamppfiles/htdocs/flexible1.1/img/historial_main.png");

        if (historicGraphs.width() == 0 || historicGraphs.height() == 0){

        }else{
            ui->label_historicRegisters->setPixmap(historicGraphs);
        }

        reloadAveragePressureValues();
    }

}

void MainWindow_UserSelectedBed::on_pushButtonPressureButton_clicked(bool checked)
{
    stateMachine = 0;
    ui->customPlot->setHidden(true);
    qDebug()<<"distribucion";
    timer->start(200);
    timerExpositionTimes->stop();
    hidenLabelesExpositionTimes();
    hidenHorizontalVerticalLabels();

}


void MainWindow_UserSelectedBed::on_pushButtonExpositionTimes_clicked(bool checked)
{
    // Abre base de datos que almacena los tiempos de exposicion
    QString path = "/Applications/XAMPP/xamppfiles/htdocs/sensorFlexible_UDP_Protocol/sensorFlexibleSQLiteDB/estadisticas.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("tiemposExposicion");
    db.setDatabaseName(path);
    open = db.open();

    stateMachine = 1;
    timerExpositionTimes->start(1500);
    hidenHorizontalVerticalLabels();

    ui->customPlot->setHidden(true);
}

void MainWindow_UserSelectedBed::on_pushButtonStadistics_2_clicked(bool checked)
{
    // Abre base de datos que almacena los promedios de presion por zonas
    QString pathPromedios = "/Applications/XAMPP/xamppfiles/htdocs/sensorFlexible_UDP_Protocol/sensorFlexibleSQLiteDB/estadisticasPromedios.db";
    QSqlDatabase dbPromedios = QSqlDatabase::addDatabase("QSQLITE");
    dbPromedios.setHostName("promediosPresion");
    dbPromedios.setDatabaseName(pathPromedios);
    openPromedios = dbPromedios.open();

    stateMachine = 2;
    timerExpositionTimes->stop();
    hidenLabelesExpositionTimes();
    hidenHorizontalVerticalLabels();

    ui->customPlot->setHidden(false);
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
    if(open){
        QSqlQuery query(db);
        query.prepare("SELECT * FROM  tiemposExposicion WHERE 1");
        query.exec();
        while (query.next()){
            QString sensorID = query.value(0).toString();
            if (sensorID == "1"){
                QString expositionTimesSensor1 = query.value(1).toString();
                reloadExpositionTimesSensor1(expositionTimesSensor1, 1);
            }
            if (sensorID == "2"){
                QString expositionTimesSensor2 = query.value(1).toString();
                reloadExpositionTimesSensor2(expositionTimesSensor2, 2);
            }
        }
        db.commit();
    }
}

void MainWindow_UserSelectedBed::reloadAveragePressureValues(){

    if(openPromedios){
        QSqlQuery queryPromedios(dbPromedios);
        queryPromedios.prepare("SELECT * FROM  promediosPresionZonas WHERE 1");
        queryPromedios.exec();

        while (queryPromedios.next()){
            QString sensorID = queryPromedios.value(0).toString();
            if (sensorID == "1"){
                promediosZona1 = queryPromedios.value(1).toString();
            }
            if (sensorID == "2"){
                promediosZona2 = queryPromedios.value(1).toString();
            }
            if (sensorID == "3"){
                promediosZona3 = queryPromedios.value(1).toString();
            }
            if (sensorID == "4"){
                promediosZona4 = queryPromedios.value(1).toString();
            }
            if (sensorID == "5"){
                promediosZona5 = queryPromedios.value(1).toString();
            }
            if (sensorID == "6"){
                promediosZona6 = queryPromedios.value(1).toString();
            }
        }
        insertPlots(promediosZona1, promediosZona2, promediosZona3, promediosZona4, promediosZona5, promediosZona6);
        dbPromedios.commit();
    }
}
void MainWindow_UserSelectedBed::insertPlots(QString promediosZona1, QString promediosZona2, QString promediosZona3, QString promediosZona4, QString promediosZona5, QString promediosZona6){
    QVector<double> x, y, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5;
    QVector<QCPScatterStyle::ScatterShape> shapes;
    shapes << QCPScatterStyle::ssCircle;

    if(contador >= 55){
        x.clear();
        y.clear();
        x1.clear();
        y1.clear();
        contador = 0;
        ui->customPlot->clearGraphs();
    }

    QStringList vectorPromedioZona1 = promediosZona1.split(',');
    QString valorFloat = vectorPromedioZona1.last();
    x.append(contador);
    y.append(valorFloat.toFloat());

    QStringList vectorPromedioZona2 = promediosZona2.split(',');
    QString valorFloat2 = vectorPromedioZona2.last();
    x1.append(contador);
    y1.append(valorFloat2.toFloat());

    QStringList vectorPromedioZona3 = promediosZona3.split(',');
    QString valorFloat3 = vectorPromedioZona3.last();
    x2.append(contador);
    y2.append(valorFloat3.toFloat());

    QStringList vectorPromedioZona4 = promediosZona4.split(',');
    QString valorFloat4 = vectorPromedioZona4.last();
    x3.append(contador);
    y3.append(valorFloat4.toFloat());

    QStringList vectorPromedioZona5 = promediosZona5.split(',');
    QString valorFloat5 = vectorPromedioZona5.last();
    x4.append(contador);
    y4.append(valorFloat5.toFloat());

    QStringList vectorPromedioZona6 = promediosZona6.split(',');
    QString valorFloat6 = vectorPromedioZona6.last();
    x5.append(contador);
    y5.append(valorFloat6.toFloat());

    ui->customPlot->addGraph();
    //ui->customPlot->graph(0)->setData(x, y);  // setData para graficar vectores completos
    ui->customPlot->graph(0)->addData(x, y);   // para graficar punto a punto
    // Nombrar los ejes
    ui->customPlot->yAxis->setLabel("Magnitud");

    ui->customPlot->xAxis->setRange(0,60);
    ui->customPlot->graph(0)->rescaleValueAxis();
    ui->customPlot->yAxis->setRange(0,600);
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->customPlot->graph()->setScatterStyle(QCPScatterStyle(shapes.at(0), 5));



    ui->customPlot->addGraph();
    //ui->customPlot->graph(1)->setData(x1, y1); // setData para graficar vectores completos
    ui->customPlot->graph(1)->addData(x1, y1);   // para graficar punto a punto
    // Nombrar los ejes
    ui->customPlot->yAxis->setLabel("Magnitud");

    ui->customPlot->xAxis->setRange(0,60);
    ui->customPlot->graph(1)->rescaleValueAxis();
    ui->customPlot->yAxis->setRange(0,600);
    ui->customPlot->graph(1)->setPen(QPen(Qt::black));
    ui->customPlot->graph()->setScatterStyle(QCPScatterStyle(shapes.at(0), 5));


    ui->customPlot->addGraph();
    //ui->customPlot->graph(1)->setData(x1, y1); // setData para graficar vectores completos
    ui->customPlot->graph(2)->addData(x2, y2);   // para graficar punto a punto
    // Nombrar los ejes
    ui->customPlot->yAxis->setLabel("Magnitud");

    ui->customPlot->xAxis->setRange(0,60);
    ui->customPlot->graph(2)->rescaleValueAxis();
    ui->customPlot->yAxis->setRange(0,600);
    ui->customPlot->graph(2)->setPen(QPen(Qt::blue));
    ui->customPlot->graph()->setScatterStyle(QCPScatterStyle(shapes.at(0), 5));


    ui->customPlot->addGraph();
    //ui->customPlot->graph(1)->setData(x1, y1); // setData para graficar vectores completos
    ui->customPlot->graph(3)->addData(x3, y3);   // para graficar punto a punto
    // Nombrar los ejes
    ui->customPlot->yAxis->setLabel("Magnitud");

    ui->customPlot->xAxis->setRange(0,60);
    ui->customPlot->graph(3)->rescaleValueAxis();
    ui->customPlot->yAxis->setRange(0,600);
    ui->customPlot->graph(3)->setPen(QPen(Qt::black));
    ui->customPlot->graph()->setScatterStyle(QCPScatterStyle(shapes.at(0), 5));


    ui->customPlot->addGraph();
    //ui->customPlot->graph(1)->setData(x1, y1); // setData para graficar vectores completos
    ui->customPlot->graph(4)->addData(x4, y4);   // para graficar punto a punto
    // Nombrar los ejes
    ui->customPlot->yAxis->setLabel("Magnitud");

    ui->customPlot->xAxis->setRange(0,60);
    ui->customPlot->graph(4)->rescaleValueAxis();
    ui->customPlot->yAxis->setRange(0,600);
    ui->customPlot->graph(4)->setPen(QPen(Qt::blue));
    ui->customPlot->graph()->setScatterStyle(QCPScatterStyle(shapes.at(0), 5));


    ui->customPlot->addGraph();
    //ui->customPlot->graph(1)->setData(x1, y1); // setData para graficar vectores completos
    ui->customPlot->graph(5)->addData(x5, y5);   // para graficar punto a punto
    // Nombrar los ejes
    ui->customPlot->yAxis->setLabel("Magnitud");

    ui->customPlot->xAxis->setRange(0,60);
    ui->customPlot->graph(5)->rescaleValueAxis();
    ui->customPlot->yAxis->setRange(0,600);
    ui->customPlot->graph(5)->setPen(QPen(Qt::black));
    ui->customPlot->graph()->setScatterStyle(QCPScatterStyle(shapes.at(0), 5));
    ui->customPlot->replot();
    ui->customPlot->yAxis->setVisible(false);

    contador = contador + 1;

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
    if(stateMachine == 0 || stateMachine == 2){
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

void MainWindow_UserSelectedBed::changeControlImage(){
    QPixmap imageControl(":/images/controlActivo1.png");
    countImageControl = countImageControl + 1;
    if(countImageControl<10){
        imageControl = QPixmap(":/images/controlActivo1.png");
    }else if(countImageControl >= 10){
        imageControl = QPixmap(":/images/control1.1.png");
    }
    if (countImageControl>20){
        countImageControl = 0;
    }
    ui->label_BedControl->setPixmap(imageControl);
}

