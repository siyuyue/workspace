#include "arrowitem.h"

ArrowItem::ArrowItem(HEESGraphicsItem *startItemP, HEESGraphicsItem *endItemP, bool isLeftPort, QGraphicsItem *parent):
    QGraphicsLineItem(parent)
{
    startItem = startItemP;
    endItem = endItemP;
    if( isLeftPort )
    {
        startOffsetX = -30;
        startOffsetY = 15;
    }
    else
    {
        startOffsetX = 0;
        startOffsetY = 15;
    }

    switch( endItem->myType() )
    {
    case SOURCE:
        endOffsetX = -25;
        endOffsetY = 0;
        break;
    case BANK:
        endOffsetX = -20;
        endOffsetY = 20;
        break;
    case LOAD:
        endOffsetX = -20;
        endOffsetY = 20;
        break;
    case CTI:
        endOffsetX = 0;
        endOffsetY = 40;
        break;
    }

    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsSelectable, false);

    QLineF line( mapFromItem(startItem, startOffsetX, startOffsetY), mapFromItem(endItem, endOffsetX, endOffsetY) );
    setLine(line);
}

void ArrowItem::updatePosition()
{
    QLineF line( mapFromItem(startItem, startOffsetX, startOffsetY), mapFromItem(endItem, endOffsetX, endOffsetY) );
    setLine(line);
}
