#ifndef HEESSYSTEMSCENE_H
#define HEESSYSTEMSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "heesgraphicsitem.h"

class HEESSystemScene : public QGraphicsScene
{
    Q_OBJECT
    enum Mode{ADD_ARROW, DEFAULT};

public:
    explicit HEESSystemScene(QObject *parent = 0);
    void setAddArrowMode();

signals:
    void portSelected(HEESGraphicsItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
     Mode myMode;
};

#endif // HEESSYSTEMSCENE_H
