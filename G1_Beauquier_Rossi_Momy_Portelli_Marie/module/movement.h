#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "type.h"
#include "gameSprite.h"

/*!
 * \brief caseExist : vérifie si la case existe et s'il est possible d'y aller, pour le fantome
 * \param[in] mat : la matrice qui représente la grille de jeu
 * \param[in] pos : la position de la case sur laquelle on veut se rendre
 * \return renvoie un booléen pour dire si la case existe
 * @fn bool caseExistForGhost (const UIntMat & mat, const Position & pos);
 */
bool caseExistForGhost (const UIntMat & mat, const Position & pos);

/*!
 * \brief caseExist : vérifie si la case existe et s'il est possible d'y aller, pour le pacman
 * \param[in] mat : la matrice qui représente la grille de jeu
 * \param[in] pos : la position de la case de la case sur laquelle on veut se rendre
 * \return renvoie un booléen pour dire si la case existe
 * @fn bool caseExistForPacman (const UIntMat & mat, const Position & pos);
 */
bool caseExistForPacman (const UIntMat & mat, const Position & pos);

/*!
 * \brief pacmanHitGhost : dit si pacman est en contact avec le fantome
 * \param[in] mat : grille de jeu
 * \param[in] pos : position de la case à vérifier
 * \return un booléen pour dire si pacman est en contact avec le fantome
 * @fn bool pacmanHitGhost (const UIntMat & mat, const Position & pos);
 */
bool pacmanHitGhost (const UIntMat & mat, const Position & pos);

/*!
 * \brief ghostHitPacman : dit si le fantome est en contact avec pacman
 * \param[in] mat : grille de jeu
 * \param[in] pos : position de la case à vérifier
 * \return un booléen pour dire si le fantome est en contact avec pacman
 * @fn bool ghostHitPacman (const UIntMat & mat, const Position & pos);
*/
bool ghostHitPacman (const UIntMat & mat, const Position & pos);

/*!
 * \brief movementDirection : permet de gérer les déplacements réel et fictif du pacman en fonction des touches pressées
 * \param[in_out] mat : la matrice qui représente la grille de jeu
 * \param[in_out] pressedKey : la touche qui à été préssé
 * \param[in_out] pac : la structure de notre pacman
 * \param[in] caseSize : la taille d'une case fictive
 * @fn void movementDirection (UIntMat & mat, char & pressedKey, sPacman & pac, const unsigned & caseSize);
 */
void movementDirection (UIntMat & mat, char & pressedKey, sPacman & pac, const unsigned & caseSize);

/*!
 * \brief movementDirection : permet de gérer les déplacements réel et fictif du fantome en fonction des touches pressées
 * \param[in_out] mat : la matrice qui représente la grille de jeu
 * \param[in_out] pressedKey : la touche qui à été préssé
 * \param[in_out] pac : la structure de notre fantome
 * \param[in] caseSize : la taille d'une case fictive
 * @fn void movementDirectionGhost (UIntMat & mat, char & pressedKey, sGhost & ghost, const unsigned & caseSize);
 */
void movementDirectionGhost (UIntMat & mat, char & pressedKey, sGhost & ghost, const unsigned & caseSize);

/*!
 * \brief tp : permet de gérer la téléportation de pacman lorsqu'il sort de l'écran
 * \param[in] mat : la matrice qui représente la grille de jeu
 * \param[out] pos : la position actuelle du pacman
 * @fn void tp (const UIntMat & mat, Position & pos);
 */
void tp (const UIntMat & mat, Position & pos);

/*!
 * \brief move : gère les déplacement réel du pacman dans la matrice
 * \param[out] mat : la matrice qui représente la grille de jeu
 * \param[out] posStart : position de début du pacman
 * \param[out] posEnd : position de fin du pacman
 * \param[out] pac : le pacman à modifier
 * @fn void move (UIntMat & mat, Position & posStart, Position & posEnd, sPacman & pac);
 */
void move (UIntMat & mat, Position & posStart, Position & posEnd, sPacman & pac);

/*!
 * \brief move : gère les déplacement réel du fantome dans la matrice
 * \param[out] mat : la matrice qui represente la grille de jeu
 * \param[out] posStart : position de début du fantome
 * \param[out] posEnd : position de fin du fantome
 * \param[out] ghost : le fantome à modifier
 * @fn void move (UIntMat & mat, Position & posStart, Position & posEnd, unsigned & previousCase);
 */
void move (UIntMat & mat, Position & posStart, Position & posEnd, sGhost & ghost);

#endif // MOVEMENT_H
