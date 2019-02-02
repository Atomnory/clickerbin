#ifndef FARMINGSLOT_H
#define FARMINGSLOT_H


class FarmingSlot
{
public:
    FarmingSlot(int, int, int);

    void setWorkers (int);
    int getWorkrers();
    void setWorkersHouse (int);
    int getWorkrersHouse();

    int getPriceWorkers();
    int getPriceWorkersHouse();
    void setPriceWorkersHouse (int);

    void setNeedWorkers (int);
    int getNeedWorkrers();

    void calculatingPriceHouse();

    int calculateCash();

private:
    int workers = 0;
    int workersHouse = 0;
    int priceWorkers = 0;
    int priceWorkersHouse = 0;
    int needWorkers = 0;
    double multPriceWorkersHouse = 1.5;
    int increaseCashHouseMult = 0;

};

#endif // FARMINGSLOT_H
