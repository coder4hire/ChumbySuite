#include <QtGui/QApplication>
#include "cwidgetbase.h"
#include "WidgetSelector.h"
#include "HardwareLayer.h"
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CWidgetSelector selector;

    selector.LoadWidgets();

    //-F- Appying default stylesheet
    QFile file(":/Resources/default.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    a.setStyleSheet(styleSheet);
    file.close();

    //-F- Calling OnSettingsChanged to load initial values
    for(int i=0;i<selector.GetCount();i++)
    {
        selector.GetWidget(i)->OnSettingsChanged();
    }

    //-F- Showing Main Window Widget
    selector.show();
    selector.ShowThisWidget(0);   

    //-F- Adjusting brightness
    CHardwareLayer::GetInstance()->SetBrightness(
                selector.GetSettings()->value("General/Brightness",100).toInt());

    return a.exec();
}
