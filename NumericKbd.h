#ifndef NUMERICKBD_H
#define NUMERICKBD_H

#include <KbdBase.h>

namespace Ui {
    class CNumericKbd;
}

class CNumericKbd : public CKbdBase
{
    Q_OBJECT

public:
    explicit CNumericKbd(QWidget *parent = 0);
    virtual ~CNumericKbd();

    static void ShowKeyboard(QLineEdit* pCallerEdit,QWidget* parent);
    static void CloseDelayed();
    static void Close();
    static bool IsVisible(){return pKeyboard && pKeyboard->isVisible();}
    static QLineEdit* GetEdit(){return pKeyboard ? pKeyboard->GetAssociatedEdit() : NULL;}

protected:
    static CNumericKbd* pKeyboard;

private:
    Ui::CNumericKbd *ui;

private slots:
    void on_btnClose_clicked();
    void on_btnClear_clicked();
    void on_btnBksp_clicked();
    void on_btnDot_clicked();
    void on_btnComma_clicked();
    void on_btn0_clicked();
    void on_btn9_clicked();
    void on_btn8_clicked();
    void on_btn7_clicked();
    void on_btn6_clicked();
    void on_btn5_clicked();
    void on_btn4_clicked();
    void on_btn3_clicked();
    void on_btn2_clicked();
    void on_btn1_clicked();
};

#endif // NUMERICKBD_H
