#include "Logger.h"

#include <list>
#include <string>

#include "core/Display.h"
#include "gfx/Colors.h"

void Logger::render() {

    Display::blendMode = MIX;
    
    int i = 0;
    if (log.size() > 60) {
        i = log.size() - 60;
    }
    
    int y = 0;
    while (i < log.size()) {
        Display::drawString(0,y,log[i],Colors::white,Colors::black,false,&Font4x6,1);

        y+=6;
        i++;
    }

    dirty = false; 
    
    Display::blendMode = NORMAL;


    // while (i*6 < 234 && i < log.size()) {
    //     Display::drawString(0,i*6,log[i],0xffff,Display::alpha,false,&Font4x6);
        
    // }

}