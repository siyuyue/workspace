#include "heesitemwidget.h"

HEESItemWidget::HEESItemWidget(QWidget *parent) :
    QWidget(parent)
{
    item = NULL;

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
    deleteButton = new QPushButton(QString("Remove Component"),parent);

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
    vLayout->addWidget(deleteButton);

    groupBox = new QGroupBox;

    QGridLayout *layout = new QGridLayout;
    layout->addLayout(vLayout, 0, 0);

    setLayout(layout);
}

void HEESItemWidget::setModel(HEESGraphicsItem *modelItem)
{
    item = modelItem;
}
