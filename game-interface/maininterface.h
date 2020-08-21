#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include "gameinterface.h"
#include "featurepoint.h"
#include "mainmenubuttonfeature.h"

class MainInterface: public GameInterface
{
private:
    FeaturePoint *menuControlButton;
    QMap<QString, MainMenuButtonFeature> *menuMap;
public:
    MainInterface();
    ~MainInterface();
    FeaturePoint *getMenuControlButton() const;
    MainMenuButtonFeature getMenuButton(QString &key);
};

#endif // MAININTERFACE_H
