#define FPS_LIMIT 144

#include <iostream>
#include <thread>

#include "mingl/mingl.h"

#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"

//#include "mingl/shape/line.h"
//#include "mingl/shape/triangle.h"

#include <random>

#include "module/type.h"
#include "module/gameSprite.h"
#include "module/movement.h"
//#include "module/convertImgMat.h"

using namespace std;
using namespace nsShape;
using namespace nsGraphics;

void displayMat (UIntMat & mat, const unsigned & caseSize, const unsigned & margeSize, MinGL & window, sPacman & pacman, sGhost & ghost)
{
    // reset fenetre
    //windowClear();
    unsigned posx;
    unsigned posy;
    for (unsigned i = 0; i < mat.size(); ++i){
        for (unsigned j = 0; j < mat[i].size(); ++j){
            posx = (j * caseSize) + margeSize;
            posy = (i * caseSize) + margeSize;
            if (mat[i][j] == 1){
                nsShape::Rectangle rect1(nsGraphics::Vec2D(posx, posy), nsGraphics::Vec2D(posx + caseSize, posy + caseSize), nsGraphics::KBlueWall);
                window << rect1;
            }
            if (mat[i][j] == 2){
                window << nsShape::Circle(nsGraphics::Vec2D(posx + (caseSize/2), posy + (caseSize/2)), caseSize / 15, 20, 0, 20, nsGraphics::KBeige);
            }
            if (mat[i][j] == 3){
                window << nsShape::Circle(nsGraphics::Vec2D(posx + (caseSize/2), posy + (caseSize/2)), caseSize / 5, 20, 0, 20, nsGraphics::KBeige);
            }
            if (mat[i][j] == 8){
                pacman.posMat = {i, j};
                if (pacman.cooldown == 0) {
                    pacman.pos.first = posx + (caseSize/2);
                    pacman.pos.second = posy + (caseSize/2);
                }
//                window << nsShape::Circle(nsGraphics::Vec2D(posx + (caseSize/2), posy + (caseSize/2)), caseSize / 2, 20, 0, 20, nsGraphics::KYellow);
            }
            if (mat[i][j] == 9){
                ghost.pos.first = posx + (caseSize/2);
                ghost.pos.second = posy + (caseSize/2);
            }
        }
    }
}

template<typename T>
void affMat (vector<vector<T>> & mat) {
    for (auto & i : mat) {
        for (auto & j : i)
            cout << j;
        cout << endl;
    }

}

void affPac(MinGL & window, sPacman & pacman) {
    window << Circle(Vec2D(pacman.pos.first, pacman.pos.second), pacman.size, pacman.triangleAmount, 0, pacman.triangleAmount, pacman.color);
    window << Circle(Vec2D(pacman.pos.first, pacman.pos.second),
                     pacman.size,
                     pacman.triangleAmount,
                     pacman.mouthStart-(pacman.triangleAmount/4)*pacman.rotation,
                     pacman.mouthSize,
                     pacman.mouthColor);
}

void affGhost(MinGL & window, sGhost & ghost) {
    // tete
    window << Circle(Vec2D(ghost.pos.first, ghost.pos.second), ghost.size, ghost.triangleAmount, 0, ghost.triangleAmount, ghost.color);
    // jointure entre tete et vague
    window << Rectangle(Vec2D(ghost.pos.first+ghost.size, ghost.pos.second), Vec2D(ghost.pos.first-ghost.size, ghost.wavePos.second), ghost.color);
    // yeux
    window << Circle(Vec2D(ghost.rightEyePos.first, ghost.rightEyePos.second), ghost.eyeSize, ghost.triangleAmount, 0, ghost.triangleAmount, ghost.eyeColor);
    window << Circle(Vec2D(ghost.leftEyePos.first, ghost.leftEyePos.second), ghost.eyeSize, ghost.triangleAmount, 0, ghost.triangleAmount, ghost.eyeColor);
    window << Circle(Vec2D(ghost.rightEyePos.first, ghost.rightEyePos.second), ghost.pupilSize, ghost.triangleAmount, 0, ghost.triangleAmount, ghost.pupilColor);
    window << Circle(Vec2D(ghost.leftEyePos.first, ghost.leftEyePos.second), ghost.pupilSize, ghost.triangleAmount, 0, ghost.triangleAmount, ghost.pupilColor);
    // vague
    for (unsigned i (0) ; i < ghost.nbWave ; ++i) {
        window << Circle(Vec2D(ghost.wavePos.first+i*ghost.waveSize*2, ghost.wavePos.second), ghost.waveSize, ghost.triangleAmount, 0, ghost.triangleAmount, ghost.color);
        //cout << ghost.size << ", " << ghost.waveSize << endl;
    }
}


bool getHit (sGhost & ghost){
    return ghost.previousCase == '8';
}

void addScore (const UIntMat & mat, const Position & pos, unsigned & score){
    if (mat[pos.first][pos.second] == 2){
        score += 10;
    }
    else if (mat[pos.first][pos.second] == 3){
        score += 50;
    }
    else if (mat[pos.first][pos.second] ==  4){
        score += 100;
    }
}

void isKeyPressed (MinGL & window, char & pressedKey) {
    if (window.isPressed({'z', false}))
        pressedKey = 'z';
    else if (window.isPressed({'s', false}))
        pressedKey = 's';
    else if (window.isPressed({'q', false}))
        pressedKey = 'q';
    else if (window.isPressed({'d', false}))
        pressedKey = 'd';
}

void isKeyPressedGhost (MinGL & window, char & pressedKey) {
    if (window.isPressed({'8', false}))
        pressedKey = '8';
    else if (window.isPressed({'5', false}))
        pressedKey = '5';
    else if (window.isPressed({'4', false}))
        pressedKey = '4';
    else if (window.isPressed({'6', false}))
        pressedKey = '6';
}

int main()
{
    srand(time(NULL));
    // Initialise le système
    MinGL window("Pacman", Vec2D(1000, 1000), Vec2D(128, 128), RGBAcolor(0,0,0));
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    UIntMat matrice =
                 {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                  {1,3,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,3,1},
                  {1,2,1,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,2,1},
                  {1,2,2,2,1,2,2,2,1,2,1,2,1,2,2,2,1,2,2,2,1},
                  {1,1,2,2,1,2,1,2,1,2,2,2,1,2,1,2,1,2,2,1,1},
                  {1,1,2,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,2,1,1},
                  {1,1,2,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,2,1,1},
                  {1,1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1,1},
                  {1,1,2,2,2,2,2,0,0,0,0,0,0,0,2,2,2,2,2,1,1},
                  {7,2,2,1,2,1,1,0,1,1,0,1,1,0,1,1,2,1,2,2,7},
                  {1,1,1,1,2,2,1,0,1,0,9,0,1,0,1,2,2,1,1,1,1},
                  {7,2,2,1,2,1,1,0,1,1,1,1,1,0,1,1,2,1,2,2,7},
                  {1,1,2,2,2,2,1,0,0,0,0,0,0,0,1,2,2,2,2,1,1},
                  {1,1,2,1,1,1,1,1,1,2,1,2,1,1,1,1,1,1,2,1,1},
                  {1,1,2,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,2,1,1},
                  {1,1,2,1,1,2,1,2,1,1,1,1,1,2,1,2,1,1,2,1,1},
                  {1,1,2,2,1,2,2,2,2,2,2,2,2,2,2,2,1,2,2,1,1},
                  {1,2,2,2,1,2,1,1,1,1,2,1,1,1,1,2,1,2,2,2,1},
                  {1,2,1,2,1,2,1,2,2,2,2,2,2,2,1,2,1,2,1,2,1},
                  {1,3,2,2,2,2,2,2,2,2,8,2,2,2,2,2,2,2,2,3,1},
                  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

    // initialisation des sprites
    unsigned caseSize = 36;
    char pressedKey = 'p';
    char pressedKeyGhost = 'p';
    sPacman pac1;
    sGhost ghost1;
    initPacman(pac1, caseSize);
    initGhost(ghost1, caseSize);

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // affiche la grille de jeu
        displayMat(matrice, caseSize, 50, window, pac1, ghost1);

        affPac(window, pac1);
        majGhostSpritePos(ghost1);
        affGhost(window, ghost1);

        // Mouvements
        isKeyPressed(window, pressedKey);
        isKeyPressedGhost(window, pressedKeyGhost);

        movementDirection(matrice, pressedKey, pac1, caseSize);
        movementDirectionGhost(matrice, pressedKeyGhost, ghost1, caseSize);

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
