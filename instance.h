#ifndef INSTANCE_H
#define INSTANCE_H
#include <QString>
#include <QSettings>

class Instance
{
private:
    QString name;
    QString key;
    unsigned long rewordColor;
    int rewordBox;
    bool checked;

public:
    Instance(const QString &name, const QString &key, unsigned long rewordColor, int rewordBox);
    Instance();

    static Instance *fromInitValue(const QString key, const QStringList &value);
    QStringList toIniValue();
    bool iniSave(QSettings *settings);

    unsigned long getRewordColor() const;
    void setRewordColor(unsigned long value);
    int getRewordBox() const;
    void setRewordBox(int value);
    QString getName() const;
    void setName(const QString &value);
    QString getKey() const;
    void setKey(const QString &value);
    bool getChecked() const;
    void setChecked(bool value);
};

#endif // INSTANCE_H
