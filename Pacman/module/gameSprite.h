#ifndef GAMESPRITE_H
#define GAMESPRITE_H

#include "type.h"
#include <math.h>

struct sPacman {
    Position pos;
    unsigned size = 10;
    unsigned rotation;

    unsigned triangleAmount;
    unsigned mouthStart;
    unsigned mouthSize;

    //pacMousePos triangle1, triangle2, triangle3, triangle4;
    // couleur
    RGBAcolor color;
    RGBAcolor mouthColor;
};

struct sGhost {
    Position pos;
    Position rightEyePos, leftEyePos;
    unsigned size = 10;
    unsigned rotation = 0;

    unsigned triangleAmount;
    unsigned eyeSize, pupilSize;

    RGBAcolor color, eyeColor, pupilColor;

    unsigned previousCase = 0;
};

void initPacman(sPacman & pac);

void initGhost(sGhost & ghost);

void majGhostSpritePos(sGhost & ghost);

#endif // GAMESPRITE_H
