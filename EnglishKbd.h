#ifndef ENGLISHKBD_H
#define ENGLISHKBD_H

#include <KbdBase.h>
#include <QPushButton>

namespace Ui {
    class CEnglishKbd;
}

class CEnglishKbd : public CKbdBase
{
    Q_OBJECT

    enum EShiftMode
    {
        SH_NONE,
        SH_SHIFT,
        SH_CAPS
    };

public:
    explicit CEnglishKbd(QWidget *parent = 0);
    virtual ~CEnglishKbd();

    static void ShowKeyboard(QLineEdit* pCallerEdit,QWidget* parent);
    static void CloseDelayed();
    static void Close();
    static bool IsVisible(){return pKeyboard && pKeyboard->isVisible();}
    static QLineEdit* GetEdit(){return pKeyboard ? pKeyboard->GetAssociatedEdit() : NULL;}

private slots:
    void on_btnSpace_clicked();
    void on_btnSym_clicked();
    void on_btnShift_clicked();
    void on_btnBksp_clicked();

    void on_btnClear_clicked();

    void on_btnClose_clicked();
    void on_SymbolButton_clicked();

private:
    Ui::CEnglishKbd *ui;

protected:
    QPushButton* buttons[40];
    static const char* lowCaseBtns;
    static const char* upperCaseBtns;
    static const char* symbolsBtns;
    EShiftMode shiftMode;
    bool isSymbolMode;

    static CEnglishKbd* pKeyboard;

    void SetButtonsNames();
};

#endif // ENGLISHKBD_H
