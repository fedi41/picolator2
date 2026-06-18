

#include "MainApp.h"
#include "core/Logger.h"

void MainApp::init() {
    Logger::d("Initializing MainApp");
    items = {"Dino runner", "cool app", "EEPROM writer", "wooooow", "heheh", "buah", "idk"};
    heading = "PICOLATOR";
    setDirty();
}