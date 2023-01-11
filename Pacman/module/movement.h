#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "type.h"
#include "gameSprite.h"

/*!
 * \brief caseExist : verifie si la case existe et si c'est possible d'y aller
 * \param[in] mat : la matrice qui represente la grille de jeu
 * \param[in] pos : la position de la case
 * \return renvoie un booleen pour dire si la case existe
 * @fn bool caseExist (const UIntMat & mat, const Position & pos);
 */
bool caseExist (const UIntMat & mat, const Position & pos);

/*!
 * \brief movementDirection : permet de gerer les deplacements reel et fictif en fonction des touches pressees
 * \param[in out] mat : la matrice qui represente la grille de jeu
 * \param[in out] pressedKey : la touche qui a ete presse
 * \param[in out] pac : la structure de notre pacman
 * \param[in] caseSize : la taille d'une case
 * @fn void movementDirection (UIntMat & mat, char & pressedKey, sPacman & pac, const unsigned & fps);
 */
void movementDirection (UIntMat & mat, char & pressedKey, sPacman & pac, const unsigned & caseSize);

/*!
 * \brief tp : permet de gerer la teleportation de pacman lorsqu'il sors de l'ecran
 * \param[in] mat : la matrice qui represente la grille de jeu
 * \param[out] pos : la position actuelle du pacman
 * @fn void tp (const UIntMat & mat, Position & pos);
 */
void tp (const UIntMat & mat, Position & pos);

/*!
 * \brief move : gere les deplacement reel du pacman dans la matrice
 * \param[out] mat : la matrice qui represente la grille de jeu
 * \param[out] posStart : position de debut du pacman
 * \param[out] posEnd : position de fin du pacman
 * @fn void move (UIntMat & mat, Position & posStart, Position & posEnd);
 */
void move (UIntMat & mat, Position & posStart, Position & posEnd);

/*!
 * \brief move : gere les deplacement reel du pacman dans la matrice
 * \param[out] mat : la matrice qui represente la grille de jeu
 * \param[out] posStart : position de debut du fantome
 * \param[out] posEnd : position de fin du fantome
 * \param[in out] previousCase : c'est ce que contenait la case avant que le fantome ne passe dessus
 * @fn void move (UIntMat & mat, Position & posStart, Position & posEnd, unsigned & previousCase);
 */
void move (UIntMat & mat, Position & posStart, Position & posEnd, unsigned & previousCase);

void movementDirectionGhost (UIntMat & mat, char & pressedKey, sGhost & ghost, const unsigned & caseSize);

#endif // MOVEMENT_H
