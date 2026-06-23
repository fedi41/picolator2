#pragma once
#include "assets/Image.h"
#include "gfx/DrawUtils.h"
#include "storage/Storage.h"
#include "core/Input.h"
#include <cstdlib>

#define DINO_JUMP_VEL 12.5
#define DINO_SCREEN_X 7
#define FLOOR_HEIGHT 50

#define GRAVITY 1
#define GRAVITY_SNEAK 2


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
    bool sneaking = false;
    Cactus currentCactus = {
        240, &DinoRunnerAssets::Cactus::cactus_small1 
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
            240, &DinoRunnerAssets::Cactus::cactus_small1
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

        if (sneaking) {
            yVel -= GRAVITY_SNEAK;
        } else {
            yVel -= GRAVITY;
        }
        dinoY += yVel;
        levelScroll += speed;
        currentCactus.x -= speed;
        score += 1;
        
        speed += 0.004;


        if (currentCactus.x < -currentCactus.texture->width) {
            currentCactus.x = 240 + speed * 10 + rand() % 100 - 50;

            int cactusType = rand() % 3;

            switch (cactusType) {
                case 0:
                    currentCactus.texture = &DinoRunnerAssets::Cactus::cactus_small1;break;
                case 1: 
                    currentCactus.texture = &DinoRunnerAssets::Cactus::cactus_big1;break;
                case 2:
                    currentCactus.texture = &DinoRunnerAssets::Cactus::cactus_multi;break;
                default: break;
            }

            if (Input::pressed(KEY_Y)) {
                currentCactus.texture = &DinoRunnerAssets::Cactus::cactus_giga;
            }
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
            if (score > Storage::data.dinoRunnerHighScore) {
                Storage::data.dinoRunnerHighScore = score;
                Storage::save();

            }
        }



        // UPDATE TEXTURE
        
        dinoAnimCounter += 1;

        dinoTexture = &DinoRunnerAssets::Dino::idle;
        if (gameOver) {
            dinoTexture = &DinoRunnerAssets::Dino::scared;
        } else if (isOnGround()) {
            if (sneaking) {
                dinoTexture = &DinoRunnerAssets::Dino::sneak1;
                if (dinoAnimCounter > 10) {
                    dinoAnimCounter = 0;
                } else if (dinoAnimCounter > 5) {
                    dinoTexture = &DinoRunnerAssets::Dino::sneak2;
                }
            } else {
                dinoTexture = &DinoRunnerAssets::Dino::run1;
                if (dinoAnimCounter > 10) {
                    dinoAnimCounter = 0;
                } else if (dinoAnimCounter > 5) {
                    dinoTexture = &DinoRunnerAssets::Dino::run2;
                }
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