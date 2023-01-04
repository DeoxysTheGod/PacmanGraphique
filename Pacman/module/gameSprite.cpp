#include "gameSprite.h"

void initPacman(sPacman & pac) {
    pac.pos = {200, 200};
    pac.size = 150;
    pac.triangleAmount = 40;
    pac.rotation = 0;

    // Bouche du pacman
    pac.mouthSize = pac.triangleAmount/5;
    pac.mouthStart = pac.triangleAmount-pac.mouthSize/2;

    // bouche
//    float pi = 3.141592654;
//    double triangleIsoBaseSize = (cos(81*pi/180)*pac.size)*2;
//    unsigned decTriangleX1 = triangleIsoBaseSize * cos(81*pi/180);
//    unsigned decTriangleY1 = triangleIsoBaseSize * cos(9*pi/180);
//    unsigned decTriangleX2 = triangleIsoBaseSize * cos(72*pi/180) + decTriangleX1;
//    unsigned decTriangleY2 = triangleIsoBaseSize * cos(18*pi/180) + decTriangleY1;
//    cout << decTriangleX2 << ", " << decTriangleY2 << ", " << triangleIsoBaseSize<< endl;

//    pac.triangle1 = {{pac.pos.first + pac.size, pac.pos.second}, {pac.pos.first+pac.size-decTriangleX1, pac.pos.second-decTriangleY1}};
//    pac.triangle2 = {{pac.pos.first + pac.size, pac.pos.second}, {pac.pos.first+pac.size-decTriangleX1, pac.pos.second+decTriangleY1}};
//    pac.triangle3 = {{pac.pos.first+pac.size-decTriangleX1, pac.pos.second-decTriangleY1}, {pac.pos.first+pac.size-decTriangleX2, pac.pos.second-decTriangleY2}};
//    pac.triangle4 = {{pac.pos.first+pac.size-decTriangleX1, pac.pos.second+decTriangleY1}, {pac.pos.first+pac.size-decTriangleX2, pac.pos.second+decTriangleY2}};

    // couleur
    pac.color = KYellow;
    pac.colorMouth = KBlack;
}
