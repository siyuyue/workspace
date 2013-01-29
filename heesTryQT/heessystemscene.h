#ifndef HEESSYSTEMSCENE_H
#define HEESSYSTEMSCENE_H

#include <QGraphicsScene>

class HEESSystemScene : public QGraphicsScene
{
    Q_OBJECT
    enum Mode{ADD_ARROW, DEFAULT};

public:
    explicit HEESSystemScene(QObject *parent = 0);
    void setAddArrowMode();

protected:
     void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
     void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
     void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
     Mode myMode;
};

#endif // HEESSYSTEMSCENE_H
