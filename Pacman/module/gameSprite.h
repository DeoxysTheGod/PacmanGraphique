#ifndef GAMESPRITE_H
#define GAMESPRITE_H

#include "type.h"
#include <math.h>

/*!
 * \brief The sPacman class : informations concernant le pacman
 */
struct sPacman {
    // position
    Position pos, nextPos, posMat, initialPos;
    bool initialPosNotInit;

    // touches
    authorizedKeyPacman authKey;
    std::map <std::string, char> MapParamChar;

    // contact
    bool hitGhost;

    // corps du pacman
    unsigned triangleAmount;
    unsigned size;
    unsigned rotation;

    // score
    unsigned score;
    unsigned stock;
    unsigned beignetToEat;

    // cooldown
    unsigned fps;
    unsigned eatCooldown;
    bool canEat;
    unsigned cooldown;

    // deplacement
    char lastMove;
    char currentMove;
    unsigned speed;

    // bouche
    unsigned totalAnimation;
    unsigned currentAnimation;
    unsigned idle;
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
    // position
    Position pos, nextPos, posMat, initialPos;
    Position rightEyePos, leftEyePos;

    // contact
    bool hitPacman;

    // cooldown
    unsigned cooldown;
    unsigned baseCooldown;

    // touches
    authorizedKeyGhost authKey;
    std::map <std::string, char> MapParamChar;

    // deplacement
    char currentMove;
    char lastMove;
    unsigned speed;
    unsigned baseSpeed;

    // sprite
    unsigned size;
    unsigned triangleAmount;
    unsigned eyeSize, pupilSize;

    Position wavePos;
    unsigned nbWave, waveSize;

    RGBAcolor color, eyeColor, pupilColor;

    unsigned previousCase = 0;
};

/*!
 * \brief initPacman : initialisation des variables de bases du pacman
 * \param[in_out] pac : le pacman à modifier
 * \param[in] caseSize : la taille des cases fictives sur l'écran
 * @fn void initPacman(sPacman & pac, const unsigned caseSize);
 */
void initPacman(sPacman & pac, const unsigned caseSize);

/*!
 * \brief initPacman : initialisation des variables de bases du fantome
 * \param[in_out] pac : le fantome à modifier
 * \param[in] caseSize : la taille des cases fictives sur l'écran
 * @fn void initGhost(sGhost & ghost, const unsigned caseSize);
 */
void initGhost(sGhost & ghost, const unsigned caseSize);

/*!
 * \brief majGhostSpritePos : cette fonction sert à faire en sorte que les yeux se déplacent à l'endroit où est le fantome
 * \param[in_out] ghost : la structure du fantome
 * @fn void majGhostSpritePos(sGhost & ghost);
 */
void majGhostSpritePos(sGhost & ghost);

/*!
 * \brief pacmanAnimation : gère les animations de la bouche de pacman
 * \param[in_out] pac : le pacman à modifier
 * @fn void pacmanAnimation(sPacman & pac);
 */
void pacmanAnimation(sPacman & pac);

#endif // GAMESPRITE_H
