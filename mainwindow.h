#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QThread>
#include <QSettings>
#include <QTextCodec>
#include <QFile>
#include <cstdlib>
#include <iostream>
#include "script/abstractscript.h"
#include "script/rewordscript.h"
#include "instance.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString &configFilePath, QWidget *parent = nullptr);
    ~MainWindow();
    void clearOutput();

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void rewordNormal(const QString &msg);

    void rewordError(const QString &msg);

    void rewordScanResult(const QString &name, int number, int expect);

    void setRewordScriptStateLabel(bool state);


private slots:
    void on_rewordStartButton_clicked();

    void on_rewordResetWindowButton_clicked();

    void on_rewordStopButton_clicked();

    void on_registerPulignButton_clicked();

    void on_uinstallPulignButton_clicked();

private:
    Ui::MainWindow *ui;

    Dm::dmsoft *dm;

    gc::WindowControl *wc;

    QThread scriptThread;

    AbstractScript *script;

    QSettings *settings;

    Instance **instances;

    int instancesLength;

    bool isInitSuccess;

    QString stateStopStyle, stateStartStyle;

    bool initInstances();

    void reInitInstance();

    void initUiData();

    void initRewordConnect(RewordScript *rscript);

    void writeSettings();

signals:
    void startScript();

};
#endif // MAINWINDOW_H
