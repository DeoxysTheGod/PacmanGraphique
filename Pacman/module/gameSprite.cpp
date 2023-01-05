#include "gameSprite.h"
#include <iostream>

using namespace std;
using namespace nsShape;
using namespace nsGraphics;

void initPacman(sPacman & pac) {
    pac.pos = {200, 200};
    pac.triangleAmount = 40;
    pac.rotation = 0;

    // Bouche du pacman
    pac.mouthSize = pac.triangleAmount/5;
    pac.mouthStart = pac.triangleAmount-pac.mouthSize/2;

    // couleur
    pac.color = KYellow;
    pac.mouthColor = KBlack;
}

void initGhost(sGhost & ghost) {
    ghost.pos = {200, 200};
    ghost.size = 100;
    ghost.triangleAmount = 40;
    ghost.rotation = 0;

    // Yeux du ghost
    ghost.eyeSize = ghost.size/2.8;
    ghost.pupilSize = ghost.size/7;
    ghost.rightEyePos = {ghost.pos.first - ghost.size/2.5, ghost.pos.second};
    ghost.leftEyePos = {ghost.pos.first + ghost.size/2.5, ghost.pos.second};

    // couleur
    ghost.color = KRed;
    ghost.eyeColor = KWhite;
    ghost.pupilColor = KLightBlue;
}
