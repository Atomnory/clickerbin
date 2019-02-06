#ifndef MAPTOWN_H
#define MAPTOWN_H

#include <QObject>
//#include <QPointF>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>
#include "common.h"
#include "iconmaptown.h"
#include "townfield.h"
#include "dragdropinfo.h"

class mapTown : public QGraphicsView
{
    Q_OBJECT
public:
    mapTown();

    void change_available_icn_marketeer(int);
    void init_icon();
    void show_all_items();

    void change_ectt_mt();

    int check_ectt(int);
    void set_ectt(int, int);
    void change_pastAvailable(int);
    int get_Bonus(int);

private:
    bool is_moving_on_field(const QPointF&);

    void move_from_space_to_field(QPointF);

private slots:
    void icn_market_pressed(int );
    void icn_market_released(int );

private:
    const int CountMark = 9;
    int availableMarketeer = 0;
    int pastAvailableMarketeer = 0;

    int y = 50; // coordinate for spawn icon

    QGraphicsScene *mScene;
    townField nField;
    iconMapTown *marketIcon = new iconMapTown[CountMark];

};

#endif // MAPTOWN_H
