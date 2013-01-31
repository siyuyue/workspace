#include "heessystemscene.h"

HEESSystemScene::HEESSystemScene(QObject *parent)
    : QGraphicsScene(parent)
{
    myMode = DEFAULT;
}

void HEESSystemScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if( myMode == ADD_ARROW )
    {
        if( mouseEvent->button() != Qt::MouseButton::LeftButton )
        {
            emit portSelected( NULL );
            myMode = DEFAULT;
            return;
        }

        QGraphicsItem *item = itemAt(mouseEvent->scenePos(), QTransform());

        if( item != NULL && typeid(*item) == typeid(HEESGraphicsItem) )
        {
            emit portSelected( static_cast<HEESGraphicsItem*>(item) );
            myMode = DEFAULT;
        }
    }
    else
    {
        QGraphicsScene::mousePressEvent(mouseEvent);
    }
}

void HEESSystemScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    return;
}

void HEESSystemScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void HEESSystemScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void HEESSystemScene::setAddArrowMode()
{
    myMode = ADD_ARROW;
}
