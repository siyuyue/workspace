#ifndef HEESGRAPHICSITEM_H
#define HEESGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QString>
#include "derivedattributes.h"
#include "arrowitem.h"

enum ItemType{
    SOURCE, BANK, LOAD, CTI, CONVERTER
};

class ArrowItem;

class HEESGraphicsItem : public QGraphicsPolygonItem
{
public:
    HEESGraphicsItem(int t);

    DerivedAttributes * myAttributes();
    ItemType myType();

public:
    QString name;
    QString derivedType;
    QString portAName;
    QString portBName;

private:
    ItemType type;
    DerivedAttributes attributes;
    ArrowItem *leftArrow;
    ArrowItem *rightArrow;
};

#endif // HEESGRAPHICSITEM_H
