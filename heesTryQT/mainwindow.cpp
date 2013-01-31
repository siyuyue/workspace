#include "mainwindow.h"
#include "derivedattributes.h"
#include "ui_mainwindow.h"
#include "heesgraphicsitem.h"
#include "heesitemwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    scene = new HEESSystemScene;
    ui->setupUi(this);
    ui->compTypeBox->addItem(QString("Source"));
    ui->compTypeBox->addItem(QString("Bank"));
    ui->compTypeBox->addItem(QString("Load"));
    ui->compTypeBox->addItem(QString("CTI"));
    ui->compTypeBox->addItem(QString("Converter"));
    ui->compTypeBox->setCurrentIndex(0);

    ui->graphicsView->setScene( scene );

    connect(scene, SIGNAL(selectionChanged()), this, SLOT(selectionChangedInScene()) );
    connect(ui->widget, SIGNAL(selectPort()), this, SLOT(selectPortInScene()) );
    connect(scene, SIGNAL(portSelected(HEESGraphicsItem*)), ui->widget, SLOT(portSelectedFromScene(HEESGraphicsItem*)));
    connect(ui->widget, SIGNAL(removeItem(HEESGraphicsItem*)), this, SLOT(removeItemInScene(HEESGraphicsItem*)));
}

MainWindow::~MainWindow()
{
    QList<QGraphicsItem *> itemList = scene->items();
    for( int i=0; i<itemList.size(); i++ )
        delete itemList[i];
    delete ui;
    delete scene;
}

void MainWindow::selectionChangedInScene()
{
    QList<QGraphicsItem *> itemList = scene->selectedItems();
    if( itemList.empty() )
    {
        ui->widget->setModel(NULL);
    }
    else
    {
        ui->widget->setModel(static_cast<HEESGraphicsItem*>(itemList[0]));
    }
}

void MainWindow::removeItemInScene(HEESGraphicsItem* item)
{
    scene->removeItem(item);
    delete item;
}

void MainWindow::selectPortInScene()
{
    scene->setAddArrowMode();
}

void MainWindow::on_addButton_clicked()
{
    scene->addItem( new HEESGraphicsItem(ui->compTypeBox->currentIndex()) );
}
