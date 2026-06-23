#pragma once
#include "assets/Image.h"
#include "gfx/DrawUtils.h"

#define DINO_JUMP_VEL 12.5
#define DINO_SCREEN_X 7
#define FLOOR_HEIGHT 50

// #define FLOOR_TEXTURE &DinoRunnerAssets::floor;
// #define DINO_IDLE_TEXTURE &DinoRunnerAssets::Dino::idle;
// #define DINO_RUN1_TEXTURE &DinoRunnerAssets::Dino::run1;
// #define DINO_RUN2_TEXTURE &DinoRunnerAssets::Dino::run2;
// #define DINO_SCARED_TEXTURE &DinoRunnerAssets::Dino::scared;


struct Cactus {
    float x = 240;
    const Image1Bit* texture;
};

class DinoGame 
{
public:
    float dinoY = FLOOR_HEIGHT; 
    float yVel = 0; 
    float levelScroll = 0;
    int score = 0;
    const Image1Bit* dinoTexture = &DinoRunnerAssets::Dino::run1;
    Cactus currentCactus = {
        240, &DinoRunnerAssets::Cactus::cactus1 
    };
    float speed = 4;
    int dinoAnimCounter = 0;

    bool gameOver = false;

    void restart() {
        dinoY = FLOOR_HEIGHT; 
        yVel = 0; 
        levelScroll = 0;
        dinoTexture = &DinoRunnerAssets::Dino::run1;
        currentCactus = {
            240, &DinoRunnerAssets::Cactus::cactus1 
        };
        speed = 4;
        dinoAnimCounter = 0;
        score = 0;

        gameOver = false;
    }
    
    bool isOnGround() {return dinoY <= FLOOR_HEIGHT;}
    void fixPosition() {
        if (dinoY < FLOOR_HEIGHT) {
            yVel = 0;
            dinoY = FLOOR_HEIGHT;
        }
    }
    void update() {
        if (gameOver) {
            return;
        }


        yVel -= 1;
        dinoY += yVel;
        levelScroll += speed;
        currentCactus.x -= speed;
        score += 1;
        speed += 0.004;


        if (currentCactus.x < -currentCactus.texture->width) {
            currentCactus.x = 240 + speed * 10;
        }

        if (DrawUtils::overlap(
            DINO_SCREEN_X, 
            240 - dinoY - dinoTexture->height, 
            *dinoTexture,
            
            currentCactus.x, 
            240 - currentCactus.texture->height-FLOOR_HEIGHT, 
            *currentCactus.texture
        )) {
            gameOver = true;
        }



        // UPDATE TEXTURE
        
        dinoAnimCounter += 1;

        dinoTexture = &DinoRunnerAssets::Dino::idle;
        if (gameOver) {
            dinoTexture = &DinoRunnerAssets::Dino::scared;
        } else if (isOnGround()) {
            dinoTexture = &DinoRunnerAssets::Dino::run1;
            if (dinoAnimCounter > 10) {
                dinoAnimCounter = 0;
            } else if (dinoAnimCounter > 5) {
                dinoTexture = &DinoRunnerAssets::Dino::run2;
            }
        }

        fixPosition();

    }   
    void jump() {
        if (gameOver) { return; }

        if (dinoY <= FLOOR_HEIGHT) {
            yVel = DINO_JUMP_VEL;
        }
    }
};