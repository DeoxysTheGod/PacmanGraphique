#include "gameSprite.h"

using namespace std;
using namespace nsShape;
using namespace nsGraphics;

void initPacman(sPacman & pac, const unsigned caseSize) {
    pac.pos = {200, 200};
    pac.posMat = {1,1};
    pac.triangleAmount = 40;
    pac.size = caseSize/2.5;
    pac.rotation = 0;

    // Bouche du pacman
    pac.mouthSize = pac.triangleAmount/5;
    pac.mouthStart = pac.triangleAmount-pac.mouthSize/2;

    // couleur
    pac.color = KYellow;
    pac.mouthColor = KBlack;
}

void initGhost(sGhost & ghost, const unsigned caseSize) {
    ghost.pos = {200, 200};
    ghost.triangleAmount = 40;
    ghost.size = caseSize/3;
    ghost.rotation = 0;

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
}

void majGhostSpritePos(sGhost & ghost) {
    ghost.rightEyePos = {ghost.pos.first - ghost.size/2.2, ghost.pos.second};
    ghost.leftEyePos = {ghost.pos.first + ghost.size/2.2, ghost.pos.second};
    ghost.wavePos = {(ghost.pos.first-ghost.size)+ghost.waveSize, ghost.pos.second+ghost.size};
}
