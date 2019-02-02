#include "dragdropinfo.h"

dragDropInfo::dragDropInfo()
{

}

dragDropInfo::~dragDropInfo()
{

}

dragDropInfo &dragDropInfo::instance()
{
    static dragDropInfo res;
    return res;
}

bool dragDropInfo::cellIsEmpty()
{
    return ObjectInfo.type == eCellTownType::EMPTY;
}

void dragDropInfo::pull(strctDragData aInfo)
{
    ObjectInfo = aInfo;
}

void dragDropInfo::pull(strctDDOnlyPos posInfo)
{
    ObjectPos = posInfo;
}

void dragDropInfo::reset()
{
    ObjectInfo.type = eCellTownType::EMPTY;
}

strctDragData dragDropInfo::pop()
{
    strctDragData res = ObjectInfo;
    reset();
    return res;
}

strctDragData dragDropInfo::object() const
{
    return ObjectInfo;
}

