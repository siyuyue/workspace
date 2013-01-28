#ifndef ARROWITEM_H
#define ARROWITEM_H

#include "heesgraphicsitem.h"
#include <QGraphicsLineItem>

class HEESGraphicsItem;

class ArrowItem : public QGraphicsLineItem
{
public:
    explicit ArrowItem(HEESGraphicsItem *startItemP, HEESGraphicsItem *endItemP, bool isLeftPort = true, QObject *parent = 0);    

private:
    HEESGraphicsItem *startItem;
    HEESGraphicsItem *endItem;
    qreal startOffsetX;
    qreal startOffsetY;
    qreal endOffsetX;
    qreal endOffsetY;
};

#endif // ARROWITEM_H
