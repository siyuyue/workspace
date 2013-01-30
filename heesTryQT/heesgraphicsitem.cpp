#include "heesgraphicsitem.h"

HEESGraphicsItem::HEESGraphicsItem(int t)
{
    qreal xPos = 0;
    qreal yPos = 0;
    type = ItemType(t);

    type = ItemType(t);
    QPainterPath path;
    QPolygonF myPolygon;
    switch (type) {
    case SOURCE:
        path.moveTo(xPos, yPos);
        path.arcTo(xPos - 50, yPos - 25, 50, 50, 0, 360);
        myPolygon = path.toFillPolygon();
        break;
    case BANK:
        path.moveTo(xPos, yPos);
        path.arcTo(xPos - 39, yPos - 10, 40, 20, 0, 360);
        path.lineTo(xPos, yPos + 40);
        path.arcTo(xPos - 39, yPos + 40, 40, 20, 0, -180);
        path.lineTo(xPos - 39, yPos);
        path.arcTo(xPos - 39, yPos - 10, 40, 20, 180, 180);
        myPolygon = path.toFillPolygon();
        break;
    case LOAD:
        path.moveTo(xPos, yPos);
        path.lineTo(xPos, yPos + 50);
        path.lineTo(xPos - 36, yPos + 50);
        path.lineTo(xPos - 36, yPos);
        myPolygon = path.toFillPolygon();
        break;
    case CTI:
        path.moveTo(xPos, yPos);
        path.lineTo(xPos + 20, yPos + 20);
        path.lineTo(xPos + 10, yPos + 20);
        path.lineTo(xPos + 10, yPos + 120);
        path.lineTo(xPos + 20, yPos + 120);
        path.lineTo(xPos, yPos + 140);
        path.lineTo(xPos - 20, yPos + 120);
        path.lineTo(xPos - 10, yPos + 120);
        path.lineTo(xPos - 10, yPos + 20);
        path.lineTo(xPos - 20, yPos + 20);
        myPolygon = path.toFillPolygon();
        break;
    case CONVERTER:
        path.moveTo(xPos, yPos);
        path.lineTo(xPos + 5, yPos + 5);
        path.lineTo(xPos + 5, yPos + 25);
        path.lineTo(xPos, yPos + 30);
        path.lineTo(xPos - 30, yPos + 30);
        path.lineTo(xPos - 35, yPos + 25);
        path.lineTo(xPos - 35, yPos + 5);
        path.lineTo(xPos - 30, yPos);
        myPolygon = path.toFillPolygon();
    break;
    }

    setPolygon(myPolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    setPos(qrand() % 200 - 100, qrand() % 200 - 100);

    leftArrow = NULL;
    rightArrow = NULL;
}

DerivedAttributes * HEESGraphicsItem::myAttributes()
{
    return &attributes;
}

ItemType HEESGraphicsItem::myType()
{
    return type;
}
