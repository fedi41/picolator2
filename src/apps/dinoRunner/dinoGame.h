#pragma once

#define DINO_JUMP_VEL 12.5

class DinoGame 
{
public:
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
        x += 1;
        fixPosition();

    }   
    void jump() {
        if (y <= 0) {
            yVel = DINO_JUMP_VEL;
        }
    }
};