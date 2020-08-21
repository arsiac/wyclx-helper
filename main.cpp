#include <QApplication>
#include <QDir>
#include <QIcon>
#include <QSettings>
#include "widget/scriptwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString currentDir = QApplication::applicationDirPath();
    QDir::setCurrent(currentDir);
    ScriptWindow scriptWindow;
    scriptWindow.setWindowIcon(QIcon("./resource/images/qc.ico"));
    scriptWindow.show();
    return app.exec();
}
