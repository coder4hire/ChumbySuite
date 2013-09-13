#include "KbdEditBox.h"
#include "NumericKbd.h"
#include "EnglishKbd.h"
#include "stdio.h"

CKbdEditBox::CKbdEditBox(QWidget *parent) :
    QLineEdit(parent)
{
    IsNumeric=false;
    IsAutoDeleteEnabled=false;
}

void CKbdEditBox::focusInEvent(QFocusEvent *ev)
{
    QLineEdit::focusInEvent(ev);
    QWidget* parent = parentWidget();
    while(parent->parentWidget() && !parent->inherits("QDialog"))
    {
        parent = parent->parentWidget();
    }

    if(IsNumeric)
    {
        if(IsAutoDeleteEnabled && CNumericKbd::GetEdit()!=this)
        {
            setText("");
        }
        CNumericKbd::ShowKeyboard((QLineEdit*)this,parent);
        CEnglishKbd::Close();
    }
    else
    {
        if(IsAutoDeleteEnabled && CEnglishKbd::GetEdit()!=this)
        {
            setText("");
        }
        CEnglishKbd::ShowKeyboard((QLineEdit*)this,parent);
        CNumericKbd::Close();
    }
}

void CKbdEditBox::focusOutEvent(QFocusEvent *ev)
{
    QLineEdit::focusOutEvent(ev);
    if(IsNumeric)
    {
        CNumericKbd::CloseDelayed();
    }
    else
    {
        CEnglishKbd::CloseDelayed();
    }
}
