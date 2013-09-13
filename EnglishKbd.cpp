#include "EnglishKbd.h"
#include "ui_EnglishKbd.h"
#include "stdio.h"

const char* CEnglishKbd::lowCaseBtns = {"1234567890qwertyuiopasdfghjkl;zxcvbnm,./"};
const char* CEnglishKbd::upperCaseBtns = {"!@#$%^&*()QWERTYUIOPASDFGHJKL:ZXCVBNM<>?"};
const char* CEnglishKbd::symbolsBtns={"1234567890!@#$%^&*()`~-_=+;:\"'[]{}\\|/?<>"};

CEnglishKbd* CEnglishKbd::pKeyboard=NULL;

CEnglishKbd::CEnglishKbd(QWidget *parent) :
    CKbdBase(parent),
    ui(new Ui::CEnglishKbd)
{
    ui->setupUi(this);

    //-F- Filling buttons matrix
    for(int i=0;i<this->children().size();i++)
    {
        int x=0,y=0;
        QObject* pChild=this->children().at(i);
        if(pChild->inherits("QPushButton") &&
           sscanf(pChild->objectName().toLatin1().data(),"btn%d_%d",&x,&y)==2)
        {
            buttons[(y-1)*10+(x-1)]=(QPushButton*)pChild;
            connect((QPushButton*)pChild,SIGNAL(clicked()),SLOT(on_SymbolButton_clicked()));
        }
    }

    shiftMode=SH_NONE;
    isSymbolMode = false;
    SetButtonsNames();
}

CEnglishKbd::~CEnglishKbd()
{
    delete ui;
    pKeyboard=NULL;
}

void CEnglishKbd::on_btnBksp_clicked()
{
    pCallerEdit->backspace();
    ui->lineEdit->setText(pCallerEdit->text());
    pCallerEdit->setFocus();
}

void CEnglishKbd::on_btnClear_clicked()
{
    pCallerEdit->clear();
    ui->lineEdit->setText(pCallerEdit->text());
    pCallerEdit->setFocus();
}

void CEnglishKbd::on_btnClose_clicked()
{
    close();
}

void CEnglishKbd::SetButtonsNames()
{
    const char * buttonsMatrix=NULL;

    if(!isSymbolMode)
    {
        switch(shiftMode)
        {
        case SH_NONE:
            buttonsMatrix = lowCaseBtns;
            break;
        case SH_SHIFT:
        case SH_CAPS:
            buttonsMatrix = upperCaseBtns;
            break;
        }
    }
    else
    {
        buttonsMatrix = symbolsBtns;
    }

    for(unsigned int i=0;i<sizeof(buttons)/sizeof(QPushButton*);i++)
    {
        buttons[i]->setText(buttonsMatrix[i]=='&' ? "&&" : QString(buttonsMatrix[i]));
        QPalette pal=buttons[i]->palette();
        pal.setColor(QPalette::WindowText,isSymbolMode ? Qt::blue : Qt::black);
        buttons[i]->setPalette(pal);
    }
}

void CEnglishKbd::on_btnShift_clicked()
{
    if(shiftMode== SH_NONE)
    {
        shiftMode = SH_SHIFT;
    }
    else
    {
        shiftMode = SH_NONE;
    }

    SetButtonsNames();
}

void CEnglishKbd::on_btnSym_clicked()
{
    isSymbolMode=!isSymbolMode;

    SetButtonsNames();
}

void CEnglishKbd::on_SymbolButton_clicked()
{
    QPushButton *pBtn = qobject_cast<QPushButton*>(sender());
    if(pBtn)
    {
        pCallerEdit->insert(pBtn->text()== "&&" ? "&" : pBtn->text());
        ui->lineEdit->setText(pCallerEdit->text());
        if(shiftMode==SH_SHIFT)
        {
            shiftMode=SH_NONE;
            SetButtonsNames();
        }
    }
}

void CEnglishKbd::on_btnSpace_clicked()
{
    pCallerEdit->insert(" ");
    ui->lineEdit->setText(pCallerEdit->text());
    if(shiftMode==SH_SHIFT)
    {
        shiftMode=SH_NONE;
        SetButtonsNames();
    }
}

void CEnglishKbd::ShowKeyboard(QLineEdit* pCallerEdit,QWidget* parent)
{
    if(!pKeyboard)
    {
        pKeyboard = new CEnglishKbd();
    }

    bool isNewEdit = pKeyboard->GetAssociatedEdit()!=pCallerEdit;
    pKeyboard->ShowKbd(pCallerEdit,parent);
    if(isNewEdit)
    {
        pKeyboard->ui->lineEdit->setText(pCallerEdit->text());
        pKeyboard->ui->lblName->setText(pCallerEdit->toolTip());
    }
}

void CEnglishKbd::CloseDelayed()
{
    //-F- Don't close this keyboard on timeout
    //pKeyboard->CloseKbdDelayed();
}

void CEnglishKbd::Close()
{
    if(IsVisible())
    {
        pKeyboard->close();
    }
}
