#include "farmingslot.h"
#include <QtMath>

FarmingSlot::FarmingSlot(int priceW, int priceWH, int increaseCHM)
{
    priceWorkers = priceW;
    priceWorkersHouse = priceWH;
    increaseCashHouseMult = increaseCHM;
}

void FarmingSlot::setWorkers (int worke)
{
    workers = worke;
}

int FarmingSlot::getWorkrers ()
{
    return workers;
}

void FarmingSlot::setWorkersHouse (int workeHouse)
{
    workersHouse = workeHouse;
}

int FarmingSlot::getWorkrersHouse ()
{
    return workersHouse;
}

int FarmingSlot::getPriceWorkers()
{
    return priceWorkers;
}

int FarmingSlot::getPriceWorkersHouse()
{
    return priceWorkersHouse;
}

void FarmingSlot::setPriceWorkersHouse (int newPrice)
{
    priceWorkersHouse = newPrice;
}

void FarmingSlot::setNeedWorkers (int nessecary)
{
    needWorkers = nessecary;
}

int FarmingSlot::getNeedWorkrers ()
{
    return needWorkers;
}


void FarmingSlot::calculatingPriceHouse()
{
    priceWorkersHouse*= multPriceWorkersHouse;
}

int FarmingSlot::calculateCash()
{
    int tempCashInSec = 0;

    if (workersHouse > 0)
    {
        tempCashInSec = workers * (qPow(increaseCashHouseMult, workersHouse - 1));
    }
    else
        tempCashInSec = 0;

    return  tempCashInSec;
}
