#include "WebBrowserWidget.h"
#include "ui_WebBrowserWidget.h"
#include "WidgetSelector.h"

CWebBrowserWidget::CWebBrowserWidget(QWidget *parent) :
    CWidgetBase(parent),
    ui(new Ui::CWebBrowserWidget)
{
    setObjectName("Web Browser");
    ui->setupUi(this);
}

CWebBrowserWidget::~CWebBrowserWidget()
{
    delete ui;
}

void CWebBrowserWidget::on_btnGo_clicked()
{
    ui->webView->setUrl(ui->editURL->text());
}

void CWebBrowserWidget::on_btnClose_clicked()
{
    ui->webView->setUrl(QString("about::blank"));
    pSelector->ShowSelectionScreen();
}
