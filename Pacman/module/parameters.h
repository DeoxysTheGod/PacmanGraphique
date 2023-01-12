#ifndef PARAMETERS_H
#define PARAMETERS_H

#include "type.h"
#include "gameSprite.h"

#include <fstream>
#include <algorithm>

void loadParameter (sPacman & pacman, authorizedKeyPacman & authKey);

void loadParameter (sGhost & ghost, authorizedKeyGhost & authKey);

#endif // PARAMETERS_H
