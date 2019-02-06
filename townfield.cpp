#include "townfield.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QDebug>
#include <QFile>
#include <QCloseEvent>

static QFile saves("saveCell.txt");

townField::townField(/*int nLines, int nColumns, int nCellWidth*/)
//                    : fLines(nLines), fColumns(nColumns), fCellWidth(nCellWidth)
//                    , fHeight(nLines * nCellWidth), fWidth(nColumns * nCellWidth)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::MouseButton::LeftButton);

    ediCell.resize(FNine + 1);
    init_cells();
    init_pix_cell();
}

/*void townField::closeEvent(QCloseEvent *eventCloseTF)         //start saving
{
    if(saves.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream writeStream(&saves);

        for(int i = 1; i <= FNine; i++)
        {
            QString cttcellLoad;
            cttcellLoad = (ecttCell[i] == eCellTownType::EMPTY) ? 0 : 1;
            writeStream << cttcellLoad << endl;
        }

        saves.close();
        eventCloseTF->accept();
    }
    else
        eventCloseTF->ignore();
} */                                                          //end saving

int townField::checkECTTCell(int ind)
{
    int retInt = -1;
    if (ecttCell[ind] == eCellTownType::EMPTY)
        retInt = 0;
    else
        retInt = 1;
        return retInt;
}

void townField::set_ECTT_from_load(int index, int value)
{
    if (value == 0)
        ecttCell[index] =  eCellTownType::EMPTY;
    else
        ecttCell[index] =  eCellTownType::FULL;
}

QRectF townField::boundingRect() const
{
    return QRectF(0, 0, fWidth, fHeight);
}

void townField::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for(int l = 0; l <= fLines; l++)
    {
        painter->setPen(QColor(105,105,105));
        painter->drawLine(QLineF(0, l * fCellWidth, fWidth, l * fCellWidth));
    }

    for(int c = 0; c <= fColumns; c++)
    {
        painter->setPen(QColor(105,105,105));
        painter->drawLine(QLineF(c * fCellWidth, 0, c * fCellWidth, fHeight));
    }
    ediCell.resize(fLines * fColumns + 1);

//    init_cells();
    draw_cells(painter);

    if(fHover)
    {
        int x = fMousePos.x() / fCellWidth;
        int y = fMousePos.y() / fCellWidth;

        painter->setPen(QColor(30, 190, 235));
        painter->drawRect(x * fCellWidth, y * fCellWidth, fCellWidth, fCellWidth);
    }

}

void townField::mousePressEvent(QGraphicsSceneMouseEvent *aEvent)
{
    update();
}

void townField::hoverMoveEvent(QGraphicsSceneHoverEvent *apEvent)
{
    fMousePos = apEvent->pos();
    fHover = true;
    QGraphicsItem::update();
}

void townField::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    fHover = false;
    QGraphicsItem::update();
}

bool townField::cellIsEmpty(const QPointF &aPos)
{
    return getCellType(aPos) == eCellTownType::EMPTY;
}

eCellTownType townField::getCellType(const QPointF &bPos)
{
    QPointF pos = mapFromScene(bPos);
    int index = index_calculating(pos);
    return ecttCell[index];
}

void townField::takeCell(QPointF aPos)
{
    QPointF pos = mapFromScene(aPos);
    int index = index_calculating(pos);

    ecttCell[index] = eCellTownType::EMPTY;
}

void townField::set_field(QPointF aPos)
{
    QPointF pos = mapFromScene(aPos);
    int index = index_calculating(pos);

    ecttCell[index] = eCellTownType::FULL;
}

void townField::init_cells()
{
    for(int i = 0; i <= FNine; i++)
      ecttCell[i] = eCellTownType::EMPTY;

    ediCell[0] = eCellInfo::Unknown;
    ediCell[1] = eCellInfo::CELL_1;
    ediCell[2] = eCellInfo::CELL_2;
    ediCell[3] = eCellInfo::CELL_3;
    ediCell[4] = eCellInfo::CELL_4;
    ediCell[5] = eCellInfo::CELL_5;
    ediCell[6] = eCellInfo::CELL_6;
    ediCell[7] = eCellInfo::CELL_7;
    ediCell[8] = eCellInfo::CELL_8;
    ediCell[9] = eCellInfo::CELL_9;
}

void townField::init_pix_cell()
{

    cellActive.load(":/icon/pics/manActive.jpg");
    hometown.load(":/icon/pics/hometown.jpg");
    hometownActive.load(":/icon/pics/hometownActive2.jpg");
    farm.load(":/icon/pics/farm.jpg");
    farmActive.load(":/icon/pics/farmActive3.jpg");
    market.load(":/icon/pics/market.jpg");
    marketActive.load(":/icon/pics/marketActive2.jpg");
    mine.load(":/icon/pics/mine2.jpg");
    mineActive.load(":/icon/pics/mineActive.jpg");
    stable.load(":/icon/pics/stable.jpg");
    stableActive.load(":/icon/pics/stableActive.jpg");
}

void townField::draw_cells(QPainter *painter)       // рисует картинки/текст в ячейке
{
    if(ediCell.size() == 0)
        return;

    for(int i = 0; i <= fLines * fColumns; i++)
    {
        switch (ediCell[i])
        {
            case eCellInfo::Unknown:
            {
                break;
            }
            case eCellInfo::CELL_1:
            {
                QPointF cellPos = position_calculating(i);
                int x = cellPos.x();
                int y = cellPos.y();

                if(ecttCell[i] == eCellTownType::EMPTY)
                {
                    pixWidth = farm.width();
                    pixHeight = farm.height();
                    painter->drawPixmap(x + FSpacer, y + FSpacer, pixWidth, pixHeight, farm);
                    bonusCell[i] = 1;
                }

                else if(ecttCell[i] == eCellTownType::FULL)
                {
                    pixWidth = farmActive.width();
                    pixHeight = farmActive.height();
                    painter->drawPixmap(x + FSpacer, y + FSpacer, pixWidth, pixHeight, farmActive);
                    bonusCell[i] = 5;
                }
                break;
            }
            case eCellInfo::CELL_2:
            {
                QPointF cellPos = position_calculating(i);
                int x = cellPos.x();
                int y = cellPos.y();

                if(ecttCell[i] == eCellTownType::EMPTY)
                {
                    pixWidth = stable.width();
                    pixHeight = stable.height();
                    painter->drawPixmap(x + FSpacer, y + FSpacer, pixWidth, pixHeight, stable);
                    bonusCell[i] = 1;
                }

                else if(ecttCell[i] == eCellTownType::FULL)
                {
                    pixWidth = stableActive.width();
                    pixHeight = stableActive.height();
                    painter->drawPixmap(x + FSpacer, y + FSpacer, pixWidth, pixHeight, stableActive);
                    bonusCell[i] = 2;
                }
                break;
            }

            case eCellInfo::CELL_3:
            {
                QPointF cellPos = position_calculating(i);
                int x = cellPos.x();
                int y = cellPos.y();

                if(ecttCell[i] == eCellTownType::EMPTY)
                {
                    pixWidth = market.width();
                    pixHeight = market.height();
                    painter->drawPixmap(x + FSpacer, y + FSpacer, pixWidth, pixHeight, market);
                    bonusCell[i] = 1;
                }

                else if(ecttCell[i] == eCellTownType::FULL)
                {
                    pixWidth = marketActive.width();
                    pixHeight = marketActive.height();
                    painter->drawPixmap(x + FSpacer, y + FSpacer, pixWidth, pixHeight, marketActive);
                    bonusCell[i] = 5;
                }
                break;
            }

            case eCellInfo::CELL_4:
            {
                QPointF cellPos = position_calculating(i);
                int x = cellPos.x();
                int y = cellPos.y();

                if(ecttCell[i] == eCellTownType::EMPTY)
                {
                    pixWidth = market.width();
                    pixHeight = market.height();
                    painter->drawPixmap(x + FSpacer, y + FSpacer, pixWidth, pixHeight, market);
                    bonusCell[i] = 1;
                }

                else if(ecttCell[i] == eCellTownType::FULL)
                {
                    pixWidth = marketActive.width();
                    pixHeight = marketActive.height();
                    painter->drawPixmap(x + FSpacer, y + FSpacer, pixWidth, pixHeight, marketActive);
                    bonusCell[i] = 2;
                }
                break;
            }

            case eCellInfo::CELL_5:
            {
                QPointF cellPos = position_calculating(i);
                int x = cellPos.x();
                int y = cellPos.y();

                if(ecttCell[i] == eCellTownType::EMPTY)
                {
                    pixWidth = hometown.width();
                    pixHeight = hometown.height();
                    painter->drawPixmap(x + FSpacer, y + FSpacer, pixWidth, pixHeight, hometown);
                    bonusCell[i] = 1;
                }

                else if(ecttCell[i] == eCellTownType::FULL)
                {
                    pixWidth = hometownActive.width();
                    pixHeight = hometownActive.height();
                    painter->drawPixmap(x + FSpacer, y + FSpacer, pixWidth, pixHeight, hometownActive);
                    bonusCell[i] = 10;
                }
                break;
            }

            case eCellInfo::CELL_6:
            {
                QPointF cellPos = position_calculating(i);
                int x = cellPos.x();
                int y = cellPos.y();

                if(ecttCell[i] == eCellTownType::EMPTY)
                {
                    pixWidth = stable.width();
                    pixHeight = stable.height();
                    painter->drawPixmap(x + FSpacer, y + FSpacer, pixWidth, pixHeight, stable);
                    bonusCell[i] = 1;
                }

                else if(ecttCell[i] == eCellTownType::FULL)
                {
                    pixWidth = stableActive.width();
                    pixHeight = stableActive.height();
                    painter->drawPixmap(x + FSpacer, y + FSpacer, pixWidth, pixHeight, stableActive);
                    bonusCell[i] = 5;
                }
                break;
            }

            case eCellInfo::CELL_7:
            {
                QPointF cellPos = position_calculating(i);
                int x = cellPos.x();
                int y = cellPos.y();

                if(ecttCell[i] == eCellTownType::EMPTY)
                {
                    pixWidth = mine.width();
                    pixHeight = mine.height();
                    painter->drawPixmap(x + FSpacer, y + FSpacer, pixWidth, pixHeight, mine);
                    bonusCell[i] = 1;
                }

                else if(ecttCell[i] == eCellTownType::FULL)
                {
                    pixWidth = mineActive.width();
                    pixHeight = mineActive.height();
                    painter->drawPixmap(x + FSpacer, y + FSpacer, pixWidth, pixHeight, mineActive);
                    bonusCell[i] = 5;
                }
                break;
            }

            case eCellInfo::CELL_8:
            {
                QPointF cellPos = position_calculating(i);
                int x = cellPos.x();
                int y = cellPos.y();

                if(ecttCell[i] == eCellTownType::EMPTY)
                {
                    pixWidth = farm.width();
                    pixHeight = farm.height();
                    painter->drawPixmap(x + FSpacer, y + FSpacer, pixWidth, pixHeight, farm);
                    bonusCell[i] = 1;
                }

                else if(ecttCell[i] == eCellTownType::FULL)
                {
                    pixWidth = farmActive.width();
                    pixHeight = farmActive.height();
                    painter->drawPixmap(x + FSpacer, y + FSpacer, pixWidth, pixHeight, farmActive);
                    bonusCell[i] = 2;
                }
                break;
            }

            case eCellInfo::CELL_9:
            {
                QPointF cellPos = position_calculating(i);
                int x = cellPos.x();
                int y = cellPos.y();

                if(ecttCell[i] == eCellTownType::EMPTY)
                {
                    pixWidth = mine.width();
                    pixHeight = mine.height();
                    painter->drawPixmap(x + FSpacer, y + FSpacer, pixWidth, pixHeight, mine);
                    bonusCell[i] = 1;
                }

                else if(ecttCell[i] == eCellTownType::FULL)
                {
                    pixWidth = mineActive.width();
                    pixHeight = mineActive.height();
                    painter->drawPixmap(x + FSpacer, y + FSpacer, pixWidth, pixHeight, mineActive);
                    bonusCell[i] = 2;
                }
                break;
            }
        }
    }
}

void townField::set_size_cell(int Line, int Column, int CellW)
{
    fLines = Line;
    fColumns = Column;
    fCellWidth = CellW;
    fWidth = fColumns * fCellWidth;
    fHeight = fLines * fCellWidth;
}

void townField::boundingRectOnSceneCalculate()
{
    QPointF position = scenePos();
    QRectF rectangle = boundingRect();

    QPointF topLeft{position.x() + rectangle.x(), position.x() + rectangle.x()};
    QPointF bottomRight{topLeft.x() + rectangle.width(), topLeft.y() + rectangle.height()};

    fBoundingSceneRect.setTopLeft(topLeft);
    fBoundingSceneRect.setBottomRight(bottomRight);
}

qreal townField::topLeftX()
{
    return fBoundingSceneRect.topLeft().x();
}

qreal townField::topLeftY()
{
    return fBoundingSceneRect.topLeft().y();
}

qreal townField::bottomRightX()
{
    return fBoundingSceneRect.bottomRight().x();
}

qreal townField::bottomRightY()
{
    return fBoundingSceneRect.bottomRight().y();
}

void townField::change_ecttTF()
{
    ecttCell[5] = eCellTownType::EMPTY;
    QGraphicsItem::update();
}

int townField::index_calculating(QPointF pos)
{
    int index = 0;
    int column = pos.x() / fCellWidth;
    int line = pos.y() / fCellWidth;

    if(line < fLines && column < fColumns)
    {
        column++;
        index = line * fColumns + column;
        return index;
    }

    return 0;
}

QPointF townField::position_calculating(int index)
{
    QPointF pos;
    qreal cellWidth = fCellWidth;
    int line = 0, column = 0;

    if(index == 1 || index == 4 || index == 7)
    {
        column = 1;
        if(index - column == 0)
            line = 0;
        else
            line = (index - column) / fLines;
         column--;
         pos.setX(column * cellWidth);
         pos.setY(line * cellWidth);
    }
    else if(index == 2 || index == 5 || index == 8)
    {
        column = 2;
        if(index - column == 0)
            line = 0;
        else
            line = (index - column) / fLines;
         column--;
         pos.setX(column * cellWidth);
         pos.setY(line * cellWidth);
    }
    else if(index == 3 || index == 6 || index == 9)
    {
        column = 3;
        if(index - column == 0)
            line = 0;
        else
            line = (index - column) / fLines;
         column--;
         pos.setX(column * cellWidth);
         pos.setY(line * cellWidth);
    }

    return pos;
}

void townField::update_field()
{
    update();
}

QPointF townField::get_field_posPressEvent()
{
    return posPressEvent;
}

int townField::getBonus(int index)
{
    int retBonus = bonusCell[index];
    return retBonus;
}
