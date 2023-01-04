#ifndef GAMESPRITE_H
#define GAMESPRITE_H

#include "type.h"
#include <math.h>

struct sPacman {
    Position pos;
    unsigned size;
    pacMousePos triangle1;
    // couleur
    RGBAcolor color;
};

void initPacman(sPacman & pac);

#endif // GAMESPRITE_H
