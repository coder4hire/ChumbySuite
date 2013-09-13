#ifndef CWIDGETBASE_H
#define CWIDGETBASE_H

#include <QDialog>
#include <QWidget>

class CWidgetSelector;
class QSettings;
class CConfigWidgetBase;

class CWidgetBase : public QWidget
{
    Q_OBJECT
    friend class CWidgetSelector;

public:
    explicit CWidgetBase(QWidget *parent=0);
    virtual ~CWidgetBase();

    void setBackground(QString fileName);
//    CWidgetSelector* GetWidgetSelector(){return (CWidgetSelector*)parentWidget()->parentWidget();}
    virtual void Initialize(CWidgetSelector* pSelector, QSettings* pSettings);
    CConfigWidgetBase* GetConfigWidget(){return pConfigWidget;}
    virtual void OnSettingsChanged(){};

    virtual bool OnButtonDown(){return false;}
    virtual bool OnButtonUp(bool isLongClick){isLongClick=false;return false;}
    virtual bool OnRotaryMoved(int speed,bool isButtonDown){speed=0;isButtonDown=false;return false;}

protected:
    CWidgetSelector* pSelector;
    QSettings* pSettings;
    CConfigWidgetBase* pConfigWidget;

    int nightBrightness;
    int brightness;

    void paintEvent (QPaintEvent *);
};

#endif // CWIDGETBASE_H
