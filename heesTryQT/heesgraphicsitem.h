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
    ~HEESGraphicsItem();

    DerivedAttributes * myAttributes();
    ItemType myType();

    void setLeftItem(HEESGraphicsItem *item);
    void setRightItem(HEESGraphicsItem *item);
    void addConverter(HEESGraphicsItem *converter);
    void removeConverter(HEESGraphicsItem *converter);
    void portItemRemoved(HEESGraphicsItem *item);
    void updateArrowLocation();
    QString getPortAName();
    QString getPortBName();
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

public:
    QString name;
    QString derivedType;

private:
    ItemType type;
    DerivedAttributes attributes;

    HEESGraphicsItem *portAItem;
    HEESGraphicsItem *portBItem;

    ArrowItem *leftArrow;
    ArrowItem *rightArrow;
    QList<HEESGraphicsItem*> connectedConverters;
    bool willBeRemoved;
};

#endif // HEESGRAPHICSITEM_H
