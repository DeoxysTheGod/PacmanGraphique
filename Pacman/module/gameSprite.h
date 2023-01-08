#ifndef GAMESPRITE_H
#define GAMESPRITE_H

#include "type.h"
#include <math.h>

/*!
 * \brief The sPacman class : informations concernant le pacman
 */
struct sPacman {
    // position
    Position pos, nextPos, posMat;
    // corps du pacman
    unsigned triangleAmount;
    unsigned size;
    unsigned rotation;

    // cooldown
    unsigned cooldown;
    unsigned baseCooldown;

    // deplacement
    char currentMove;
    unsigned speed;

    // bouche
    unsigned mouthStart;
    unsigned mouthSize;

    // couleur
    RGBAcolor color;
    RGBAcolor mouthColor;
};

/*!
 * \brief The sGhost class : informations concernant le fantome
 */
struct sGhost {
    Position pos;
    Position rightEyePos, leftEyePos;
    unsigned size;
    unsigned rotation = 0;

    unsigned triangleAmount;
    unsigned eyeSize, pupilSize;

    Position wavePos;
    unsigned nbWave, waveSize;

    RGBAcolor color, eyeColor, pupilColor;

    unsigned previousCase = 0;
};

/*!
 * \brief initPacman : initialisation des variables de bases du pacman
 * \param[in out] pac : le pacman a modifier
 * \param[in] caseSize : la taille des cases fictives sur l'ecran
 * @fn void initPacman(sPacman & pac, const unsigned caseSize);
 */
void initPacman(sPacman & pac, const unsigned caseSize);

/*!
 * \brief initPacman : initialisation des variables de bases du fantome
 * \param[in out] pac : le fantome a modifier
 * \param[in] caseSize : la taille des cases fictives sur l'ecran
 * @fn void initGhost(sGhost & ghost, const unsigned caseSize);
 */
void initGhost(sGhost & ghost, const unsigned caseSize);

/*!
 * \brief majGhostSpritePos : cette fonction sert a faire en sorte que les yeux se deplacent a l'endroit ou est le fantome
 * \param[in out] ghost : la structure du fantome
 * @fn void majGhostSpritePos(sGhost & ghost);
 */
void majGhostSpritePos(sGhost & ghost);

#endif // GAMESPRITE_H
