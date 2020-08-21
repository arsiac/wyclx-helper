#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QStringList>
#include <QSettings>
#include <QTextCodec>
#include "instance.h"

class Settings
{
private:
    QSettings *settings;

public:
    Settings(const char *path);

    // default
    bool getAutoOpenLOG();
    void saveAutoOpenLOG(bool state);

    // reword
    QStringList getInstancesNames();
    QStringList getInstanceByKey(const QString &key);
    void saveInstances(Instance **instances, int length);
    int getRewordFlashDelay();
    void saveRewordFlashDelay(int delay);
    int getRewordPopupDelay();
    void saveRewordPopupDelay(int delay);
    QString getRewordFontLibrary();
    void setRewrdFontLibrary(QString &path);

    // daily
    QString getDailyFontLibrary();
    void saveDailyFontLibrary(QString &path);
    int getDailyFlashDelay();
    void setDailyFlashDelay(int delay);
};

#endif // SETTINGS_H
