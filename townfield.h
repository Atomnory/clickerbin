#ifndef TOWNFIELD_H
#define TOWNFIELD_H

#include <QGraphicsItem>
#include <QVector>
#include <QPixmap>
#include "common.h"

class townField : public QGraphicsItem
{
public:
    townField(/*int nLines, int nColumns, int nCellWidth*/);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *) override;

    void hoverMoveEvent(QGraphicsSceneHoverEvent *) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override;

    bool cellIsEmpty(const QPointF&);
    eCellTownType getCellType(const QPointF&);

    void takeCell(QPointF);
    void set_field(QPointF);

    void init_cells();
    void init_pix_cell();
    void draw_cells(QPainter *);

    void set_size_cell(int, int, int);

    void boundingRectOnSceneCalculate();
    qreal topLeftX();
    qreal topLeftY();
    qreal bottomRightX();
    qreal bottomRightY();

    void change_ecttTF();

    void update_field();

    QPointF get_field_posPressEvent();

signals:
    void fieldMousePressEvent();

private:
    int index_calculating(QPointF);
    QPointF position_calculating(int);

protected:
    int fLines{0};
    int fColumns{0};
    int fCellWidth{0};
    int fHeight{0};
    int fWidth{0};
    const int FNine{9};
    bool fHover{false};

    const int FSpacer{1};

    int pixWidth{0};
    int pixHeight{0};

    QPointF fMousePos;
    QRectF fBoundingSceneRect;
    QPixmap hometown, hometownActive, farm, farmActive, market, marketActive;
    QPixmap cell, cellActive, mine, mineActive, stable, stableActive;
    QPointF posPressEvent;

    eCellTownType *ecttCell = new eCellTownType[FNine];
    QVector<eCellInfo> ediCell;

};

#endif // TOWNFIELD_H
