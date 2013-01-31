#include "heesgraphicsitem.h"

HEESGraphicsItem::HEESGraphicsItem(int t)
{
    leftArrow = NULL;
    rightArrow = NULL;
    portAItem = NULL;
    portBItem = NULL;

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
        leftArrow = new ArrowItem(true, this);
        rightArrow = new ArrowItem(false, this);
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

    QBrush brush(QColor(255,255,255));
    setBrush(brush);
    setPolygon(myPolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    setPos(qrand() % 200 - 100, qrand() % 200 - 100);

    // Make other components stay on top of the converter and arrows
    if( type != CONVERTER)
        setZValue(1);

    willBeRemoved = false;
}

HEESGraphicsItem::~HEESGraphicsItem()
{
    willBeRemoved = true;
    for(int i=0;i<connectedConverters.size();i++)
    {
        connectedConverters[i]->portItemRemoved(this);
        connectedConverters[i]->updateArrowLocation();
    }
}

DerivedAttributes * HEESGraphicsItem::myAttributes()
{
    return &attributes;
}

ItemType HEESGraphicsItem::myType()
{
    return type;
}

void HEESGraphicsItem::setLeftItem(HEESGraphicsItem *item)
{
    portAItem = item;
    leftArrow->setEndItem(item);
}

void HEESGraphicsItem::setRightItem(HEESGraphicsItem *item)
{
    portBItem = item;
    rightArrow->setEndItem(item);
}

void HEESGraphicsItem::addConverter(HEESGraphicsItem *converter)
{
    connectedConverters.push_back(converter);
}

void HEESGraphicsItem::removeConverter(HEESGraphicsItem *converter)
{
    if(!willBeRemoved)
        connectedConverters.removeOne(converter);
}

void HEESGraphicsItem::portItemRemoved(HEESGraphicsItem *item)
{
    if(item == portAItem)
    {
        portAItem = NULL;
        leftArrow->setEndItem(NULL);
    }
    if(item == portBItem)
    {
        portBItem = NULL;
        rightArrow->setEndItem(NULL);
    }
}

void HEESGraphicsItem::updateArrowLocation()
{
    if(leftArrow)
        leftArrow->updatePosition();
    if(rightArrow)
        rightArrow->updatePosition();
}

QString HEESGraphicsItem::getPortAName()
{
    if(portAItem)
        return portAItem->name;
    return QString();
}

QString HEESGraphicsItem::getPortBName()
{
    if(portBItem)
        return portBItem->name;
    return QString();
}

QVariant HEESGraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange)
    {
        if(leftArrow)
            leftArrow->updatePosition();
        if(rightArrow)
            rightArrow->updatePosition();
        for(int i=0;i<connectedConverters.size();i++)
            connectedConverters[i]->updateArrowLocation();
    }

    return value;
}
