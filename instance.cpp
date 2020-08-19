#include "instance.h"

bool Instance::getChecked() const
{
    return checked;
}

void Instance::setChecked(bool value)
{
    checked = value;
}

Instance::Instance(const QString &name, const QString &key, unsigned long rewordColor, int rewordBox)
{
    this->name = name;
    this->key = key;
    this->rewordColor = rewordColor;
    this->rewordBox = rewordBox;
}

Instance::Instance()
{
    Instance("", "", 0L, 0);
}

Instance *Instance::fromInitValue(const QString key, const QStringList &value)
{
    if (value.length() != 4)
    {
        return NULL;
    }
    Instance *instance = new Instance;
    instance->setKey(key);
    instance->setName(value.at(0));
    instance->setRewordColor(value.at(1).toULong());
    instance->setRewordBox(value.at(2).toInt());
    instance->setChecked(value.at(3).toInt());
    return instance;
}

QStringList Instance::toIniValue()
{
    QStringList objectList;
    objectList.append(name);
    objectList.append(QString::number(rewordColor));
    objectList.append(QString::number(rewordBox));
    objectList.append(QString::number(checked));
    return objectList;
}

#include <iostream>
bool Instance::iniSave(QSettings *settings)
{
    if (key == "")
    {
        return false;
    }
    if (!settings)
    {
        return false;
    }

    QStringList objList = this->toIniValue();
//    std::cout << objList.join(",").toStdString() << std::endl;
    settings->setValue(key.prepend("instance/"), toIniValue());
    return true;
}

QString Instance::getName() const
{
    return name;
}

void Instance::setName(const QString &value)
{
    name = value;
}

QString Instance::getKey() const
{
    return key;
}

void Instance::setKey(const QString &value)
{
    key = value;
}

unsigned long Instance::getRewordColor() const
{
    return rewordColor;
}

void Instance::setRewordColor(unsigned long value)
{
    rewordColor = value;
}

int Instance::getRewordBox() const
{
    return rewordBox;
}

void Instance::setRewordBox(int value)
{
    rewordBox = value;
}

