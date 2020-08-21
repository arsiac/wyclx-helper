#include "settings.h"

Settings::Settings(const char *path)
{
    settings = new QSettings(path, QSettings::IniFormat);
    settings->setIniCodec(QTextCodec::codecForName("UTF-8"));
}

QStringList Settings::getInstancesNames()
{
    if (!settings->contains("instance/names"))
    {
        return QStringList();
    }
    return settings->value("instance/names").toStringList();
}

QStringList Settings::getInstanceByKey(const QString &key)
{
    QString ikey = QString("instance/").append(key);
    if (!settings->contains(ikey))
    {
        return QStringList();
    }
    return settings->value(ikey).toStringList();
}

void Settings::saveInstances(Instance **instances, int length)
{
    QStringList nameList;
    QString key;
    for(int i=0; i<length; i++)
    {
        key = instances[i]->getKey();
        nameList.append(key);
        settings->setValue(QString("instance/").append(key), instances[i]->toIniValue());
    }
    if (!nameList.length())
    {
        return;
    }
    settings->setValue("instance/names", nameList);
}

int Settings::getRewordFlashDelay()
{
    if (!settings->contains("reword/flashDelay"))
    {
        return 200;
    }
    return settings->value("reword/flashDelay").toInt();

}

void Settings::saveRewordFlashDelay(int delay)
{
    settings->setValue("reword/flashDelay", delay);
}

int Settings::getRewordPopupDelay()
{
    if (!settings->contains("reword/popupDelay"))
    {
        return 100;
    }
    return settings->value("reword/popupDelay").toInt();
}

void Settings::saveRewordPopupDelay(int delay)
{
    settings->setValue("reword/popupDelay", delay);
}

QString Settings::getRewordFontLibrary()
{
    if (!settings->contains("reword/fontLibrary"))
    {
        return "";
    }
    return settings->value("reword/fontLibrary").toString();
}

void Settings::setRewrdFontLibrary(QString &path)
{
    settings->setValue("reword/fontLibrary", path);
}

QString Settings::getDailyFontLibrary()
{
    if (!settings->contains("daily/fontLibrary"))
    {
        return "";
    }
    return settings->value("daily/fontLibrary").toString();
}

void Settings::saveDailyFontLibrary(QString &path)
{
    settings->setValue("daily/fontLibrary", path);
}

int Settings::getDailyFlashDelay()
{
    if (!settings->contains("daily/flashDelay"))
    {
        return 2000;
    }
    return settings->value("daily/flashDelay").toInt();
}

void Settings::setDailyFlashDelay(int delay)
{
    settings->setValue("daily/flashDelay", delay);
}

bool Settings::getAutoOpenLOG()
{
    if (!settings->contains("default/autoOpenLOG"))
    {
        return true;
    }
    return settings->value("default/autoOpenLOG").toBool();
}

void Settings::saveAutoOpenLOG(bool state)
{
    settings->setValue("default/autoOpenLOG", state);
}

