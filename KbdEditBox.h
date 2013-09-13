#ifndef KBDEDITBOX_H
#define KBDEDITBOX_H

#include <QLineEdit>

class CKbdEditBox : public QLineEdit
{
    Q_OBJECT
public:
    explicit CKbdEditBox(QWidget *parent = 0);
    bool IsNumeric;
    bool IsAutoDeleteEnabled;

protected:
    void focusInEvent(QFocusEvent *);
    void focusOutEvent(QFocusEvent *);

signals:

public slots:

};

#endif // KBDEDITBOX_H
