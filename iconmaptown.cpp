#include "iconmaptown.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "maptown.h"

iconMapTown::iconMapTown()
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
}

QRectF iconMapTown::boundingRect() const
{
    return QRectF(0, 0, icnWidth, icnHeight);
}

void iconMapTown::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(icnHover)
        painter->setPen(QColor(225, 0, 70));

    painter->drawRoundRect(0, 0, icnWidth, icnHeight, 2, 2);
    painter->drawPixmap(0, 0, icnWidth, icnHeight, icnPixMap);

}

void iconMapTown::mousePressEvent(QGraphicsSceneMouseEvent *aEvent)
{
    posPressEvent = aEvent->scenePos();
    icnIsMoving = false;

    emit icnMousePressEvent();
    QGraphicsItem::update();
}

void iconMapTown::mouseMoveEvent(QGraphicsSceneMouseEvent *apEvent)
{
    QPointF newPos = mapToScene(apEvent->pos()/* - icnStartMovePos*/);

    if((newPos.x() < 0) || (newPos.y() < 0))
        return;
    if((newPos.x() > 750) || (newPos.y() > 420))
        return;

    icnIsMoving = true;
    this->setPos(newPos);

    emit icnMouseMoveEvent();
    update();
}

void iconMapTown::mouseReleaseEvent(QGraphicsSceneMouseEvent *aEvent)
{
    posReleaseEvent = aEvent->scenePos();
    emit icnMouseReleaseEvent();
    update();
}

void iconMapTown::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    icnHover = true;
    QGraphicsItem::update();
}

void iconMapTown::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    icnHover = false;
    QGraphicsItem::update();
}

void iconMapTown::setGeometry(int nWidth, int nHeight)
{
    icnWidth = nWidth;
    icnHeight = nHeight;
}

void iconMapTown::setImage(QString nPath)
{
    icnPixMap.load(nPath);
    icnWidth = icnPixMap.width();
    icnHeight = icnPixMap.height();
}

QPointF iconMapTown::get_posPressEvent()
{
    return posPressEvent;
}

QPointF iconMapTown::get_posReleaseEvent()
{
    return posReleaseEvent;
}
