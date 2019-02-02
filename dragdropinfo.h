#ifndef DRAGDROPINFO_H
#define DRAGDROPINFO_H

#include "common.h"

class dragDropInfo
{
    dragDropInfo();
    ~dragDropInfo();

public:
    static dragDropInfo &instance();

    bool cellIsEmpty();

    void pull(strctDragData);
    void reset();

    void pull(strctDDOnlyPos);

    strctDragData pop();
    strctDragData object() const;

private:
    strctDragData ObjectInfo{eCellTownType::EMPTY, {0,0}};
    strctDDOnlyPos ObjectPos{{0,0}};
};

#endif // DRAGDROPINFO_H
