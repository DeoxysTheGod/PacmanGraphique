#ifndef GAMESPRITE_H
#define GAMESPRITE_H

#include "type.h"
#include <math.h>

struct sPacman {
    Position pos, posMat;
    unsigned size;
    unsigned rotation;

    unsigned cooldown;

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
    unsigned size;
    unsigned rotation = 0;

    unsigned triangleAmount;
    unsigned eyeSize, pupilSize;

    Position wavePos;
    unsigned nbWave, waveSize;

    RGBAcolor color, eyeColor, pupilColor;

    unsigned previousCase = 0;
};

void initPacman(sPacman & pac, const unsigned caseSize);

void initGhost(sGhost & ghost, const unsigned caseSize);

void moveStop(sPacman & pac);

void majGhostSpritePos(sGhost & ghost);

#endif // GAMESPRITE_H
