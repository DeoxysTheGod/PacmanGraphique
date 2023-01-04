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

void affPac(MinGL & window, sPacman & pacman) {
    window << Circle(Vec2D(pacman.pos.first, pacman.pos.second), pacman.size, pacman.color);
    window << Triangle(Vec2D(pacman.pos.first, pacman.pos.second),
                       Vec2D(pacman.triangle1.first.first, pacman.triangle1.first.second),
                       Vec2D(pacman.triangle1.second.first, pacman.triangle1.second.second), KRed);
}

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
