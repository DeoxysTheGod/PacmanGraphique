#include "gameSprite.h"
#include "parameters.h"

using namespace std;
using namespace nsShape;
using namespace nsGraphics;

void initPacman(sPacman & pac, const unsigned caseSize) {
    // position
    pac.pos = {200, 200};
    pac.posMat = {1,1};
    pac.initialPosNotInit = true;

    // sprite
    pac.triangleAmount = 40;
    pac.size = caseSize/2.5;
    pac.rotation = 0;

    // score
    pac.score = 0;
    pac.stock = 3;

    // deplacement
    pac.speed = 3;
    pac.currentMove = 'p';
    pac.lastMove = 'p';

    // contact
    pac.hitGhost = false;

    // cooldown
    pac.cooldown = 0;
    pac.eatCooldown = 0;
    pac.canEat = false;

    // Bouche du pacman
    pac.mouthSize = pac.triangleAmount/5;
    pac.mouthStart = pac.triangleAmount-pac.mouthSize/2;

    // animation bouche
    pac.idle = 1;
    pac.totalAnimation = pac.mouthSize;
    pac.currentAnimation = 0;

    // couleur
    pac.color = KYellow;
    pac.mouthColor = KBlack;

    // touches
    loadParameter (pac, pac.authKey);
}

void initGhost(sGhost & ghost, const unsigned caseSize) {
    // position
    ghost.pos = {200, 200};
    ghost.posMat = {1,1};

    // sprite
    ghost.triangleAmount = 40;
    ghost.size = caseSize/3;

    // contact
    ghost.hitPacman = false;

    // mouvements
    ghost.lastMove = 'p';
    ghost.currentMove = 'p';
    ghost.speed = 4;
    ghost.baseSpeed = ghost.speed;

    // cooldown
    ghost.cooldown = 0;

    // Yeux du fantome
    ghost.eyeSize = ghost.size/3;
    ghost.pupilSize = ghost.size/6;
    ghost.rightEyePos = {ghost.pos.first - ghost.size/2, ghost.pos.second};
    ghost.leftEyePos = {ghost.pos.first + ghost.size/2, ghost.pos.second};

    // Vague
    ghost.nbWave = 4;
    ghost.waveSize = double(ghost.size)/double(ghost.nbWave);
    ghost.wavePos = {(ghost.pos.first-ghost.size)+ghost.waveSize, ghost.pos.second+ghost.size};

    // couleur
    ghost.color = KRed;
    ghost.eyeColor = KWhite;
    ghost.pupilColor = KLightBlue;

    // touches
    loadParameter (ghost, ghost.authKey);
}

void majGhostSpritePos(sGhost & ghost) {
    ghost.rightEyePos = {ghost.pos.first - ghost.size/2.2, ghost.pos.second};
    ghost.leftEyePos = {ghost.pos.first + ghost.size/2.2, ghost.pos.second};
    ghost.wavePos = {(ghost.pos.first-ghost.size)+ghost.waveSize, ghost.pos.second+ghost.size};
}

void pacmanAnimation(sPacman & pac) {
    if (pac.currentAnimation < pac.totalAnimation/2) {
        pac.mouthSize -= 2;
        ++pac.mouthStart;
        ++pac.currentAnimation;
    }
    else if (pac.currentAnimation < pac.totalAnimation) {
        pac.mouthSize += 2;
        --pac.mouthStart;
        ++pac.currentAnimation;
    }
    else if (pac.currentAnimation < pac.totalAnimation + pac.idle)
        ++pac.currentAnimation;
    else
        pac.currentAnimation = 0;
}
