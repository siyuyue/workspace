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
    ui->compTypeBox->addItem(QString("Source"));
    ui->compTypeBox->addItem(QString("Bank"));
    ui->compTypeBox->addItem(QString("Load"));
    ui->compTypeBox->addItem(QString("CTI"));
    ui->compTypeBox->addItem(QString("Converter"));
    ui->compTypeBox->setCurrentIndex(0);

    ui->compAttributeBox->setDisabled(true);

    ui->graphicsView->setScene( scene );

    QObject::connect(scene, SIGNAL(selectionChanged()), this, SLOT(selectionChangedInScene()) );
}

MainWindow::~MainWindow()
{
    QList<QGraphicsItem *> itemList = scene->items();
    for( int i=0; i<itemList.size(); i++ )
        delete itemList[i];
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
        ui->nameEdit->clear();
        ui->derivedEdit->clear();
    }
    else if( itemList.size() > 1 )
    {
        scene->clearSelection();
        ui->compAttributeBox->setEnabled(false);
        ui->attributeTableView->setModel(NULL);
        ui->nameEdit->clear();
        ui->derivedEdit->clear();
    }
    else
    {
        ui->compAttributeBox->setEnabled(true);
        ui->attributeTableView->setModel( static_cast<HEESGraphicsItem*>(itemList[0])->myAttributes() );
        ui->nameEdit->setText( static_cast<HEESGraphicsItem*>(itemList[0])->getName() );
        ui->derivedEdit->setText( static_cast<HEESGraphicsItem*>(itemList[0])->getDerivedType() );
    }
}

void MainWindow::on_nameEdit_editingFinished()
{
    QList<QGraphicsItem *> itemList = scene->selectedItems();
    static_cast<HEESGraphicsItem*>(itemList[0])->setName( ui->nameEdit->text() );
}

void MainWindow::on_derivedEdit_editingFinished()
{
    QList<QGraphicsItem *> itemList = scene->selectedItems();
    static_cast<HEESGraphicsItem*>(itemList[0])->setDerivedType( ui->derivedEdit->text() );
}
