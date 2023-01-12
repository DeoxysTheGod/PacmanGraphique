#ifndef SCORE_H
#define SCORE_H

#include "type.h"
#include "gameSprite.h"

void addScore (const UIntMat & mat, const Position & pos, unsigned & score);


void majScore (string & scoreStr, sPacman & pacman);

#endif // SCORE_H
