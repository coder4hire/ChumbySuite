#include "NumericKbd.h"
#include "ui_NumericKbd.h"
#include "QKeyEvent"

CNumericKbd* CNumericKbd::pKeyboard = NULL;

CNumericKbd::CNumericKbd(QWidget *parent) :
    CKbdBase(parent),
    ui(new Ui::CNumericKbd)
{
    ui->setupUi(this);
    pCallerEdit=NULL;
}

CNumericKbd::~CNumericKbd()
{
    delete ui;
    pKeyboard = NULL;

}

void CNumericKbd::ShowKeyboard(QLineEdit* pCallerEdit,QWidget* parent)
{
    if(!pKeyboard)
    {
        pKeyboard = new CNumericKbd();
    }

    bool isNewEdit = pKeyboard->GetAssociatedEdit()!=pCallerEdit;
    pKeyboard->ShowKbd(pCallerEdit,parent);
    if(isNewEdit)
    {
        pKeyboard->ui->lineEdit->setText(pCallerEdit->text());
        pKeyboard->ui->lblName->setText(pCallerEdit->toolTip());
    }
}

void CNumericKbd::CloseDelayed()
{
    pKeyboard->CloseKbdDelayed();
}

void CNumericKbd::on_btn1_clicked()
{
    pCallerEdit->insert("1");
    ui->lineEdit->setText(pCallerEdit->text());
    pCallerEdit->setFocus();
}

void CNumericKbd::on_btn2_clicked()
{
    pCallerEdit->insert("2");
    ui->lineEdit->setText(pCallerEdit->text());
    pCallerEdit->setFocus();
}

void CNumericKbd::on_btn3_clicked()
{
    pCallerEdit->insert("3");
    ui->lineEdit->setText(pCallerEdit->text());
    pCallerEdit->setFocus();
}

void CNumericKbd::on_btn4_clicked()
{
    pCallerEdit->insert("4");
    ui->lineEdit->setText(pCallerEdit->text());
    pCallerEdit->setFocus();
}

void CNumericKbd::on_btn5_clicked()
{
    pCallerEdit->insert("5");
    ui->lineEdit->setText(pCallerEdit->text());
    pCallerEdit->setFocus();
}

void CNumericKbd::on_btn6_clicked()
{
    pCallerEdit->insert("6");
    ui->lineEdit->setText(pCallerEdit->text());
    pCallerEdit->setFocus();
}

void CNumericKbd::on_btn7_clicked()
{
    pCallerEdit->insert("7");
    ui->lineEdit->setText(pCallerEdit->text());
    pCallerEdit->setFocus();
}

void CNumericKbd::on_btn8_clicked()
{
    pCallerEdit->insert("8");
    ui->lineEdit->setText(pCallerEdit->text());
    pCallerEdit->setFocus();
}

void CNumericKbd::on_btn9_clicked()
{
    pCallerEdit->insert("9");
    ui->lineEdit->setText(pCallerEdit->text());
    pCallerEdit->setFocus();
}

void CNumericKbd::on_btn0_clicked()
{
    pCallerEdit->insert("0");
    ui->lineEdit->setText(pCallerEdit->text());
    pCallerEdit->setFocus();
}

void CNumericKbd::on_btnComma_clicked()
{
    pCallerEdit->insert(",");
    ui->lineEdit->setText(pCallerEdit->text());
    pCallerEdit->setFocus();
}

void CNumericKbd::on_btnDot_clicked()
{
    pCallerEdit->insert(".");
    ui->lineEdit->setText(pCallerEdit->text());
    pCallerEdit->setFocus();
}

void CNumericKbd::on_btnBksp_clicked()
{
    pCallerEdit->backspace();
    ui->lineEdit->setText(pCallerEdit->text());
    pCallerEdit->setFocus();
}

void CNumericKbd::on_btnClear_clicked()
{
    pCallerEdit->clear();
    ui->lineEdit->setText(pCallerEdit->text());
    pCallerEdit->setFocus();
}

void CNumericKbd::on_btnClose_clicked()
{
    close();
}

void CNumericKbd::Close()
{
    if(IsVisible())
    {
        pKeyboard->close();
    }
}
