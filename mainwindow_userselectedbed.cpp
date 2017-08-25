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

QString pathFlexible1 = "/Applications/XAMPP/xamppfiles/htdocs/sensorFlexible_UDP_Protocol/sensorFlexibleSQLiteDB/";

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
    stateMachine = 0;
    ui->pushButtonPressureButton->setEnabled(true);
    ui->pushButtonPressureButton->setStyleSheet("background: #222222; color:white");

    ui->pushButtonExpositionTimes->setEnabled(true);
    ui->pushButtonExpositionTimes->setStyleSheet("background: #222222; color:white");

    ui->pushButtonStadistics_2->setEnabled(true);
    ui->pushButtonStadistics_2->setStyleSheet("background: #222222; color:white");

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
    QPixmap pixmapSensor1(pathFlexible1 + "GraficoPresion.png");
    QPixmap pixmapSensor2(pathFlexible1 + "GraficoPresion.png");
    QPixmap historicGraphs(pathFlexible1 + "GraficoPresion.png");
    QImage imageSensor(pathFlexible1 + "sensor1.jpeg");

     if(stateMachine == 0 || stateMachine == 1){
         imageSensor = QImage(pathFlexible1 + "sensor1.jpeg");

         pixmapSensor1 = QPixmap(pathFlexible1 + "sensor1.jpeg");
         qDebug()<< "size"<< pixmapSensor1.toImage().size();
         qDebug()<< "valor en pixel"<< pixmapSensor1.toImage().pixel(799,399);
         if (pixmapSensor1.toImage().pixel(799,399)==4294967039){
             if(pixmapSensor1.size().width()==0 & pixmapSensor1.size().height()==0){

             }else{
                 ui->label_stadisticWindow->setPixmap(pixmapSensor1);
             }

         }else{
            qDebug()<< "entra 2";
         }
     }

     historicGraphs = QPixmap(pathFlexible1 + "historial_main.png");

     if (historicGraphs.width() == 0 || historicGraphs.height() == 0){

     }else{
         ui->label_historicRegisters->setPixmap(historicGraphs);
     }

     reloadAveragePressureValues();


}

void MainWindow_UserSelectedBed::on_pushButtonPressureButton_clicked(bool checked)
{
    stateMachine = 0;
    ui->pushButtonPressureButton->setEnabled(false);
    ui->pushButtonPressureButton->setStyleSheet("background: green; color:white");

    ui->pushButtonExpositionTimes->setEnabled(true);
    ui->pushButtonExpositionTimes->setStyleSheet("background: #222222; color:white");

    ui->pushButtonStadistics_2->setEnabled(true);
    ui->pushButtonStadistics_2->setStyleSheet("background: #222222; color:white");

    ui->customPlot->setHidden(true);
    qDebug()<<"distribucion";
    timer->stop();
    timer->start(200);
    timerExpositionTimes->stop();
    hidenLabelesExpositionTimes();
    hidenHorizontalVerticalLabels();

}


void MainWindow_UserSelectedBed::on_pushButtonExpositionTimes_clicked(bool checked)
{
    // Abre base de datos que almacena los tiempos de exposicion
    QString path = pathFlexible1 + "estadisticas.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("tiemposExposicion");
    db.setDatabaseName(path);
    open = db.open();

    stateMachine = 1;

    ui->pushButtonPressureButton->setEnabled(true);
    ui->pushButtonPressureButton->setStyleSheet("background: #222222; color:white");

    ui->pushButtonExpositionTimes->setEnabled(false);
    ui->pushButtonExpositionTimes->setStyleSheet("background: green; color:white");

    ui->pushButtonStadistics_2->setEnabled(true);
    ui->pushButtonStadistics_2->setStyleSheet("background: #222222; color:white");

    timerExpositionTimes->stop();
    timerExpositionTimes->start(1500);

    hidenHorizontalVerticalLabels();

    ui->customPlot->setHidden(true);
}

void MainWindow_UserSelectedBed::on_pushButtonStadistics_2_clicked(bool checked)
{
    // Abre base de datos que almacena los promedios de presion por zonas
    QString pathPromedios = pathFlexible1 + "estadisticasPromedios.db";
    QSqlDatabase dbPromedios = QSqlDatabase::addDatabase("QSQLITE");
    dbPromedios.setHostName("promediosPresion");
    dbPromedios.setDatabaseName(pathPromedios);
    openPromedios = dbPromedios.open();

    stateMachine = 2;
    ui->pushButtonPressureButton->setEnabled(true);
    ui->pushButtonPressureButton->setStyleSheet("background: #222222; color:white");

    ui->pushButtonExpositionTimes->setEnabled(true);
    ui->pushButtonExpositionTimes->setStyleSheet("background: #222222; color:white");

    ui->pushButtonStadistics_2->setEnabled(false);
    ui->pushButtonStadistics_2->setStyleSheet("background: green; color:white");

    timerExpositionTimes->stop();
    hidenLabelesExpositionTimes();
    hidenHorizontalVerticalLabels();

    ui->customPlot->setHidden(false);
}

void MainWindow_UserSelectedBed::userSelectedBed(int bed){
 userSelectedBed_int = bed;

 if(userSelectedBed_int == 1){
     QPixmap pixmapFourBedsImage(":/images/UCI1.png");
    ui->label_fourBedsImage->setPixmap(pixmapFourBedsImage);
 }else if (userSelectedBed_int == 2){
    QPixmap pixmapFourBedsImage(":/images/UCI2.png");
    ui->label_fourBedsImage->setPixmap(pixmapFourBedsImage);
 }else if (userSelectedBed_int == 3){
     QPixmap pixmapFourBedsImage(":/images/UCI3.png");
     ui->label_fourBedsImage->setPixmap(pixmapFourBedsImage);
  }else if (userSelectedBed_int == 4){
     QPixmap pixmapFourBedsImage(":/images/UCI4.png");
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
        ui->label_zona1_0_0->setHidden(true);
    }else{
        ui->label_zona1_0_0->setHidden(false);
    }

    if (vectorExpositionTimes[1]  == "00:00:00"){
        ui->label_zona1_0_1->setHidden(true);
    }else{
        ui->label_zona1_0_1->setHidden(false);
    }

    if (vectorExpositionTimes[2]  == "00:00:00"){
        ui->label_zona1_0_2->setHidden(true);
    }else{
        ui->label_zona1_0_2->setHidden(false);
    }

    if (vectorExpositionTimes[3]  == "00:00:00"){
        ui->label_zona1_1_0->setHidden(true);
    }else{
        ui->label_zona1_1_0->setHidden(false);
    }

    if (vectorExpositionTimes[4]  == "00:00:00"){
        ui->label_zona1_1_1->setHidden(true);
    }else{
        ui->label_zona1_1_1->setHidden(false);
    }

    if (vectorExpositionTimes[5]  == "00:00:00"){
        ui->label_zona1_1_2->setHidden(true);
    }else{
        ui->label_zona1_1_2->setHidden(false);
    }

    if (vectorExpositionTimes[6]  == "00:00:00"){
        ui->label_zona1_2_0->setHidden(true);
    }else{
        ui->label_zona1_2_0->setHidden(false);
    }

    if (vectorExpositionTimes[7]  == "00:00:00"){
        ui->label_zona1_2_1->setHidden(true);
    }else{
        ui->label_zona1_2_1->setHidden(false);
    }

    if (vectorExpositionTimes[8]  == "00:00:00"){
        ui->label_zona1_2_2->setHidden(true);
    }else{
        ui->label_zona1_2_2->setHidden(false);
    }

    QString timeZone0_0 = vectorExpositionTimes[0];
    QString timeZone0_1 = vectorExpositionTimes[1];
    QString timeZone0_2 = vectorExpositionTimes[2];

    QString timeZone1_0 = vectorExpositionTimes[3];
    QString timeZone1_1 = vectorExpositionTimes[4];
    QString timeZone1_2 = vectorExpositionTimes[5];

    QString timeZone2_0 = vectorExpositionTimes[6];
    QString timeZone2_1 = vectorExpositionTimes[7];
    QString timeZone2_2 = vectorExpositionTimes[8];

    ui->label_zona1_0_0->setText(timeZone0_0);
    ui->label_zona1_0_1->setText(timeZone0_1);
    ui->label_zona1_0_2->setText(timeZone0_2);

    ui->label_zona1_1_0->setText(timeZone1_0);
    ui->label_zona1_1_1->setText(timeZone1_1);
    ui->label_zona1_1_2->setText(timeZone1_2);

    ui->label_zona1_2_0->setText(timeZone2_0);
    ui->label_zona1_2_1->setText(timeZone2_1);
    ui->label_zona1_2_2->setText(timeZone2_2);



}

void MainWindow_UserSelectedBed::reloadExpositionTimesSensor2(QString expositionTimes, int sensorID){
    QStringList vectorExpositionTimes = expositionTimes.split(",");

    if (vectorExpositionTimes[0]  == "00:00:00"){
        ui->label_zona2_0_0->setHidden(true);
    }else{
        ui->label_zona2_0_0->setHidden(false);
    }

    if (vectorExpositionTimes[1]  == "00:00:00"){
        ui->label_zona2_0_1->setHidden(true);
    }else{
        ui->label_zona2_0_1->setHidden(false);
    }

    if (vectorExpositionTimes[2]  == "00:00:00"){
        ui->label_zona2_0_2->setHidden(true);
    }else{
        ui->label_zona2_0_2->setHidden(false);
    }

    if (vectorExpositionTimes[3]  == "00:00:00"){
        ui->label_zona2_1_0->setHidden(true);
    }else{
        ui->label_zona2_1_0->setHidden(false);
    }

    if (vectorExpositionTimes[4]  == "00:00:00"){
        ui->label_zona2_1_1->setHidden(true);
    }else{
        ui->label_zona2_1_1->setHidden(false);
    }

    if (vectorExpositionTimes[5]  == "00:00:00"){
        ui->label_zona2_1_2->setHidden(true);
    }else{
        ui->label_zona2_1_2->setHidden(false);
    }

    if (vectorExpositionTimes[6]  == "00:00:00"){
        ui->label_zona2_2_0->setHidden(true);
    }else{
        ui->label_zona2_2_0->setHidden(false);
    }

    if (vectorExpositionTimes[7]  == "00:00:00"){
        ui->label_zona2_2_1->setHidden(true);
    }else{
        ui->label_zona2_2_1->setHidden(false);
    }

    if (vectorExpositionTimes[8]  == "00:00:00"){
        ui->label_zona2_2_2->setHidden(true);
    }else{
        ui->label_zona2_2_2->setHidden(false);
    }


    QString timeZone0_0 = vectorExpositionTimes[0];
    QString timeZone0_1 = vectorExpositionTimes[1];
    QString timeZone0_2 = vectorExpositionTimes[2];

    QString timeZone1_0 = vectorExpositionTimes[3];
    QString timeZone1_1 = vectorExpositionTimes[4];
    QString timeZone1_2 = vectorExpositionTimes[5];

    QString timeZone2_0 = vectorExpositionTimes[6];
    QString timeZone2_1 = vectorExpositionTimes[7];
    QString timeZone2_2 = vectorExpositionTimes[8];

    ui->label_zona2_0_0->setText(timeZone0_0);
    ui->label_zona2_0_1->setText(timeZone0_1);
    ui->label_zona2_0_2->setText(timeZone0_2);

    ui->label_zona2_1_0->setText(timeZone1_0);
    ui->label_zona2_1_1->setText(timeZone1_1);
    ui->label_zona2_1_2->setText(timeZone1_2);

    ui->label_zona2_2_0->setText(timeZone2_0);
    ui->label_zona2_2_1->setText(timeZone2_1);
    ui->label_zona2_2_2->setText(timeZone2_2);

}

void MainWindow_UserSelectedBed::hidenLabelesExpositionTimes(){

        ui->label_zona1_2_0->setHidden(true);
        ui->label_zona1_1_0->setHidden(true);
        ui->label_zona1_0_0->setHidden(true);

        ui->label_zona1_2_1->setHidden(true);
        ui->label_zona1_1_1->setHidden(true);
        ui->label_zona1_0_1->setHidden(true);

        ui->label_zona1_2_2->setHidden(true);
        ui->label_zona1_1_2->setHidden(true);
        ui->label_zona1_0_2->setHidden(true);

        ui->label_zona2_2_0->setHidden(true);
        ui->label_zona2_1_0->setHidden(true);
        ui->label_zona2_0_0->setHidden(true);

        ui->label_zona2_2_1->setHidden(true);
        ui->label_zona2_1_1->setHidden(true);
        ui->label_zona2_0_1->setHidden(true);

        ui->label_zona2_2_2->setHidden(true);
        ui->label_zona2_1_2->setHidden(true);
        ui->label_zona2_0_2->setHidden(true);

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

void MainWindow_UserSelectedBed::reloadInclinationBedImage(){

    QPixmap pixmapInclinationBedImage(pathFlexible1 + "inclinacion.jpeg");
    if (pixmapInclinationBedImage.width() == 0 || pixmapInclinationBedImage.height() == 0){

    }else{
        ui->label_Inclinacion->setPixmap(pixmapInclinationBedImage);
    }
}

