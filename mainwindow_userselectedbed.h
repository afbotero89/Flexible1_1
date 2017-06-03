#ifndef MAINWINDOW_USERSELECTEDBED_H
#define MAINWINDOW_USERSELECTEDBED_H

#include <QMainWindow>

namespace Ui {
class MainWindow_UserSelectedBed;
}

class MainWindow_UserSelectedBed : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_UserSelectedBed(QWidget *parent = 0);
    ~MainWindow_UserSelectedBed();

    void initActionsConnections();

    void userSelectedBed(int bed);

    void reloadExpositionTimesSensor1(QString expositionTimes, int sensorID);

    void reloadExpositionTimesSensor2(QString expositionTimes, int sensorID);

    void hidenLabelesExpositionTimes();

    void hidenHorizontalVerticalLabels();

    void reloadAveragePressureValues();

    void insertPlots(QString promediosZona1, QString promediosZona2, QString promediosZona3, QString promediosZona4, QString promediosZona5, QString promediosZona6);

    void changeControlImage();

private slots:

    void reloadExpositionTimes();

    void on_pushButton_4_clicked(bool checked);

    void reloadStadisticsImage();

    void on_pushButtonPressureButton_clicked(bool checked);

    void on_pushButtonExpositionTimes_clicked(bool checked);

    void on_pushButtonStadistics_2_clicked(bool checked);

private:
    Ui::MainWindow_UserSelectedBed *ui;
};

#endif // MAINWINDOW_USERSELECTEDBED_H
