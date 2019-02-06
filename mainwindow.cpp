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
static FarmingSlot townhall(10000, 1000000, 5);
static FarmingSlot market(100000, 10000000, 6);
static QFile saves("save.txt");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    nMapTown = new mapTown();
    ui->gridLayout_mapTown->addWidget(nMapTown);

                                   //start loading saves
    if(saves.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;
        QString readCashStr = saves.readLine(), readCoAvMaStr = saves.readLine();

        tempCash = readCashStr.toUInt();
        countAvailableMarket = readCoAvMaStr.toInt();
        nMapTown->change_pastAvailable(countAvailableMarket);

        QString readWorkStr = saves.readLine();
        QString readWorkHouseStr = saves.readLine();
        QString readPriceHouseStr = saves.readLine();

        farm.setWorkers(readWorkStr.toInt());
        farm.setWorkersHouse(readWorkHouseStr.toInt());
        farm.setPriceWorkersHouse(readPriceHouseStr.toInt());


        readWorkStr = saves.readLine();
        readWorkHouseStr = saves.readLine();
        readPriceHouseStr = saves.readLine();
        stable.setWorkers(readWorkStr.toInt());
        stable.setWorkersHouse(readWorkHouseStr.toInt());
        stable.setPriceWorkersHouse(readPriceHouseStr.toInt());

        readWorkStr = saves.readLine();
        readWorkHouseStr = saves.readLine();
        readPriceHouseStr = saves.readLine();
        mine.setWorkers(readWorkStr.toInt());
        mine.setWorkersHouse(readWorkHouseStr.toInt());
        mine.setPriceWorkersHouse(readPriceHouseStr.toInt());

        readWorkStr = saves.readLine();
        readWorkHouseStr = saves.readLine();
        readPriceHouseStr = saves.readLine();
        townhall.setWorkers(readWorkStr.toInt());
        townhall.setWorkersHouse(readWorkHouseStr.toInt());
        townhall.setPriceWorkersHouse(readPriceHouseStr.toInt());

        readWorkStr = saves.readLine();
        readWorkHouseStr = saves.readLine();
        readPriceHouseStr = saves.readLine();
        market.setWorkers(readWorkStr.toInt());
        market.setWorkersHouse(readWorkHouseStr.toInt());
        market.setPriceWorkersHouse(readPriceHouseStr.toInt());

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

        QString readTownTypeCell= saves.readLine();

        for(int i = 1; i <= 9; i++)
        {
            if(readTownTypeCell.toInt() == 0)
                nMapTown->set_ectt(i, 0);
            else
                nMapTown->set_ectt(i, 1);

            readTownTypeCell= saves.readLine();
        }

        calc_Time_Absence(year, month, day, hour, minute, second);

        qDebug() << "Cash is loaded from save";
        show_Cash();
        show_All_Price();
        set_need_Workers();

        saves.close();  
    }                              //end loading saves




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
        QDate nowDate(QDate::currentDate());
        QTime nowTime(QTime::currentTime());

        QTextStream writeStream(&saves);
        writeStream << QString::number(tempCash) << endl;
        writeStream << QString::number(countAvailableMarket) << endl;

        writeStream << QString::number(farm.getWorkrers()) << endl;
        writeStream << QString::number(farm.getWorkrersHouse()) << endl;
        writeStream << QString::number(farm.getPriceWorkersHouse()) << endl;

        writeStream << QString::number(stable.getWorkrers()) << endl;
        writeStream << QString::number(stable.getWorkrersHouse()) << endl;
        writeStream << QString::number(stable.getPriceWorkersHouse()) << endl;

        writeStream << QString::number(mine.getWorkrers()) << endl;
        writeStream << QString::number(mine.getWorkrersHouse()) << endl;
        writeStream << QString::number(mine.getPriceWorkersHouse()) << endl;

        writeStream << QString::number(townhall.getWorkrers()) << endl;
        writeStream << QString::number(townhall.getWorkrersHouse()) << endl;
        writeStream << QString::number(townhall.getPriceWorkersHouse()) << endl;

        writeStream << QString::number(market.getWorkrers()) << endl;
        writeStream << QString::number(market.getWorkrersHouse()) << endl;
        writeStream << QString::number(market.getPriceWorkersHouse()) << endl;

        writeStream << nowDate.toString("yyyy") << endl;
        writeStream << nowDate.toString("M") << endl;
        writeStream << nowDate.toString("d") << endl;

        writeStream << nowTime.toString("H") << endl;
        writeStream << nowTime.toString("m") << endl;
        writeStream << nowTime.toString("s") << endl;

        QString cttcellSave;
        for(int i = 1; i <= 9; i++)
        {
            cttcellSave = QString::number(nMapTown->check_ectt(i));
            writeStream << cttcellSave << endl;
        }
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

    rateCashInSec = farm.calculateCash() * nMapTown->get_Bonus(1) + stable.calculateCash() * nMapTown->get_Bonus(6)
            + mine.calculateCash() * nMapTown->get_Bonus(7) + townhall.calculateCash() * nMapTown->get_Bonus(5)
            + market.calculateCash() * nMapTown->get_Bonus(3);
    rateCashInSec*= difTime;
    tempCash+= rateCashInSec;

    qDebug() << "Difference time is " << difTime;
    qDebug() << "Difference cash is " << rateCashInSec;

}

void MainWindow::calculate_Cash()
{
    int cashInSec = 0;

    cashInSec = farm.calculateCash() * nMapTown->get_Bonus(1) + stable.calculateCash() * nMapTown->get_Bonus(6)
            + mine.calculateCash() * nMapTown->get_Bonus(7) + townhall.calculateCash() * nMapTown->get_Bonus(5)
            + market.calculateCash() * nMapTown->get_Bonus(3);
    tempCash+= cashInSec;

    qDebug() << "Farm bonus is " << nMapTown->get_Bonus(1);
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
    show_Price_Townhall();
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
    countAvailableMarket+= 1;

    nMapTown->change_available_icn_marketeer(countAvailableMarket);
}

//========================================farm=========================================================

void MainWindow::on_pushButton_fermers_clicked()
{
    if ((farm.getWorkrersHouse() > 0) && (tempCash >= farm.getPriceWorkers()))
    {
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

//========================================Townhall======================================================

void MainWindow::on_pushButton_mayor_clicked()
{
    if ((townhall.getWorkrersHouse() > 0) && (tempCash >= townhall.getPriceWorkers()))
    {
        int mayor = 0;

        mayor = townhall.getWorkrers() + 1;
        townhall.setWorkers(mayor);

        tempCash-= townhall.getPriceWorkers();
        show_Price_Townhall();
        show_Cash();
    }
}

void MainWindow::on_pushButton_townhall_clicked()
{
    if ((townhall.getWorkrers() >= townhall.getNeedWorkrers()) && (tempCash >= townhall.getPriceWorkersHouse()))
    {
        int town = 0;

        town = townhall.getWorkrersHouse() + 1;
        townhall.setWorkersHouse(town);

        tempCash-= townhall.getPriceWorkersHouse();

        townhall.setNeedWorkers(qPow(10, townhall.getWorkrersHouse()));
        townhall.calculatingPriceHouse();
        show_Price_Townhall();
        show_Cash();
    }
}

void MainWindow::show_Price_Townhall()
{
    ui->label_mayor->setText(QString::number(townhall.getWorkrers()));
    ui->label_townhall->setText(QString::number(townhall.getWorkrersHouse()));
    ui->pushButton_mayor->setText(QString("Hire: $") + QString::number(townhall.getPriceWorkers()));
    ui->pushButton_mayor_MAX->setText(QString("$") + QString::number((townhall.getNeedWorkrers() - townhall.getWorkrers()) * townhall.getPriceWorkers()));
    ui->pushButton_townhall->setText(QString("Buy: $") + QString::number(townhall.getPriceWorkersHouse()));
}

void MainWindow::on_pushButton_mayor_MAX_clicked()
{
    if ((townhall.getWorkrersHouse() > 0) &&
            ((townhall.getNeedWorkrers() - townhall.getWorkrers()) * townhall.getPriceWorkers() <= tempCash))
    {
        townhall.setWorkers(townhall.getNeedWorkrers());
        tempCash-= (townhall.getNeedWorkrers() - townhall.getWorkrers()) * townhall.getPriceWorkers();
        show_Price_Townhall();
        show_Cash();
    }
}

//========================================market=========================================================

void MainWindow::on_pushButton_marketeer_clicked()
{
    if ((market.getWorkrersHouse() > 0) && (tempCash >= market.getPriceWorkers()))
    {
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

void MainWindow::on_pushButton_addMarketeer_clicked()       //test function
{
    change_data_scene_map_Town();
    ui->pushButton_addMarketeer->setText(QString::number(countAvailableMarket));
}

void MainWindow::on_pushButton_change_ectt_clicked()        //test function
{
    nMapTown->change_ectt_mt();
}
