#include "Logger.h"

#include <list>
#include <string>

#include "core/Display.h"


void Logger::render() {
    Display::overlayMode = true;

    Display::clear(Display::alpha);

    int y = 0;
    for (std::string l : log) {
        Display::drawString(0,y,l,0xffff,Display::alpha,false,&Font6x8,1);

        y+=8;
    }

    Display::overlayMode = false;

    // while (i*6 < 234 && i < log.size()) {
    //     Display::drawString(0,i*6,log[i],0xffff,Display::alpha,false,&Font4x6);
        
    // }

}