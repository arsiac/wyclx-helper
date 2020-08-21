#ifndef MAINMENUBUTTONFEATURE_H
#define MAINMENUBUTTONFEATURE_H

#include "window-controller/point.h"

class MainMenuButtonFeature
{
private:
    gc::Point location;
    bool needOpenMenu;
public:
    MainMenuButtonFeature(int x, int y, bool need);
    MainMenuButtonFeature();
    gc::Point getLocation() const;
    void setLocation(const gc::Point &value);
    bool getNeedOpenMenu() const;
    void setNeedOpenMenu(bool value);
};

#endif // MAINMENUBUTTONFEATURE_H
