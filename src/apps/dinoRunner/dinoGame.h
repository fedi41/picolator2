#pragma once

class DinoGame {
    float y = 0; 
    float yVel = 0; 
    float x = 0;
    
    bool isOnGround() {return y <= 0;}
    void fixPosition() {
        if (y < 0) {
            yVel = 0;
            y = 0;
        }
    }
    void update() {

        yVel -= 1;
        y += yVel;


    }
    
};