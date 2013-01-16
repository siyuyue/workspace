#include "heesgraphicsitem.h"

HEESGraphicsItem::HEESGraphicsItem(int t)
{
    width = 20;
    height = 20;
    xPos = qrand() % 200 - 100;
    yPos = qrand() % 200 - 100;
    type = ItemType(t);

    setFlags( QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
}

QRectF HEESGraphicsItem::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(xPos - penWidth/2, yPos - penWidth/2, width + penWidth, height + penWidth);
}

void HEESGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(QRectF(xPos, yPos, width, height));
}
