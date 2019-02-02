#include "maptown.h"
#include <QGraphicsSceneMouseEvent>
#include <QSpacerItem>

mapTown::mapTown()
{
    setRenderHint(QPainter::Antialiasing);
    setCacheMode(QGraphicsView::CacheNone);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setAlignment(Qt::AlignCenter);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFrameStyle(0);

    mScene = new QGraphicsScene();
    setScene(mScene);
    setSceneRect(0 , 0 , 750, 420);

    nField.set_size_cell(3, 3, 102);
    nField.boundingRectOnSceneCalculate();
    mScene->addItem(&nField);

    qDebug() << nField.topLeftX() << " - " << nField.topLeftY() << endl
             << nField.bottomRightX() << " - " << nField.bottomRightY() << endl;

}

void mapTown::change_available_icn_marketeer(int nMarketeer)
{
    if(nMarketeer <= CountMark)
    {
        pastAvailableMarketeer = availableMarketeer;
        availableMarketeer = nMarketeer;
        init_icon();
        y+= 20;
    }
    else
        return;

}

void mapTown::init_icon()
{
    for(int i = pastAvailableMarketeer, x = 450; i < availableMarketeer ; i++)
    {
        marketIcon[i].setPos(x, y);
        marketIcon[i].setImage(":/icon/pics/man.jpg");
        connect(&marketIcon[i], &iconMapTown::icnMousePressEvent, [this, i]{mapTown::icn_market_pressed(i); });
        connect(&marketIcon[i], &iconMapTown::icnMouseReleaseEvent, [this, i]{mapTown::icn_market_released(i); });

        mScene->addItem(&marketIcon[i]);
        marketIcon[i].show();
    }
}

void mapTown::show_all_items()
{
    nField.show();

    for(int i = 0; i < availableMarketeer ; i++)
    {
        marketIcon[i].show();
    }
}

bool mapTown::is_moving_on_field(const QPointF &bPos)
{
    return (bPos.x() >= nField.topLeftX()) && (bPos.y() >= nField.topLeftY())
        && (bPos.x() <= nField.bottomRightX()) && (bPos.y() <= nField.bottomRightY());
}

void mapTown::icn_market_pressed(int i)
{
    const QPointF &pos = marketIcon[i].get_posPressEvent();
    dragDropInfo &ddi = dragDropInfo::instance();

    ddi.pull({pos});
}

void mapTown::icn_market_released(int i)
{
    const QPointF &pos = marketIcon[i].get_posReleaseEvent();
    dragDropInfo &ddi = dragDropInfo::instance();

    if(is_moving_on_field(pos) && nField.cellIsEmpty(pos))
    {
        qDebug() << "move from space to field";
        move_from_space_to_field(pos);
        marketIcon[i].hide();
    }

    ddi.reset();
//    QGraphicsScene::mouseReleaseEvent();
}

void mapTown::change_ectt_mt()
{
    nField.change_ecttTF();
}

void mapTown::move_from_space_to_field(QPointF aPos)
{
    nField.set_field(aPos);
    nField.update_field();
}
