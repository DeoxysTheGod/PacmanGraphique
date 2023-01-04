#include "gameSprite.h"

void initPacman(sPacman & pac) {
    pac.pos = {60, 60};
    pac.size = 50;

    // bouche
    double triangleIsoBaseSize = (sin(18)*10)/sin(81);
    double triangleX = triangleIsoBaseSize * sin(126);
    double triangleY = triangleIsoBaseSize * sin(9);
    pac.triangle1 = {{pac.pos.first + pac.size, pac.pos.second}, {pac.pos.first+pac.size-unsigned(triangleX), pac.pos.second+pac.size-unsigned(triangleY)}};
    // couleur
    pac.color = KYellow;
}
