#ifndef GAMESPRITE_H
#define GAMESPRITE_H

#include "type.h"
#include <math.h>

struct sPacman {
    Position pos;
    unsigned size;
    unsigned rotation;

    unsigned triangleAmount;
    unsigned mouthStart;
    unsigned mouthSize;

    //pacMousePos triangle1, triangle2, triangle3, triangle4;
    // couleur
    RGBAcolor color;
    RGBAcolor colorMouth, colorMouse2;
};

void initPacman(sPacman & pac);

#endif // GAMESPRITE_H
