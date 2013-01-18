#include "mainwindow.h"
#include "derivedattributes.h"
#include "ui_mainwindow.h"
#include "heesgraphicsitem.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    scene = new QGraphicsScene;
    ui->setupUi(this);
    ui->compTypeBox->addItem(tr("Source"));
    ui->compTypeBox->addItem(tr("Bank"));
    ui->compTypeBox->addItem(tr("Load"));
    ui->compTypeBox->addItem(tr("CTI"));
    ui->compTypeBox->addItem(tr("Converter"));
    ui->compTypeBox->setCurrentIndex(0);

    ui->compAttributeBox->setDisabled(true);

    ui->graphicsView->setScene( scene );

    QObject::connect(scene, SIGNAL(selectionChanged()), this, SLOT(selectionChangedInScene()) );
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

void MainWindow::on_addButton_clicked()
{
    scene->addItem( new HEESGraphicsItem(ui->compTypeBox->currentIndex()) );
}

void MainWindow::selectionChangedInScene()
{
    QList<QGraphicsItem *> itemList = scene->selectedItems();
    if( itemList.empty() )
    {
        ui->compAttributeBox->setEnabled(false);
        ui->attributeTableView->setModel(NULL);
    }
    else if( itemList.size() > 1 )
    {
        scene->clearSelection();
        ui->compAttributeBox->setEnabled(false);
        ui->attributeTableView->setModel(NULL);
    }
    else
    {
        ui->compAttributeBox->setEnabled(true);
        ui->attributeTableView->setModel( static_cast<HEESGraphicsItem*>(itemList[0])->MyAttributes() );
    }
}
