#ifndef ARROWITEM_H
#define ARROWITEM_H

#include "heesgraphicsitem.h"
#include <QGraphicsLineItem>

class ArrowItem : public QGraphicsLineItem
{
    Q_OBJECT
public:
    explicit ArrowItem(HEESGraphicsItem *startItemP, HEESGraphicsItem *endItemP, bool isLeftPort = true, QObject *parent = 0);
    
signals:
    
public slots:
    
private:
    HEESGraphicsItem *startItem;
    HEESGraphicsItem *endItem;
    qreal startOffsetX;
    qreal startOffsetY;
    qreal endOffsetX;
    qreal endOffsetY;
};

#endif // ARROWITEM_H
