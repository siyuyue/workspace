#include "mainwindow.h"
#include "derivedattributes.h"
#include "ui_mainwindow.h"
#include "heesgraphicsitem.h"

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

void MainWindow::on_deleteButton_clicked()
{
    ui->compAttributeBox->setEnabled(false);
    ui->attributeTableView->setModel(NULL);
    ui->typeNameLabel->clear();
    ui->nameEdit->clear();
    ui->derivedEdit->clear();

    QGraphicsItem *item = scene->selectedItems()[0];
    scene->removeItem(item);
    scene->clearSelection();

    delete item;
}

void MainWindow::selectionChangedInScene()
{
    QList<QGraphicsItem *> itemList = scene->selectedItems();
    if( itemList.empty() )
    {
        ui->compAttributeBox->setEnabled(false);
        ui->attributeTableView->setModel(NULL);
        ui->typeNameLabel->clear();
        ui->nameEdit->clear();
        ui->derivedEdit->clear();
    }
    else if( itemList.size() > 1 )
    {
        scene->clearSelection();
        ui->compAttributeBox->setEnabled(false);
        ui->attributeTableView->setModel(NULL);
        ui->typeNameLabel->clear();
        ui->nameEdit->clear();
        ui->derivedEdit->clear();
    }
    else
    {
        ui->compAttributeBox->setEnabled(true);
        HEESGraphicsItem *selectedItem = static_cast<HEESGraphicsItem*>(itemList[0]);
        ui->attributeTableView->setModel( selectedItem->myAttributes() );
        ui->typeNameLabel->setText( ui->compTypeBox->itemText( selectedItem->myType() ) );
        ui->nameEdit->setText( selectedItem->name );
        ui->derivedEdit->setText( selectedItem->derivedType );

        if( selectedItem->myType() == CONVERTER )
        {
            ui->selectPortAButton->setEnabled(true);
            ui->selectPortBButton->setEnabled(true);

            ui->portANameLabel->setText( selectedItem->portAName );
            ui->portBNameLabel->setText( selectedItem->portBName );
        }
        else
        {
            ui->selectPortAButton->setEnabled(false);
            ui->selectPortBButton->setEnabled(false);
        }
    }
}

void MainWindow::on_nameEdit_editingFinished()
{
    QList<QGraphicsItem *> itemList = scene->selectedItems();
    static_cast<HEESGraphicsItem*>(itemList[0])->name = ui->nameEdit->text();
}

void MainWindow::on_derivedEdit_editingFinished()
{
    QList<QGraphicsItem *> itemList = scene->selectedItems();
    static_cast<HEESGraphicsItem*>(itemList[0])->derivedType = ui->derivedEdit->text();
}

void MainWindow::on_selectPortAButton_clicked()
{
    scene->setAddArrowMode();
    ui->statusBar->showMessage( QString("Choose Port A.") );
}

void MainWindow::on_selectPortBButton_clicked()
{
    scene->setAddArrowMode();
}
