#include "RadioWidget.h"
#include "ui_RadioWidget.h"

CRadioWidget::CRadioWidget(QWidget *parent):
    CWidgetBase(parent),
    ui(new Ui::CRadioWidget)
{
    ui->setupUi(this);

    //-F- Setting up table
    ui->stationsList->setColumnWidth(1,55);
    ui->stationsList->horizontalHeader()->setResizeMode(0,QHeaderView::Stretch);
}

CRadioWidget::~CRadioWidget()
{
    delete ui;
}
