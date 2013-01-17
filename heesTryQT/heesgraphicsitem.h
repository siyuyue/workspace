#ifndef HEESGRAPHICSITEM_H
#define HEESGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include "derivedattributes.h"

enum ItemType{
    SOURCE, BANK, LOAD, CTI, CONVERTER
};

class HEESGraphicsItem : public QGraphicsItem
{
public:
    HEESGraphicsItem(int t);
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    DerivedAttributes * MyAttributes();

private:
    ItemType type;
    qreal xPos;
    qreal yPos;
    qreal width;
    qreal height;

    DerivedAttributes attributes;
};

#endif // HEESGRAPHICSITEM_H
