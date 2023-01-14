#include "score.h"

void addScore (const UIntMat & mat, const Position & pos, sPacman & pacman){
    if (mat[pos.first][pos.second] == 2){
        pacman.score += 10;
        --pacman.beignetToEat;
    }
    else if (mat[pos.first][pos.second] == 3){
        pacman.score += 50;
        --pacman.beignetToEat;
    }
    else if (mat[pos.first][pos.second] ==  4){
        pacman.score += 100;
        --pacman.beignetToEat;
    }
}

void majATH (string & scoreStr, string & stockStr, sPacman & pacman){
    scoreStr = "score : " + std::to_string(pacman.score);
    stockStr = "vie : " + std::to_string(pacman.stock);
}
