#include "mainmenubuttonfeature.h"

gc::Point MainMenuButtonFeature::getLocation() const
{
    return location;
}

void MainMenuButtonFeature::setLocation(const gc::Point &value)
{
    location = value;
}

bool MainMenuButtonFeature::getNeedOpenMenu() const
{
    return needOpenMenu;
}

void MainMenuButtonFeature::setNeedOpenMenu(bool value)
{
    needOpenMenu = value;
}

MainMenuButtonFeature::MainMenuButtonFeature(int x, int y, bool need)
{
    this->location = gc::Point(x, y);
    this->needOpenMenu = need;
}

MainMenuButtonFeature::MainMenuButtonFeature()
{

}
