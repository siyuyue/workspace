#ifndef HEESITEMWIDGET_H
#define HEESITEMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include "heesgraphicsitem.h"

class HEESItemWidget : public QWidget
{
    Q_OBJECT
    
public:
    HEESItemWidget(QWidget *parent = 0);
    void setModel( HEESGraphicsItem *modelItem );

signals:
    void selectPort();

public slots:
    void portSelectedFromScene(HEESGraphicsItem *port);

private slots:
    void nameEditFinished();
    void derivedEditFinished();
    void selectAClicked();
    void selectBClicked();

private:
    QLabel *typeLabel;
    QLabel *typeNameLabel;

    QLabel *nameLabel;
    QLineEdit *nameEdit;

    QLabel *portALabel;
    QLabel *portANameLabel;
    QPushButton *selectPortAButton;

    QLabel *portBLabel;
    QLabel *portBNameLabel;
    QPushButton *selectPortBButton;

    QLabel *derivedLabel;
    QLineEdit *derivedEdit;
    QTableView *attributeTableView;
    QPushButton *deleteButton;

    HEESGraphicsItem *item;

    bool isPortA;
};

#endif
