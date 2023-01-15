#ifndef SCORE_H
#define SCORE_H

#include "type.h"
#include "gameSprite.h"

/*!
 * \brief addScore : modifie le score du pacman en fonction de ce qu'il a mangé
 * \param[in] mat : grille de jeu
 * \param[in] pos : la position de la case que pacman va manger
 * \param[in_out] pacman : le pacman à modifier
 * @fn void addScore (const UIntMat & mat, const Position & pos, sPacman & pacman);
 */
void addScore (const UIntMat & mat, const Position & pos, sPacman & pacman);

/*!
 * \brief majATH : met à jour le texte qui doit s'afficher à l'écran
 * \param[out] scoreStr : la string qui contient la phrase de score
 * \param[out] stockStr : la string qui contient la phrase des vies
 * \param[out] pacman : le pacman qui doit donner son score
 * @fn void majATH (string & scoreStr, string & stockStr, sPacman & pacman);
 */
void majATH (string & scoreStr, string & stockStr, sPacman & pacman);

#endif // SCORE_H
