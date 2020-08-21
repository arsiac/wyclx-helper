#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <windows.h>
#include <QString>
#include <QWidget>
#include <QMessageBox>
#include <QFile>
#include <QCloseEvent>
#include <QTextCursor>

namespace Ui {
class SettingWindow;
}

class SettingWindow : public QWidget
{
    Q_OBJECT



public:
    explicit SettingWindow(QWidget *parent = nullptr);
    ~SettingWindow();

    // default
    bool getAutoOpenLOG();
    void setAutoOpenLOG(bool state);
    // reword
    QString getRewordFontLibrary();
    void setRewordFontLibrary(const QString &path);
    // daily
    QString getDailyFontLibrary();
    void setDailyFontLibrary(const QString &path);
    int getDailyFlashDelay();
    void setDailyFlashDelay(int delay);

private slots:
    void on_registerPulignButton_clicked();

    void on_uinstallPulignButton_clicked();

private:
    Ui::SettingWindow *ui;
};

#endif // SETTINGWINDOW_H
