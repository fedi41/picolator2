#include "TaskBar.h"
#include <string>
#include "core/Display.h"
#include "gfx/Colors.h"
#include "core/Navigation.h"

void TaskBar::render() {
    Display::drawRect(0,0,240,10,Colors::black);
    Display::drawCenteredString(0, currentAppName, Colors::white, Display::alpha, &Font6x8, 1);
}

void TaskBar::update() {

  std::string newAppName = appName(Navigation::currentAppId());
  if (newAppName != currentAppName) {currentAppName = newAppName; setDirty();}
  
}

