#include "gameSprite.h"
#include "parameters.h"

using namespace std;
using namespace nsShape;
using namespace nsGraphics;

void initPacman(sPacman & pac, const unsigned caseSize) {
    pac.pos = {200, 200};
    pac.posMat = {1,1};
    pac.triangleAmount = 40;
    pac.size = caseSize/2.5;
    pac.rotation = 0;
    pac.score = 0;

    pac.speed = 3;
    pac.currentMove = 'p';
    pac.lastMove = 'p';

    // cooldown
    pac.cooldown = 0;

    // Bouche du pacman
    pac.mouthSize = pac.triangleAmount/5;
    pac.mouthStart = pac.triangleAmount-pac.mouthSize/2;

    // couleur
    pac.color = KYellow;
    pac.mouthColor = KBlack;

    // touches
    loadParameter (pac, pac.authKey);
}

void initGhost(sGhost & ghost, const unsigned caseSize) {
    ghost.pos = {200, 200};
    ghost.posMat = {1,1};
    ghost.triangleAmount = 40;
    ghost.size = caseSize/3;

    // mouvements
    ghost.lastMove = 'p';
    ghost.currentMove = 'p';
    ghost.speed = 3;

    // cooldown
    ghost.cooldown = 0;

    // Yeux du ghost
    ghost.eyeSize = ghost.size/3;
    ghost.pupilSize = ghost.size/6;
    ghost.rightEyePos = {ghost.pos.first - ghost.size/2, ghost.pos.second};
    ghost.leftEyePos = {ghost.pos.first + ghost.size/2, ghost.pos.second};

    // Vague
    ghost.nbWave = 3;
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
