#include "score.h"

void addScore (const UIntMat & mat, const Position & pos, unsigned & score){
    if (mat[pos.first][pos.second] == 2){
        score += 10;
    }
    else if (mat[pos.first][pos.second] == 3){
        score += 50;
    }
    else if (mat[pos.first][pos.second] ==  4){
        score += 100;
    }
}

void majScore (string & scoreStr, sPacman & pacman){
    scoreStr = "score : " + std::to_string(pacman.score);
}
