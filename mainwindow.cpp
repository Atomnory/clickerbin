#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pausedialog.h"
#include <QCoreApplication>
#include <QTimer>
#include <QtMath>
#include <QFile>
#include <QTextStream>
#include <QTime>
#include <QDate>


static FarmingSlot farm(10, 100, 2);
static FarmingSlot stable(100, 1000, 3);
static FarmingSlot mine(1000, 10000, 4);
static FarmingSlot market(10000, 1000000, 5);
QFile saves("save.txt");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
                                   //start loading saves
    if(saves.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int farmWork = 0, farmHouse = 0, stabWork = 0, stabHouse = 0, markWork = 0, markHouse = 0, mineWork = 0, mineHouse = 0;
        int farmPriceH = 0, stablePriceH = 0, marketPriceH = 0, minePriceH = 0;
        int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;
        QString readCashStr = saves.readLine();
        QString readWorkStr = saves.readLine();
        QString readWorkHouseStr = saves.readLine();
        QString readPriceHouseStr = saves.readLine();
        tempCash = readCashStr.toInt();
        farmWork = readWorkStr.toInt();
        farmHouse = readWorkHouseStr.toInt();
        farmPriceH = readPriceHouseStr.toInt();
        readWorkStr = saves.readLine();
        readWorkHouseStr = saves.readLine();
        readPriceHouseStr = saves.readLine();
        stabWork = readWorkStr.toInt();
        stabHouse = readWorkHouseStr.toInt();
        stablePriceH = readPriceHouseStr.toInt(); 
        readWorkStr = saves.readLine();
        readWorkHouseStr = saves.readLine();
        readPriceHouseStr = saves.readLine();
        mineWork = readWorkStr.toInt();
        mineHouse = readWorkHouseStr.toInt();
        minePriceH = readPriceHouseStr.toInt();
        readWorkStr = saves.readLine();
        readWorkHouseStr = saves.readLine();
        readPriceHouseStr = saves.readLine();
        markWork = readWorkStr.toInt();
        markHouse = readWorkHouseStr.toInt();
        marketPriceH = readPriceHouseStr.toInt();
        farm.setWorkers(farmWork);
        farm.setWorkersHouse(farmHouse);
        farm.setPriceWorkersHouse(farmPriceH);
        stable.setWorkers(stabWork);
        stable.setWorkersHouse(stabHouse);
        stable.setPriceWorkersHouse(stablePriceH);
        mine.setWorkers(mineWork);
        mine.setWorkersHouse(mineHouse);
        mine.setPriceWorkersHouse(minePriceH);
        market.setWorkers(markWork);
        market.setWorkersHouse(markHouse);
        market.setPriceWorkersHouse(marketPriceH);

        QString lastTime = saves.readLine();
        year = lastTime.toInt();
        lastTime = saves.readLine();
        month = lastTime.toInt();
        lastTime = saves.readLine();
        day = lastTime.toInt();
        lastTime = saves.readLine();
        hour = lastTime.toInt();
        lastTime = saves.readLine();
        minute = lastTime.toInt();
        lastTime = saves.readLine();
        second = lastTime.toInt();

        calc_Time_Absence(year, month, day, hour, minute, second);

        qDebug() << "Cash is loaded from save";
        show_Cash();
        show_All_Price();
        set_need_Workers();

        saves.close();
    }                              //end loading saves

    nMapTown = new mapTown();
    ui->gridLayout_mapTown->addWidget(nMapTown);


    QTimer *timerCalcCash = new QTimer(this);
    QTimer *timerShowCash = new QTimer(this);
    QTimer *timerShowAllPrice = new QTimer(this);

    connect(timerCalcCash, SIGNAL(timeout()), this, SLOT(calculate_Cash()));
    connect(timerShowCash, SIGNAL(timeout()), this, SLOT(show_Cash()));
    connect(timerShowAllPrice, SIGNAL(timeout()), this, SLOT(show_All_Price()));

    timerCalcCash->start(1000);

    timerShowCash->start(500);
    timerShowAllPrice->start(500);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *eventClose)
{                                                       //start saving
    if(saves.open(QIODevice::WriteOnly | QIODevice::Text))
    {
    QString saveCashStr, saveWorkersStr, saveWorkHouseStr, savePriceHouseStr;
    int saveCash = tempCash, saveWork = farm.getWorkrers(), saveWHouse = farm.getWorkrersHouse(), savePriceH = farm.getPriceWorkersHouse();

    QString timeNow;
    QDate nowDate(QDate::currentDate());
    QTime nowTime(QTime::currentTime());

    saveCashStr = QString::number(saveCash);
    saveWorkersStr = QString::number(saveWork);
    saveWorkHouseStr = QString::number(saveWHouse);
    savePriceHouseStr = QString::number(savePriceH);

    QTextStream writeStream(&saves);
    writeStream << saveCashStr << endl;
    writeStream << saveWorkersStr << endl;
    writeStream << saveWorkHouseStr << endl;
    writeStream << savePriceHouseStr << endl;

    saveWork = stable.getWorkrers();
    saveWHouse = stable.getWorkrersHouse();
    savePriceH = stable.getPriceWorkersHouse();
    saveWorkersStr = QString::number(saveWork);
    saveWorkHouseStr = QString::number(saveWHouse);
    savePriceHouseStr = QString::number(savePriceH);
    writeStream << saveWorkersStr << endl;
    writeStream << saveWorkHouseStr << endl;
    writeStream << savePriceHouseStr << endl;

    saveWork = mine.getWorkrers();
    saveWHouse = mine.getWorkrersHouse();
    savePriceH = mine.getPriceWorkersHouse();
    saveWorkersStr = QString::number(saveWork);
    saveWorkHouseStr = QString::number(saveWHouse);
    savePriceHouseStr = QString::number(savePriceH);
    writeStream << saveWorkersStr << endl;
    writeStream << saveWorkHouseStr << endl;
    writeStream << savePriceHouseStr << endl;

    saveWork = market.getWorkrers();
    saveWHouse = market.getWorkrersHouse();
    savePriceH = market.getPriceWorkersHouse();
    saveWorkersStr = QString::number(saveWork);
    saveWorkHouseStr = QString::number(saveWHouse);
    savePriceHouseStr = QString::number(savePriceH);
    writeStream << saveWorkersStr << endl;
    writeStream << saveWorkHouseStr << endl;
    writeStream << savePriceHouseStr << endl;

    timeNow = nowDate.toString("yyyy");
    writeStream << timeNow << endl;
    timeNow = nowDate.toString("M");
    writeStream << timeNow << endl;
    timeNow = nowDate.toString("d");
    writeStream << timeNow << endl;

    timeNow = nowTime.toString("H");
    writeStream << timeNow << endl;
    timeNow = nowTime.toString("m");
    writeStream << timeNow << endl;
    timeNow = nowTime.toString("s");
    writeStream << timeNow << endl;

    saves.close();

    eventClose->accept();
    }
    else                                                //end saving
        eventClose->ignore();

}

void MainWindow::calc_Time_Absence(int lyea, int lmon, int lday, int lhou, int lmin, int lsec)
{
    QDateTime current(QDateTime::currentDateTime());
    QDate lastDate(lyea, lmon, lday);
    QTime lastTime(lhou, lmin, lsec);
    QDateTime last(lastDate, lastTime);
    qint64 diff = 0;

    if(current > last)
    {
       diff = last.secsTo(current);
       calc_Cash_Absence(diff);

    }
    else if(current == last)
    {
        diff = 0;
        calc_Cash_Absence(diff);
    }
    else
        qDebug() << "Time loading error";

}

void MainWindow::calc_Cash_Absence(qint64 difTime)
{
    int rateCashInSec = 0;

    rateCashInSec = farm.calculateCash() + stable.calculateCash() + market.calculateCash() + mine.calculateCash();
    rateCashInSec*= difTime;
    tempCash+= rateCashInSec;

     qDebug() << "Difference time is " << difTime;
     qDebug() << "Difference cash is " << rateCashInSec;

}

void MainWindow::calculate_Cash()
{
    int cashInSec = 0;

    cashInSec = farm.calculateCash() + stable.calculateCash() + market.calculateCash() + mine.calculateCash();
    tempCash+= cashInSec;

}

void MainWindow::show_Cash()
{
    ui->label_cash->setText(QString::number(tempCash));
}

void MainWindow::show_All_Price()
{
    show_Price_Farm();
    show_Price_Stable();
    show_Price_Market();
    show_Price_Mine();
}

void MainWindow::set_need_Workers()         //функция предупреждает и нейтрализует баг №1.0
{
    if (farm.getWorkrersHouse() > 0)
    {
        farm.setNeedWorkers(qPow(10, farm.getWorkrersHouse()));
        qDebug() << "Workers nedeed: " << farm.getNeedWorkrers();
    }
    else
        farm.setNeedWorkers(0);

    if (stable.getWorkrersHouse() > 0)
    {
        stable.setNeedWorkers(qPow(10, stable.getWorkrersHouse()));
        qDebug() << "Workers nedeed: " << stable.getNeedWorkrers();
    }
    else
        stable.setNeedWorkers(0);

    if (market.getWorkrersHouse() > 0)
    {
        market.setNeedWorkers(qPow(10, market.getWorkrersHouse()));
        qDebug() << "Workers nedeed: " << market.getNeedWorkrers();
    }
    else
        market.setNeedWorkers(0);

    if (mine.getWorkrersHouse() > 0)
    {
        mine.setNeedWorkers(qPow(10, mine.getWorkrersHouse()));
        qDebug() << "Workers nedeed: " << mine.getNeedWorkrers();
    }
    else
        mine.setNeedWorkers(0);

}

void MainWindow::change_data_scene_map_Town()
{
    countAvailableMarketeer+= 1;

    nMapTown->change_available_icn_marketeer(countAvailableMarketeer);
}

//========================================farm=========================================================

void MainWindow::on_pushButton_fermers_clicked()
{
    if ((farm.getWorkrersHouse() > 0) && (tempCash >= farm.getPriceWorkers()))
    {
        QString farmersToShow;
        int farms = 0;

        farms = farm.getWorkrers() + 1;
        farm.setWorkers(farms);

        tempCash-= farm.getPriceWorkers();
        show_Price_Farm();
        show_Cash();

    }
}

void MainWindow::on_pushButton_fermersHouse_clicked()
{
    if ((farm.getWorkrers() >= farm.getNeedWorkrers()) && (tempCash >= farm.getPriceWorkersHouse()))
    {
        QString farmersHouseToShow;

        farm.setWorkersHouse(farm.getWorkrersHouse() + 1);

        tempCash-= farm.getPriceWorkersHouse();

        farm.setNeedWorkers(qPow(10, farm.getWorkrersHouse()));
        farm.calculatingPriceHouse();
        show_Price_Farm();
        show_Cash();

    }
}

void MainWindow::show_Price_Farm()
{
    ui->label_farmers->setText(QString::number(farm.getWorkrers()));
    ui->label_farmersHouse->setText(QString::number(farm.getWorkrersHouse()));
    ui->pushButton_fermers->setText(QString("Hire: $") + QString::number(farm.getPriceWorkers()));
    ui->pushButton_fermers_MAX->setText(QString("$") + QString::number((farm.getNeedWorkrers() - farm.getWorkrers()) * farm.getPriceWorkers()));
    ui->pushButton_fermersHouse->setText(QString("Buy: $") + QString::number(farm.getPriceWorkersHouse()));
}

void MainWindow::on_pushButton_fermers_MAX_clicked()
{
    if ((farm.getWorkrersHouse() > 0) &&
            ((farm.getNeedWorkrers() - farm.getWorkrers()) * farm.getPriceWorkers() <= tempCash))
    {
        farm.setWorkers(farm.getNeedWorkrers());
        tempCash-= (farm.getNeedWorkrers() - farm.getWorkrers()) * farm.getPriceWorkers();
        show_Price_Farm();
        show_Cash();
    }
}

//=======================================stable==========================================================

void MainWindow::on_pushButton_horseman_clicked()
{
    if ((stable.getWorkrersHouse() > 0) && (tempCash >= stable.getPriceWorkers()))
    {
        QString stablesWorkersToShow;
        int stablesWorkers = 0;

        stablesWorkers = stable.getWorkrers() + 1;
        stable.setWorkers(stablesWorkers);

        tempCash-= stable.getPriceWorkers();
        show_Price_Stable();
        show_Cash();

    }
}

void MainWindow::on_pushButton_stables_clicked()
{
    if ((stable.getWorkrers() >= stable.getNeedWorkrers()) && (tempCash >= stable.getPriceWorkersHouse()))
    {
        QString stablesToShow;
        int stables = 0;

        stables = stable.getWorkrersHouse() + 1;
        stable.setWorkersHouse(stables);

        tempCash-= stable.getPriceWorkersHouse();

        stable.setNeedWorkers(qPow(10, stable.getWorkrersHouse()));
        stable.calculatingPriceHouse();
        show_Price_Stable();
        show_Cash();

    }
}

void MainWindow::show_Price_Stable()
{
    //QString horsPB = ui->pushButton_horseman->text();
    //QString horsPB = QString("Hire: $") + QString::number(stable.getPriceWorkers());
    //ui->pushButton_horseman->setText(QString::number(stable.getPriceWorkers()));

    ui->label_horseman->setText(QString::number(stable.getWorkrers()));
    ui->label_stables->setText(QString::number(stable.getWorkrersHouse()));
    ui->pushButton_horseman->setText(QString("Hire: $") + QString::number(stable.getPriceWorkers()));
    ui->pushButton_horseman_MAX->setText(QString("$") + QString::number((stable.getNeedWorkrers() - stable.getWorkrers()) * stable.getPriceWorkers()));
    ui->pushButton_stables->setText(QString("Buy: $") + QString::number(stable.getPriceWorkersHouse()));
}

void MainWindow::on_pushButton_horseman_MAX_clicked()
{
    if ((stable.getWorkrersHouse() > 0) &&
            ((stable.getNeedWorkrers() - stable.getWorkrers()) * stable.getPriceWorkers() <= tempCash))
    {
        stable.setWorkers(stable.getNeedWorkrers());
        tempCash-= (stable.getNeedWorkrers() - stable.getWorkrers()) * stable.getPriceWorkers();
        show_Price_Stable();
        show_Cash();
    }
}

//=========================================mine==========================================================

void MainWindow::on_pushButton_mine_clicked()
{
    if ((mine.getWorkrers() >= mine.getNeedWorkrers()) && (tempCash >= mine.getPriceWorkersHouse()))
    {
        QString mineToShow;
        int mines = 0;

        mines = mine.getWorkrersHouse() + 1;
        mine.setWorkersHouse(mines);

        tempCash-= mine.getPriceWorkersHouse();

        mine.setNeedWorkers(qPow(10, mine.getWorkrersHouse()));
        mine.calculatingPriceHouse();
        show_Price_Mine();
        show_Cash();
    }
}

void MainWindow::on_pushButton_miner_clicked()
{
    if ((mine.getWorkrersHouse() > 0) && (tempCash >= mine.getPriceWorkers()))
    {
        QString mineWorkersToShow;
        int miner = 0;

        miner = mine.getWorkrers() + 1;
        mine.setWorkers(miner);

        tempCash-= mine.getPriceWorkers();
        show_Price_Mine();
        show_Cash();
    }
}

void MainWindow::show_Price_Mine()
{
    ui->label_miner->setText(QString::number(mine.getWorkrers()));
    ui->label_mine->setText(QString::number(mine.getWorkrersHouse()));
    ui->pushButton_miner->setText(QString("Hire: $") + QString::number(mine.getPriceWorkers()));
    ui->pushButton_miner_MAX->setText(QString("$") + QString::number((mine.getNeedWorkrers() - mine.getWorkrers()) * mine.getPriceWorkers()));
    ui->pushButton_mine->setText(QString("Buy: $") + QString::number(mine.getPriceWorkersHouse()));
}

void MainWindow::on_pushButton_miner_MAX_clicked()
{
    if ((mine.getWorkrersHouse() > 0) &&
            ((mine.getNeedWorkrers() - mine.getWorkrers()) * mine.getPriceWorkers() <= tempCash))
    {
        mine.setWorkers(mine.getNeedWorkrers());
        tempCash-= (mine.getNeedWorkrers() - mine.getWorkrers()) * mine.getPriceWorkers();
        show_Price_Market();
        show_Cash();
    }
}

//========================================market=========================================================

void MainWindow::on_pushButton_marketeer_clicked()
{
    if ((market.getWorkrersHouse() > 0) && (tempCash >= market.getPriceWorkers()))
    {
        QString marketWorkersToShow;
        int marketeer = 0;

        marketeer = market.getWorkrers() + 1;
        market.setWorkers(marketeer);

        tempCash-= market.getPriceWorkers();
        show_Price_Mine();
        show_Cash();

    }
}

void MainWindow::on_pushButton_market_clicked()
{
    if ((market.getWorkrers() >= market.getNeedWorkrers()) && (tempCash >= market.getPriceWorkersHouse()))
    {
        QString marketToShow;
        int mart = 0;

        mart = market.getWorkrersHouse() + 1;
        market.setWorkersHouse(mart);

        tempCash-= market.getPriceWorkersHouse();

        market.setNeedWorkers(qPow(10, market.getWorkrersHouse()));
        market.calculatingPriceHouse();
        show_Price_Market();
        show_Cash();
        change_data_scene_map_Town();       //каждый уровень market.getWorkrersHouse() добавляет на вторую вкладку чела, пока их не станет 9. После чего прекращает
    }
}

void MainWindow::show_Price_Market()
{
    ui->label_marketeer->setText(QString::number(market.getWorkrers()));
    ui->label_market->setText(QString::number(market.getWorkrersHouse()));
    ui->pushButton_marketeer->setText(QString("Hire: $") + QString::number(market.getPriceWorkers()));
    ui->pushButton_marketeer_MAX->setText(QString("$") + QString::number((market.getNeedWorkrers() - market.getWorkrers()) * market.getPriceWorkers()));
    ui->pushButton_market->setText(QString("Buy: $") + QString::number(market.getPriceWorkersHouse()));
}

void MainWindow::on_pushButton_marketeer_MAX_clicked()
{
    if ((market.getWorkrersHouse() > 0) &&
            ((market.getNeedWorkrers() - market.getWorkrers()) * market.getPriceWorkers() <= tempCash))
    {
        market.setWorkers(market.getNeedWorkrers());
        tempCash-= (market.getNeedWorkrers() - market.getWorkrers()) * market.getPriceWorkers();
        show_Price_Market();
        show_Cash();
    }
}

//=======================================================================================================

void MainWindow::on_pushButton_addMarketeer_clicked()
{
    change_data_scene_map_Town();
    ui->pushButton_addMarketeer->setText(QString::number(countAvailableMarketeer));
}

void MainWindow::on_pushButton_change_ectt_clicked()
{
    nMapTown->change_ectt_mt();
}

