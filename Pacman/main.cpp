#define FPS_LIMIT 144

#include <iostream>
#include <thread>

#include "mingl/mingl.h"

#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"

#include <random>

#include "module/type.h"

#include "module/gameSprite.h"

using namespace std;
using namespace nsShape;
using namespace nsGraphics;

void displayMat (vector<vector<unsigned>> & mat, const unsigned & caseSize, const unsigned & margeSize, MinGL & window){
    // reset fenetre
    //windowClear();
    unsigned posx;
    unsigned posy;
    for (unsigned i = 0; i < mat.size(); ++i){
        for (unsigned j = 0; j < mat[i].size(); ++j){
            posx = (j * caseSize) + margeSize;
            posy = (i * caseSize) + margeSize;
            if (mat[i][j] == 1){
                nsShape::Rectangle rect1(nsGraphics::Vec2D(posx, posy), nsGraphics::Vec2D(posx + caseSize, posy + caseSize), nsGraphics::KBlue);
                window << rect1;
            }
            if (mat[i][j] == 2){
                window << nsShape::Circle(nsGraphics::Vec2D(posx + (caseSize/2), posy + (caseSize/2)), caseSize / 15, 20, 0, 20, nsGraphics::KPurple);
            }
            if (mat[i][j] == 3){
                window << nsShape::Circle(nsGraphics::Vec2D(posx + (caseSize/2), posy + (caseSize/2)), caseSize / 10, 20, 0, 20, nsGraphics::KRed);
            }
            if (mat[i][j] == 8){
                window << nsShape::Circle(nsGraphics::Vec2D(posx + (caseSize/2), posy + (caseSize/2)), caseSize / 2, 20, 0, 20, nsGraphics::KYellow);
            }
        }
    }
}

void affPac(MinGL & window, sPacman & pacman) {
    window << Circle(Vec2D(pacman.pos.first, pacman.pos.second), pacman.size, pacman.triangleAmount, 0, pacman.triangleAmount, pacman.color);
    window << Circle(Vec2D(pacman.pos.first, pacman.pos.second),
                     pacman.size,
                     pacman.triangleAmount,
                     pacman.mouthStart-(pacman.triangleAmount/4)*pacman.rotation,
                     pacman.mouthSize,
                     pacman.colorMouth);
//    window << Triangle(Vec2D(pacman.pos.first, pacman.pos.second),
//                       Vec2D(pacman.triangle1.second.first, pacman.triangle1.second.second),
//                       Vec2D(pacman.triangle1.first.first, pacman.triangle1.first.second), pacman.colorMouse);
//    window << Triangle(Vec2D(pacman.pos.first, pacman.pos.second),
//                       Vec2D(pacman.triangle2.second.first, pacman.triangle2.second.second),
//                       Vec2D(pacman.triangle2.first.first, pacman.triangle2.first.second), pacman.colorMouse);

//    window << Triangle(Vec2D(pacman.pos.first, pacman.pos.second),
//                       Vec2D(pacman.triangle3.second.first, pacman.triangle3.second.second),
//                       Vec2D(pacman.triangle3.first.first, pacman.triangle3.first.second), pacman.colorMouse2);
//    window << Triangle(Vec2D(pacman.pos.first, pacman.pos.second),
//                       Vec2D(pacman.triangle4.second.first, pacman.triangle4.second.second),
//                       Vec2D(pacman.triangle4.first.first, pacman.triangle4.first.second), pacman.colorMouse2);
}
/*
void animPacMan (MinGL & window, unsigned & i, unsigned & move) {
    if (move> 1000) move = 0;
    if (i % 60 <= 20) {
        window << Circle(Vec2D(150+move,300), 150, KYellow);
        window << Circle(Vec2D(150+move,250), 10, KBlack);
        window << Triangle(Vec2D(150+move,300), Vec2D(293+move,250), Vec2D(300+move,300), KBlack);
        window << Triangle(Vec2D(150+move,300), Vec2D(271+move,210), Vec2D(293+move,250), KBlack);
        window << Triangle(Vec2D(150+move,300), Vec2D(293+move,350), Vec2D(300+move,300), KBlack);
        window << Triangle(Vec2D(150+move,300), Vec2D(271+move,390), Vec2D(293+move,350), KBlack);
    }
    else if (i % 60 <= 30) {
        window << Circle(Vec2D(150+move,300), 150, KYellow);
        window << Circle(Vec2D(150+move,250), 10, KBlack);
        window << Triangle(Vec2D(150+move,300), Vec2D(293+move,250), Vec2D(300+move,300), KBlack);
        window << Triangle(Vec2D(150+move,300), Vec2D(293+move,350), Vec2D(300+move,300), KBlack);
    }
    else if (i % 60 <= 50) {
        window << Circle(Vec2D(150+move,300), 150, KYellow);
        window << Circle(Vec2D(150+move,250), 10, KBlack);
    }
    else {
        window << Circle(Vec2D(150+move,300), 150, KYellow);
        window << Circle(Vec2D(150+move,250), 10, KBlack);
        window << Triangle(Vec2D(150+move,300), Vec2D(293+move,250), Vec2D(300+move,300), KBlack);
        window << Triangle(Vec2D(150+move,300), Vec2D(293+move,350), Vec2D(300+move,300), KBlack);
    }
}

void gosth(MinGL & window, const unsigned r, const unsigned g, const unsigned b, const unsigned & size) {
    window << Circle(Vec2D(600, 300), size, RGBAcolor(r,g,b));
    window << Circle(Vec2D(600 + size/6, 300 + size * 1.5), size / 6, RGBAcolor(r,g,b));
}
*/
int main()
{
    srand(time(NULL));
    // Initialise le système
    MinGL window("01 - Shapes", Vec2D(1000, 800), Vec2D(128, 128), RGBAcolor(40,40,40));
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();
    unsigned i (0);
    unsigned move (0);

    vector<vector<unsigned>> matrice =
                 {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                  {1,3,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,3,1},
                  {1,2,2,2,2,2,2,2,2,2,1,2,1,1,1,2,1,1,1,2,1},
                  {1,2,2,2,2,2,2,2,2,2,1,2,1,2,2,2,1,2,2,2,1},
                  {1,2,2,2,2,2,2,2,2,2,2,2,1,2,1,2,1,2,2,1,1},
                  {1,2,2,2,2,2,2,2,2,2,1,2,1,2,1,2,1,2,2,1,1},
                  {1,2,2,2,2,2,2,2,2,2,1,2,2,2,1,2,2,2,2,1,1},
                  {1,2,2,2,2,2,2,2,1,1,1,1,1,2,1,1,1,1,2,1,1},
                  {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1},
                  {1,2,2,2,2,1,1,2,1,1,2,1,1,2,1,1,2,1,2,2,0},
                  {0,2,2,2,2,2,1,2,1,0,9,0,1,2,1,2,2,1,1,1,1},
                  {1,2,2,2,2,1,1,2,1,1,1,1,1,2,1,1,2,1,2,2,0},
                  {1,2,2,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,2,1,1},
                  {1,2,2,2,1,1,1,1,1,2,1,2,1,1,1,1,1,1,2,1,1},
                  {1,2,2,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,2,1,1},
                  {1,2,2,2,2,2,1,2,1,1,1,1,1,2,1,2,1,1,2,1,1},
                  {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,1,1},
                  {1,2,2,2,2,2,2,2,2,2,2,2,1,1,1,2,1,2,2,2,1},
                  {1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,2,1,2,1},
                  {1,3,2,2,2,2,2,2,2,2,8,2,2,2,2,2,2,2,2,3,1},
                  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

    sPacman pac1;
    initPacman(pac1);
    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // On dessine les formes géométriques
        /*
        animPacMan(window, i, move);
        gosth(window, 190, 25, 40, 150);
        */
        affPac(window, pac1);
        displayMat(matrice,30, 50, window);

        ++i;
        move += 3;
        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }

    return 0;
}
