#define FPS_LIMIT 36

#include <iostream>
#include <thread>

#include "mingl/mingl.h"

#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/gui/text.h"
#include "mingl/gui/glut_font.h"
//#include "mingl/shape/line.h"
//#include "mingl/shape/triangle.h"

#include <random>
#include <string>
#include "module/type.h"
#include "module/gameSprite.h"
#include "module/movement.h"
#include "module/score.h"
#include "module/convertImgMat.h"
#include "module/remplissageMat.h"

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
                ghost.posMat = {i, j};
                if (ghost.cooldown == 0) {
                    ghost.pos.first = posx + (caseSize/2);
                    ghost.pos.second = posy + (caseSize/2);
                }
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
    if (window.isPressed({'o', false}))
        pressedKey = 'o';
    else if (window.isPressed({'l', false}))
        pressedKey = 'l';
    else if (window.isPressed({'k', false}))
        pressedKey = 'k';
    else if (window.isPressed({'m', false}))
        pressedKey = 'm';
}

void partialReset (UIntMat & mat, char & pressedKeyPacman, char & pressedKeyGhost, sPacman & pac, sGhost & ghost) {
    pressedKeyGhost = 'p';
    ghost.currentMove = 'p';
    ghost.lastMove = 'p';

    if (pac.canEat)
        ghost.previousCase = 8;
    else
        ghost.previousCase = 0;
    mat[ghost.posMat.first][ghost.posMat.second] = ghost.previousCase;
    mat[ghost.initialPos.first][ghost.initialPos.second] = 9;
    ghost.posMat = ghost.initialPos;

    if (!pac.canEat) {
        pressedKeyPacman = 'p';
        pac.currentMove = 'p';
        pac.lastMove = 'p';

        mat[pac.posMat.first][pac.posMat.second] = 0;
        mat[pac.initialPos.first][pac.initialPos.second] = 8;
        pac.posMat = pac.initialPos;
        pac.currentAnimation = pac.totalAnimation;

        --pac.stock;
    }
    else
        pac.score += 200;

    ghost.hitPacman = false;
    pac.hitGhost = false;
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

    // initialisation des sprites
    unsigned caseSize = 24;
    unsigned margin = 50;
    string scoreStr, stockStr;
    char pressedKey = 'p';
    char pressedKeyGhost = 'p';
    sPacman pac1;
    sGhost ghost1;
    initPacman(pac1, caseSize);
    initGhost(ghost1, caseSize);
/*
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
*/
    UIntMat matrice;
    matrice = convertMat("../Pacman/carte/map2.ppm");
    affMat(matrice);
    //fillMat(matrice);

    //affMat(matrice);

    displayMat(matrice, caseSize, margin, window, pac1, ghost1);
    pac1.initialPos = pac1.posMat;
    pac1.fps = FPS_LIMIT;
    ghost1.initialPos = ghost1.posMat;

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // affiche la grille de jeu
        displayMat(matrice, caseSize, margin, window, pac1, ghost1);

        affPac(window, pac1);
        majGhostSpritePos(ghost1);
        affGhost(window, ghost1);

        // Mouvements
        isKeyPressed(window, pressedKey);
        isKeyPressedGhost(window, pressedKeyGhost);

        if (pac1.canEat) {
            ghost1.speed = 2;
            ghost1.color = KBlue;
        }
        else {
            ghost1.speed = ghost1.baseSpeed;
            ghost1.color = KRed;
        }
        movementDirection(matrice, pressedKey, pac1, caseSize);
        movementDirectionGhost(matrice, pressedKeyGhost, ghost1, caseSize);

        if (ghost1.hitPacman || pac1.hitGhost) {
            partialReset(matrice, pressedKey, pressedKeyGhost, pac1, ghost1);
        }

        // score
        majATH(scoreStr, stockStr, pac1);
        window << nsGui::Text(Vec2D(margin,margin-10), scoreStr, KWhite, nsGui::GlutFont::BITMAP_HELVETICA_18);
        window << nsGui::Text(Vec2D(margin + (matrice.size()-1) * caseSize,margin-10), stockStr, KWhite, nsGui::GlutFont::BITMAP_HELVETICA_18);

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
