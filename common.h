#ifndef COMMON_H
#define COMMON_H

#include <QPointF>

enum class eCellTownType
{
    EMPTY
   ,FULL
};

enum class eCellInfo
{
    Unknown
    ,CELL_1
    ,CELL_2
    ,CELL_3
    ,CELL_4
    ,CELL_5
    ,CELL_6
    ,CELL_7
    ,CELL_8
    ,CELL_9
};

struct strctDragData
{
  eCellTownType type;
  QPointF drag_pos;
};

struct strctDDOnlyPos
{
    QPointF drag_pos;
};


#endif // COMMON_H
