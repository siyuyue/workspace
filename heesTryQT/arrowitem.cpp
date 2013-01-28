#include "arrowitem.h"

ArrowItem::ArrowItem(HEESGraphicsItem *startItem, HEESGraphicsItem *endItem, bool isLeftPort, QObject *parent):
    QGraphicsLineItem(parent)
{
    startItem = startItemP;
    endItem = endItemP;
    if( isLeftPort )
    {
        startOffsetX = -15;
        startOffsetY = 15;
    }
    else
    {
        startOffsetX = 15;
        startOffsetY = 15;
    }

    switch( endItem->myType() )
    {
    case SOURCE:
        endOffsetX = 0;
        endOffsetY = 0;
        break;
    case BANK:
        endOffsetX = 0;
        endOffsetY = 0;
        break;
    case LOAD:
        endOffsetX = 0;
        endOffsetY = 0;
        break;
    case CTI:
        endOffsetX = 0;
        endOffsetY = 0;
        break;
    }

    QLineF line( mapFromItem(startItem, startOffsetX, startOffsetY), mapFromItem(endItem, endOffsetX, endOffsetY) );
    setline(line);
}