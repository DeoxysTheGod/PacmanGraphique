#define FPS_LIMIT 36

#include <iostream>
#include <thread>

#include "mingl/mingl.h"
#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/gui/text.h"
#include "mingl/gui/glut_font.h"

#include <random>
#include <string>

#include "module/type.h"
#include "module/gameSprite.h"
#include "module/movement.h"
#include "module/score.h"
#include "module/convertImgMat.h"

using namespace std;
using namespace nsShape;
using namespace nsGraphics;

void displayMat (UIntMat & mat, const unsigned & caseSize, const unsigned & margeSize, MinGL & window, sPacman & pacman, sGhost & ghost);
void randomPlot (UIntMat & mat, const plotHolder & allPlot);
void affPac(MinGL & window, sPacman & pacman);
void affGhost(MinGL & window, sGhost & ghost);
void isKeyPressed (MinGL & window, char & pressedKey);
void isKeyPressedGhost (MinGL & window, char & pressedKey);
void partialReset (const plotHolder & allPlot, UIntMat & mat, char & pressedKeyPacman, char & pressedKeyGhost, sPacman & pac, sGhost & ghost, const unsigned & caseSize);
unsigned countBeignet (const UIntMat & mat);


void displayMat (UIntMat & mat, const unsigned & caseSize, const unsigned & margeSize, MinGL & window, sPacman & pacman, sGhost & ghost) {
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
            else if (mat[i][j] == 5){
                nsShape::Rectangle rect1(nsGraphics::Vec2D(posx, posy), nsGraphics::Vec2D(posx + caseSize, posy + caseSize), nsGraphics::KBlueGhostWall);
                window << rect1;
            }
            else if (mat[i][j] == 2){
                window << nsShape::Circle(nsGraphics::Vec2D(posx + (caseSize/2), posy + (caseSize/2)), caseSize / 15, 20, 0, 20, nsGraphics::KBeige);
            }
            else if (mat[i][j] == 3){
                window << nsShape::Circle(nsGraphics::Vec2D(posx + (caseSize/2), posy + (caseSize/2)), caseSize / 5, 20, 0, 20, nsGraphics::KBeige);
            }
            else if (mat[i][j] == 8){
                pacman.posMat = {i, j};
                if (pacman.cooldown == 0) {
                    pacman.pos.first = posx + (caseSize/2);
                    pacman.pos.second = posy + (caseSize/2);
                }
            }
            else if (mat[i][j] == 9){
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

void partialReset (const plotHolder & allPlot, UIntMat & mat, char & pressedKeyPacman, char & pressedKeyGhost, sPacman & pac, sGhost & ghost, const unsigned & caseSize) {
    pressedKeyGhost = 'p';
    ghost.currentMove = 'p';
    ghost.lastMove = 'p';

    if (!pac.canEat) {
        pressedKeyPacman = 'p';
        pac.currentMove = 'p';
        pac.lastMove = 'p';

        mat[pac.initialPos.first][pac.initialPos.second] = 8;
        pac.currentAnimation = pac.totalAnimation;

        --pac.stock;
    }
    else
        pac.score += 200;

    if (pac.canEat)
        ghost.previousCase = 8;
    else
        ghost.previousCase = 0;
    mat[ghost.posMat.first][ghost.posMat.second] = ghost.previousCase;
    ghost.previousCase = 0;
    mat[ghost.initialPos.first][ghost.initialPos.second] = 9;

    ghost.hitPacman = false;
    pac.hitGhost = false;
    if (pac.stock == 0 || pac.beignetToEat == 0) {
        initPacman(pac, caseSize);
        initGhost(ghost, caseSize);
        if (pac.stock == 0)
            pac.score = 0;
        pac.stock = 3;
        randomPlot(mat, allPlot);
        pac.beignetToEat = countBeignet (mat);
        pac.initialPosNotInit = true;
    }
}

void randomPlot (UIntMat & mat, const plotHolder & allPlot) {
    unsigned maxRand = allPlot.size();
    mat = allPlot.find(rand()%maxRand+1)->second;
}

unsigned countBeignet (const UIntMat & mat) {
    unsigned cpt (0);
    for (auto & i : mat) {
        for (auto & j : i) {
            if (j == 2 || j == 3 || j == 4)
                ++cpt;
        }
    }
    return cpt;
}

void affPos (const Position & pos) {
    cout << "(" << pos.first << ", " << pos.second << ")" << endl;
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
    unsigned caseSize = 30;
    unsigned margin = 50;
    string scoreStr, stockStr;
    char pressedKey = 'p';
    char pressedKeyGhost = 'p';
    sPacman pac1;
    sGhost ghost1;

    UIntMat matrice;

    plotHolder allPlot;
    importAllPlot(allPlot, "map");
    randomPlot (matrice, allPlot);
    pac1.beignetToEat = countBeignet (matrice);

    initPacman(pac1, caseSize);
    initGhost(ghost1, caseSize);

    pac1.fps = FPS_LIMIT;
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

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // affiche la grille de jeu
        displayMat(matrice, caseSize, margin, window, pac1, ghost1);
        if (pac1.initialPosNotInit) {
            pac1.initialPos = pac1.posMat;
            ghost1.initialPos = ghost1.posMat;
            pac1.initialPosNotInit = false;
        }
        affPos(pac1.initialPos);
        affPos(ghost1.initialPos);

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

        if (ghost1.hitPacman || pac1.hitGhost || pac1.beignetToEat == 0) {
            partialReset(allPlot, matrice, pressedKey, pressedKeyGhost, pac1, ghost1, caseSize);
        }

        // score
        majATH(scoreStr, stockStr, pac1);
        window << nsGui::Text(Vec2D(margin,margin-10), scoreStr, KWhite, nsGui::GlutFont::BITMAP_HELVETICA_18);
        window << nsGui::Text(Vec2D(margin + (matrice[0].size()-1) * caseSize,margin-10), stockStr, KWhite, nsGui::GlutFont::BITMAP_HELVETICA_18);

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
