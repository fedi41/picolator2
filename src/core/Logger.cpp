#include "Logger.h"

#include <list>
#include <string>

#include "core/Display.h"
#include "gfx/Colors.h"

void Logger::render() {
    
    int i = 0;
    if (log.size() > 35) {
        i = log.size() - 35;
    }
    
    int y = 0;
    while (i < log.size()) {
        Display::drawString(0,y,log[i],Colors::white,Colors::black,false,&Font4x6,1);

        y+=6;
        i++;
    }


    // while (i*6 < 234 && i < log.size()) {
    //     Display::drawString(0,i*6,log[i],0xffff,Display::alpha,false,&Font4x6);
        
    // }

}

void Logger::renderOnOverlay() {
    Display::overlayMode = true;
    Display::clear(Display::alpha);

    render();

    Display::overlayMode = false;

    // while (i*6 < 234 && i < log.size()) {
    //     Display::drawString(0,i*6,log[i],0xffff,Display::alpha,false,&Font4x6);
        
    // }

}