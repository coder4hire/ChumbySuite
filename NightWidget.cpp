#include "NightWidget.h"
#include "ui_NightWidget.h"
#include "HardwareLayer.h"
#include "WidgetSelector.h"

CNightWidget::CNightWidget(QWidget *parent) :
    CWidgetBase(parent),
    ui(new Ui::CNightWidget)
{
    ui->setupUi(this);

    setObjectName("CNightWidget");
    //ui->clockWidget->ShadeColor=0x909050;
    ui->clockWidget->TextColor=0x808080;

    ui->clockWidget->TimeFont.setFamily("Sans Serif");
    ui->clockWidget->TimeFont.setPixelSize(60);
    ui->clockWidget->TimeFont.setItalic(true);
    ui->clockWidget->TimeFont.setBold(true);
}

CNightWidget::~CNightWidget()
{

    delete ui;
}

void CNightWidget::showEvent(QShowEvent *)
{
    CHardwareLayer::GetInstance()->SetBrightness(nightBrightness);
}

void CNightWidget::hideEvent(QHideEvent *)
{
    CHardwareLayer::GetInstance()->SetBrightness(brightness);
}

void CNightWidget::OnSettingsChanged()
{
    brightness=pSelector->GetSettings()->value("General/Brightness",100).toInt();
    nightBrightness=pSelector->GetSettings()->value("General/NightBrightness",2).toInt();
}
