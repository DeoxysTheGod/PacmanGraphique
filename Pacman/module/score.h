#ifndef SCORE_H
#define SCORE_H

#include "type.h"
#include "gameSprite.h"

/*!
 * \brief addScore : modifie le score du pacman en fonction de ce qu'il a mangé
 * \param[in] mat : grille de jeu
 * \param[in] pos : la position de la case que pacman va manger
 * \param[in_out] pacman : le pacman à modifier
 */
void addScore (const UIntMat & mat, const Position & pos, sPacman & pacman);

/*!
 * \brief majATH
 * \param scoreStr
 * \param stockStr
 * \param pacman
 */
void majATH (string & scoreStr, string & stockStr, sPacman & pacman);

#endif // SCORE_H
