#include "heessystemscene.h"

HEESSystemScene::HEESSystemScene(QObject *parent)
    : QGraphicsScene(parent)
{
    myMode = DEFAULT;
}

void HEESSystemScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
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
