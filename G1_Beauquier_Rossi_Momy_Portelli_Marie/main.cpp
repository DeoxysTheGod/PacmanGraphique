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

/*!
 * \brief displayMat : lit la matrice et affiche à l'écran les objets correspondant à la position correspondante
 * \param[in] mat : la grille de jeu
 * \param[in] caseSize : taille fictive d'une case à l'écran
 * \param[in] margeSize : décalage de la grille
 * \param window : la fenêtre dans laquelle il faut afficher les formes
 * \param[in_out] pacman : le pacman à modifier
 * \param[in_out] ghost : le fantome à modifier
 * @fn void displayMat (UIntMat & mat, const unsigned & caseSize, const unsigned & margeSize, MinGL & window, sPacman & pacman, sGhost & ghost);
 */
void displayMat (const UIntMat & mat, const unsigned & caseSize, const unsigned & margeSize, MinGL & window, sPacman & pacman, sGhost & ghost);

/*!
 * \brief affPac : affiche toutes les forme pour faire le pacman
 * \param window : la fenêtre dans laquelle il faut afficher pacman
 * \param pacman : le pacman à afficher
 * @fn void affPac(MinGL & window, sPacman & pacman);
 */
void affPac(MinGL & window, sPacman & pacman);

/*!
 * \brief affGhost : affiche toutes les forme pour faire le fantome
 * \param window : la fenêtre dans laquelle il faut afficher le fantome
 * \param pacman : le fantome à afficher
 * @fn void affGhost(MinGL & window, sGhost & fantome);
 */
void affGhost(MinGL & window, sGhost & ghost);

/*!
 * \brief isKeyPressed : détecte les touches préssées
 * \param window : la fenêtre concernée
 * \param[in_out] pressedKey : la touche préssée
 * \param[in] pac : le pacman concerné pour récupérer ses touches
 * @fn void isKeyPressed (MinGL & window, char & pressedKey, const sPacman & pac);
 */
void isKeyPressed (MinGL & window, char & pressedKey, const sPacman & pac);

/*!
 * \brief isKeyPressedGhost : détecte les touches préssées
 * \param window : la fenêtre concernée
 * \param[in_out] pressedKey : la touche préssée
 * \param[in] ghost : le fantome concerné pour récupérer ses touches
 * @fn void isKeyPressedGhost (MinGL & window, char & pressedKey, const sGhost & ghost);
 */
void isKeyPressedGhost (MinGL & window, char & pressedKey, const sGhost & ghost);

/*!
 * \brief partialReset : permet de réinitialiser toutes les valeurs en cas de contact entre le fantome et pacman
 * ou lors d'une victoire ou défaite
 * \param[in] allPlot : toutes les grilles de jeu
 * \param[in_out] mat : la grille de jeu actuelle et futur en cas de reset total
 * \param[out] pressedKeyPacman : touche préssée du pacman pour les réinitialiser
 * \param[out] pressedKeyGhost : touche préssée du fantome pour les réinitialiser
 * \param[in_out] pac : le pacman concerné
 * \param[in_out] ghost : le fantome concerné
 * \param[in] caseSize : taille fictive d'une case
 * @fn void partialReset (const plotHolder & allPlot, UIntMat & mat, char & pressedKeyPacman, char & pressedKeyGhost, sPacman & pac, sGhost & ghost, const unsigned & caseSize);
 */
void partialReset (const plotHolder & allPlot, UIntMat & mat, char & pressedKeyPacman, char & pressedKeyGhost, sPacman & pac, sGhost & ghost, const unsigned & caseSize);

void displayMat (const UIntMat & mat, const unsigned & caseSize, const unsigned & margeSize, MinGL & window, sPacman & pacman, sGhost & ghost) {
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

void isKeyPressed (MinGL & window, char & pressedKey, const sPacman & pacman) {
    // les touches de déplacement
    char kUp = pacman.MapParamChar.find("PKeyUp")->second;
    char kDown = pacman.MapParamChar.find("PKeyDown")->second;
    char kRight = pacman.MapParamChar.find("PKeyRight")->second;
    char kLeft = pacman.MapParamChar.find("PKeyLeft")->second;
    if (window.isPressed({kUp, false}))
        pressedKey = kUp;
    else if (window.isPressed({kDown, false}))
        pressedKey = kDown;
    else if (window.isPressed({kLeft, false}))
        pressedKey = kLeft;
    else if (window.isPressed({kRight, false}))
        pressedKey = kRight;
}

void isKeyPressedGhost (MinGL & window, char & pressedKey, const sGhost & ghost) {
    // les touches de déplacement
    char kUp = ghost.MapParamChar.find("GKeyUp")->second;
    char kDown = ghost.MapParamChar.find("GKeyDown")->second;
    char kRight = ghost.MapParamChar.find("GKeyRight")->second;
    char kLeft = ghost.MapParamChar.find("GKeyLeft")->second;
    if (window.isPressed({kUp, false}))
        pressedKey = kUp;
    else if (window.isPressed({kDown, false}))
        pressedKey = kDown;
    else if (window.isPressed({kLeft, false}))
        pressedKey = kLeft;
    else if (window.isPressed({kRight, false}))
        pressedKey = kRight;
}

void partialReset (const plotHolder & allPlot, UIntMat & mat, char & pressedKeyPacman, char & pressedKeyGhost, sPacman & pac, sGhost & ghost, const unsigned & caseSize) {
    // réinitialise tous les mouvements du fantome
    pressedKeyGhost = 'p';
    ghost.currentMove = 'p';
    ghost.lastMove = 'p';

    // si pacman ne peut pas manger le fantome
    if (!pac.canEat) {
        // réinitialise tous les mouvements du pacman
        pressedKeyPacman = 'p';
        pac.currentMove = 'p';
        pac.lastMove = 'p';

        // remet pacman à sa position initiale
        mat[pac.initialPos.first][pac.initialPos.second] = 8;
        pac.currentAnimation = pac.totalAnimation;

        // pacman perd une vie
        --pac.stock;
    }
    else // si il peut manger
        pac.score += 200;

    if (pac.canEat)
        ghost.previousCase = 8;
    else
        ghost.previousCase = 0;
    // remet pacman à sa position initiale
    mat[ghost.posMat.first][ghost.posMat.second] = ghost.previousCase;
    ghost.previousCase = 0;
    mat[ghost.initialPos.first][ghost.initialPos.second] = 9;

    // réintialise les booléen de contact
    ghost.hitPacman = false;
    pac.hitGhost = false;

    // si pacman n'as plus de vie ou s'il a mangé tous les beignet
    if (pac.stock == 0 || pac.beignetToEat == 0) {
        // réinitialiser le fantome et pacman
        initPacman(pac, caseSize);
        initGhost(ghost, caseSize);
        // réinitialise le score de pacman s'il a perdu toutes ses vies
        if (pac.stock == 0)
            pac.score = 0;
        pac.stock = 3;
        // choisi une nouvelle carte
        randomPlot(mat, allPlot);
        pac.beignetToEat = countBeignet (mat);
        pac.initialPosNotInit = true;
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

    // taille fictive de la grille
    unsigned caseSize = 24;
    unsigned margin = 50;

    // ATH
    string scoreStr, stockStr;

    // touches préssées de base
    char pressedKey = 'p';
    char pressedKeyGhost = 'p';

    // initialisation des sprites
    sPacman pac1;
    sGhost ghost1;

    // récupération des cartes dans le fichier
    UIntMat matrice;
    plotHolder allPlot;
    importAllPlot(allPlot, "map");
    randomPlot (matrice, allPlot);

    // compte le nombre de beignet que pacman doit manger pour gagner
    pac1.beignetToEat = countBeignet (matrice);

    // initialise le pacman et le fantome
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
        if (pac1.initialPosNotInit) { // si les positions initial ne sont pas initialisé
            pac1.initialPos = pac1.posMat;
            ghost1.initialPos = ghost1.posMat;
            pac1.initialPosNotInit = false;
        }

        // affichage de pacman et du fantome
        affPac(window, pac1);
        majGhostSpritePos(ghost1);
        affGhost(window, ghost1);

        // touches préssées
        isKeyPressed(window, pressedKey, pac1);
        isKeyPressedGhost(window, pressedKeyGhost, ghost1);

        // si pacman est sous pacgum
        if (pac1.canEat) {
            ghost1.speed = 2;
            ghost1.color = KBlue;
        }
        else {
            ghost1.speed = ghost1.baseSpeed;
            ghost1.color = KRed;
        }

        // Mouvements
        movementDirection(matrice, pressedKey, pac1, caseSize);
        movementDirectionGhost(matrice, pressedKeyGhost, ghost1, caseSize);

        // contact
        if (ghost1.hitPacman || pac1.hitGhost || pac1.beignetToEat == 0) {
            partialReset(allPlot, matrice, pressedKey, pressedKeyGhost, pac1, ghost1, caseSize);
        }

        // score
        majATH(scoreStr, stockStr, pac1);
        window << nsGui::Text(Vec2D(margin,margin-10), scoreStr, KWhite, nsGui::GlutFont::BITMAP_HELVETICA_18);
        window << nsGui::Text(Vec2D(margin + (matrice[0].size()-2) * caseSize,margin-10), stockStr, KWhite, nsGui::GlutFont::BITMAP_HELVETICA_18);

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
