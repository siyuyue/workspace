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
