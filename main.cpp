#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include <QIcon>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString currentDir = QApplication::applicationDirPath();
    QDir::setCurrent(currentDir);
    MainWindow win("./resource/settings.ini");
    win.setWindowIcon(QIcon("./resource/images/qc.ico"));
    win.show();
    return app.exec();
}
