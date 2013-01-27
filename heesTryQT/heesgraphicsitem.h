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

class HEESGraphicsItem : public QGraphicsPolygonItem
{
public:
    HEESGraphicsItem(int t);

    DerivedAttributes * myAttributes();
    QString getName();
    QString getDerivedType();
    void setName( QString str );
    void setDerivedType( QString str );
    ItemType myType();

private:
    ItemType type;

    DerivedAttributes attributes;
    QString name;
    QString derivedType;

    ArrowItem *leftArrow;
    ArrowItem *rightArrow;
};

#endif // HEESGRAPHICSITEM_H
