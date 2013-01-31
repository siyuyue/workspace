#include "heesitemwidget.h"

HEESItemWidget::HEESItemWidget(QWidget *parent) :
    QWidget(parent)
{
    typeLabel = new QLabel(QString("Type:"), parent);
    typeNameLabel = new QLabel(parent);

    nameLabel = new QLabel(QString("Name:"), parent);
    nameEdit = new QLineEdit(parent);

    portALabel = new QLabel(QString("Converter Port A"), parent);
    portANameLabel = new QLabel(parent);
    selectPortAButton = new QPushButton(QString("Select"),parent);

    portBLabel = new QLabel(QString("Converter Port B"), parent);
    portBNameLabel = new QLabel(parent);
    selectPortBButton = new QPushButton(QString("Select"),parent);

    derivedLabel = new QLabel("Derived Type:", parent);
    derivedEdit = new QLineEdit(parent);
    attributeTableView = new QTableView(parent);
    removeButton = new QPushButton(QString("Remove Component"),parent);

    QHBoxLayout *hLayout1 = new QHBoxLayout;
    hLayout1->addWidget(typeLabel);
    hLayout1->addWidget(typeNameLabel);

    QHBoxLayout *hLayout2 = new QHBoxLayout;
    hLayout2->addWidget(nameLabel);
    hLayout2->addWidget(nameEdit);

    QHBoxLayout *hLayout3 = new QHBoxLayout;
    hLayout3->addWidget(portALabel);
    hLayout3->addWidget(portANameLabel, 1);
    hLayout3->addWidget(selectPortAButton);

    QHBoxLayout *hLayout4 = new QHBoxLayout;
    hLayout4->addWidget(portBLabel);
    hLayout4->addWidget(portBNameLabel, 1);
    hLayout4->addWidget(selectPortBButton);

    QHBoxLayout *hLayout5 =  new QHBoxLayout;
    hLayout5->addWidget(derivedLabel);
    hLayout5->addWidget(derivedEdit);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);
    vLayout->addLayout(hLayout3);
    vLayout->addLayout(hLayout4);
    vLayout->addLayout(hLayout5);
    vLayout->addWidget(attributeTableView, 1);
    vLayout->addWidget(removeButton);

    QGridLayout *layout = new QGridLayout;
    layout->addLayout(vLayout, 0, 0);

    setLayout(layout);

    setModel(NULL);

    connect(nameEdit, SIGNAL(editingFinished()), this, SLOT(nameEditFinished()));
    connect(derivedEdit, SIGNAL(editingFinished()), this, SLOT(derivedEditFinished()));
    connect(selectPortAButton, SIGNAL(clicked()), this, SLOT(selectAClicked()));
    connect(selectPortBButton, SIGNAL(clicked()), this, SLOT(selectBClicked()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeClicked()));
}

void HEESItemWidget::setModel(HEESGraphicsItem *modelItem)
{
    item = modelItem;
    if( item == NULL)
    {
        setEnabled(false);
        typeNameLabel->clear();
        nameEdit->clear();
        portANameLabel->clear();
        portBNameLabel->clear();
        derivedEdit->clear();
        attributeTableView->setModel(NULL);
    }
    else
    {
        setEnabled(true);
        selectPortAButton->setEnabled(false);
        selectPortBButton->setEnabled(false);

        switch( item->myType() )
        {
        case SOURCE:
            typeNameLabel->setText(QString("Source"));
            break;
        case BANK:
            typeNameLabel->setText(QString("Bank"));
            break;
        case LOAD:
            typeNameLabel->setText(QString("Load"));
            break;
        case CTI:
            typeNameLabel->setText(QString("CTI"));
            break;
        case CONVERTER:
            typeNameLabel->setText(QString("Converter"));
            selectPortAButton->setEnabled(true);
            selectPortBButton->setEnabled(true);
            portANameLabel->setText(item->getPortAName());
            portBNameLabel->setText(item->getPortBName());
            break;
        }

        nameEdit->setText(item->name);
        derivedEdit->setText(item->derivedType);
        attributeTableView->setModel(item->myAttributes());
    }
}

void HEESItemWidget::nameEditFinished()
{
    item->name = nameEdit->text();
}

void HEESItemWidget::derivedEditFinished()
{
    item->derivedType = derivedEdit->text();
}

void HEESItemWidget::selectAClicked()
{
    isPortA = true;
    emit selectPort();
}

void HEESItemWidget::selectBClicked()
{
    isPortA = false;
    emit selectPort();
}

void HEESItemWidget::removeClicked()
{
    emit removeItem(item);
}

void HEESItemWidget::portSelectedFromScene(HEESGraphicsItem *port)
{
    if( port == NULL || port->myType() == CONVERTER )
        return;
    if( isPortA )
    {
        item->setLeftItem(port);
        portANameLabel->setText(item->getPortAName());
    }
    else
    {
        item->setRightItem(port);
        portBNameLabel->setText(item->getPortBName());
    }
}
