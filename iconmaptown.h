#ifndef ICONMAPTOWN_H
#define ICONMAPTOWN_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsScene>
#include <QPointF>

class iconMapTown : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    iconMapTown();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override;

    void setGeometry(int, int);
    void setImage(QString);

    QPointF get_posPressEvent();
    QPointF get_posReleaseEvent();

signals:
    void icnMousePressEvent();
    void icnMouseMoveEvent();
    void icnMouseReleaseEvent();

private:
    int icnWidth{0};
    int icnHeight{0};

    bool icnIsMoving{true};
    bool icnHover{false};

    QPixmap icnPixMap;
    QPointF posPressEvent, posReleaseEvent;
};

#endif // ICONMAPTOWN_H
