#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQuickView>
#include <QObject>
#include "maptown.h"
#include "farmingslot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void closeEvent(QCloseEvent *eventClose);

    void show_Price_Farm();
    void show_Price_Stable();
    void show_Price_Market();
    void show_Price_Mine();
    void show_Price_Townhall();

    void calc_Time_Absence(int, int, int, int, int, int);
    void calc_Cash_Absence(qint64);

    void change_data_scene_map_Town();

private slots:
    void calculate_Cash();
    void show_Cash();
    void show_All_Price();
    void set_need_Workers();

    void on_pushButton_fermers_clicked();
    void on_pushButton_fermersHouse_clicked();
    void on_pushButton_horseman_clicked();
    void on_pushButton_stables_clicked();
    void on_pushButton_mine_clicked();
    void on_pushButton_miner_clicked();
    void on_pushButton_mayor_clicked();
    void on_pushButton_townhall_clicked();
    void on_pushButton_marketeer_clicked();
    void on_pushButton_market_clicked();

    void on_pushButton_fermers_MAX_clicked();
    void on_pushButton_horseman_MAX_clicked();
    void on_pushButton_miner_MAX_clicked();
    void on_pushButton_mayor_MAX_clicked();
    void on_pushButton_marketeer_MAX_clicked();

    void on_pushButton_addMarketeer_clicked();

    void on_pushButton_change_ectt_clicked();

private:

    Ui::MainWindow *ui;
//    friend class PauseDialog;
    mapTown *nMapTown;

    unsigned long int tempCash = 120;
    int countAvailableMarket = 0;

};

#endif // MAINWINDOW_H
