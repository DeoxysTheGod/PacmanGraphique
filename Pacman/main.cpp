#define FPS_LIMIT 36

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

void displayMat (vector<vector<unsigned>> & mat, const unsigned & caseSize, const unsigned & margeSize, MinGL & window, sPacman & pacman, sGhost & ghost)
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

bool caseExist (const vector<vector<unsigned>> & mat, const Position & pos){
    return (((0<=pos.first) && (pos.first<mat[0].size()) && (0<=pos.second) && (pos.second<mat.size())) && (mat[pos.first][pos.second] != 1));
}

void tp (vector<vector<unsigned>> & mat, Position & pos){
    if (pos.first == 0)
        pos.first = mat.size() -2;
    else if (pos.first == mat.size() -2)
        pos.first = 1;
    else if (pos.second == 0)
        pos.second = mat.size() -2;
    else if (pos.second == mat.size() -2)
        pos.second = 1;
}

void move (vector<vector<unsigned>> & mat, Position & posStart, Position & posEnd){
    cout << posEnd.first << ", " << posEnd.second << "->" << mat[posEnd.first][posEnd.second] <<  endl;
    if (mat[posEnd.first][posEnd.second] == 7)
       tp(mat, posEnd);
    mat[posEnd.first][posEnd.second] = mat[posStart.first][posStart.second];
    mat[posStart.first][posStart.second] = 0;
    posStart.first = posEnd.first;
    posStart.second = posEnd.second;
}

void move (vector<vector<unsigned>> & mat, pair<unsigned,unsigned> & posStart, pair<unsigned,unsigned> & posEnd, unsigned & previousCase)
{
    unsigned tmp = mat[posEnd.first][posEnd.second];
    mat[posEnd.first][posEnd.second] = mat[posStart.first][posStart.second];
    mat[posStart.first][posStart.second] = previousCase;
    previousCase = tmp;
    posStart.first = posEnd.first;
    posStart.second = posEnd.second;
}


void addScore (const vector<vector<unsigned>> & mat, const Position & pos, unsigned & score){
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



int main()
{
    srand(time(NULL));
    // Initialise le système
    MinGL window("Pacman", Vec2D(1000, 1000), Vec2D(128, 128), RGBAcolor(0,0,0));
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    vector<vector<unsigned>> matrice =
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
    sPacman pac1;
    sGhost ghost1;
    initPacman(pac1, caseSize);
    initGhost(ghost1, caseSize);

    chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

    //displayMat(matFirst,window);

    // On finit la frame en cours
    window.finishFrame();

    // On vide la queue d'évènements
    window.getEventManager().clearEvents();

    // On attend un peu pour limiter le framerate et soulager le CPU
    this_thread::sleep_for(chrono::milliseconds(100 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

    // On récupère le temps de frame
    frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    // On efface la fenêtre
    window.clearScreen();

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        // affiche la grille de jeu
        displayMat(matrice,caseSize, 50, window, pac1, ghost1);

        affPac(window, pac1);
        majGhostSpritePos(ghost1);
        affGhost(window, ghost1);

        if (window.isPressed({'z', false}))
            pressedKey = 'z';
        if (window.isPressed({'s', false}))
            pressedKey = 's';
        if (window.isPressed({'q', false}))
            pressedKey = 'q';
        if (window.isPressed({'d', false}))
            pressedKey = 'd';

        if ((pac1.currentMove == 'p') && pressedKey == 'z'){
            if (pac1.cooldown == 0 && caseExist(matrice, {pac1.posMat.first-1, pac1.posMat.second})) {
                pac1.rotation = 1;
                pac1.currentMove = 'z';
                pac1.cooldown = FPS_LIMIT;
                pac1.baseCooldown = pac1.cooldown;
            }
        }
        if (pac1.currentMove =='z' && pac1.cooldown == 1) {
            pac1.nextPos = {pac1.posMat.first-1, pac1.posMat.second};
            move(matrice, pac1.posMat, pac1.nextPos);
            pac1.currentMove = 'p';
            pac1.cooldown = 0;
        }

        if (pac1.currentMove =='z' && pac1.cooldown != 0) {
            pac1.pos = {pac1.pos.first, pac1.pos.second-1};
            --pac1.cooldown;
        }

        if ((pac1.currentMove == 'p') && pressedKey == 's'){
            if (pac1.cooldown == 0 && caseExist(matrice, {pac1.posMat.first+1, pac1.posMat.second})){
                pac1.rotation = 3;
                pac1.currentMove = 's';
                pac1.cooldown = FPS_LIMIT;
                pac1.baseCooldown = pac1.cooldown;
            }
        }
        if (pac1.currentMove =='s' && pac1.cooldown == 1) {
            pac1.nextPos = {pac1.posMat.first+1, pac1.posMat.second};
            move(matrice, pac1.posMat, pac1.nextPos);
            pac1.currentMove = 'p';
            pac1.cooldown = 0;
        }

        if (pac1.currentMove =='s' && pac1.cooldown != 0) {
            pac1.pos = {pac1.pos.first, pac1.pos.second+1};
            --pac1.cooldown;
        }

        if ((pac1.currentMove == 'p') && pressedKey == 'q'){
            if (pac1.cooldown == 0 && caseExist(matrice, {pac1.posMat.first, pac1.posMat.second-1})){
                pac1.rotation = 2;
                pac1.currentMove = 'q';
                pac1.cooldown = FPS_LIMIT;
                pac1.baseCooldown = pac1.cooldown;
            }
        }
        if (pac1.currentMove =='q' && pac1.cooldown == 1) {
            pac1.nextPos = {pac1.posMat.first, pac1.posMat.second-1};
            move(matrice, pac1.posMat, pac1.nextPos);
            pac1.currentMove = 'p';
            pac1.cooldown = 0;
        }

        if (pac1.currentMove =='q' && pac1.cooldown != 0) {
            pac1.pos = {pac1.pos.first-1, pac1.pos.second};
            --pac1.cooldown;
        }

        if ((pac1.currentMove == 'p') && pressedKey == 'd'){
            if (pac1.cooldown == 0 && caseExist(matrice, {pac1.posMat.first, pac1.posMat.second+1})){
                pac1.rotation = 0;
                pac1.currentMove = 'd';
                pac1.cooldown = FPS_LIMIT;
                pac1.baseCooldown = pac1.cooldown;
            }
        }
        if (pac1.currentMove == 'd' && pac1.cooldown == 1) {
            pac1.nextPos = {pac1.posMat.first, pac1.posMat.second+1};
            move(matrice, pac1.posMat, pac1.nextPos);
            pac1.currentMove = 'p';
            pac1.cooldown = 0;
        }

        if (pac1.currentMove =='d' && pac1.cooldown != 0) {
            pac1.pos = {pac1.pos.first+1, pac1.pos.second};
            --pac1.cooldown;
        }
        //cout << pac1.posMat.first << ", " << pac1.posMat.second << " -> " << pac1.currentMove << endl;

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
