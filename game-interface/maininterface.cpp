#include "maininterface.h"

FeaturePoint *MainInterface::getMenuControlButton() const
{
    return menuControlButton;
}

MainMenuButtonFeature MainInterface::getMenuButton(QString &key)
{
    QMap<QString, MainMenuButtonFeature>::iterator miter = menuMap->find(key);
    if (miter != menuMap->end())
    {
        return miter.value();
    }
    else
    {
        return MainMenuButtonFeature(-1, -1, false);
    }
}

MainInterface::MainInterface()
{
    menuControlButton = new FeaturePoint(13, 16, 14474195L);

    menuMap = new QMap<QString, MainMenuButtonFeature>;
    menuMap->insert("user", MainMenuButtonFeature(53, 16, false));
    menuMap->insert("shop", MainMenuButtonFeature(170, 16, false));
    menuMap->insert("active", MainMenuButtonFeature(209, 16, false));
    menuMap->insert("package", MainMenuButtonFeature(247, 16, false));
}

MainInterface::~MainInterface()
{
    delete menuMap;
}
