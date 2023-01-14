#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "type.h"
#include "gameSprite.h"

#include <fstream>
#include <algorithm>

/*!
 * \brief loadParameter : Permet de récupérer les paramètres du pacman stockés dans le fichier config.yaml
 * \param[out] pacman : le pacman à modifier
 * \param[out] authKey : les touches qui sont autorisées à être lu pour le pacman
 * @fn void loadParameter (sPacman & pacman, authorizedKeyPacman & authKey);
 */
void loadParameter (sPacman & pacman, authorizedKeyPacman & authKey);

/*!
 * \brief loadParameter : Permet de récupérer les paramètres du fantome stockés dans le fichier config.yaml
 * \param[out] pacman : le fantome à modifier
 * \param[out] authKey : les touches qui sont autorisées à être lu pour le fantome
 * @fn void loadParameter (sGhost & ghost, authorizedKeyGhost & authKey);
 */
void loadParameter (sGhost & ghost, authorizedKeyGhost & authKey);

#endif // PARAMETERS_H
