#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "type.h"
#include "gameSprite.h"

/*!
 * \brief caseExist : verifie si la case existe et si c'est possible d'y aller
 * \param[in] mat : la matrice qui represente la grille de jeu
 * \param[in] pos : la position de la case
 * \return renvoie un booleen pour dire si la case existe
 */
bool caseExist (const UIntMat & mat, const Position & pos);

/*!
 * \brief movementDirection : permet de gerer les deplacements reel et fictif en fonction des touches pressees
 * \param[in out] mat : la matrice qui represente la grille de jeu
 * \param[in out] pressedKey : la touche qui a ete presse
 * \param[in out] pac : la structure de notre pacman
 * \param[in] fps : le taux de raffraichissement de la fenetre
 */
void movementDirection (UIntMat & mat, char & pressedKey, sPacman & pac, const unsigned & fps);

void tp (UIntMat & mat, Position & pos);

void move (UIntMat & mat, Position & posStart, Position & posEnd);

void move (UIntMat & mat, Position & posStart, Position & posEnd, unsigned & previousCase);

#endif // MOVEMENT_H
