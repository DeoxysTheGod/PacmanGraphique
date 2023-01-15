#include "score.h"

void addScore (const UIntMat & mat, const Position & pos, sPacman & pacman){
    if (mat[pos.first][pos.second] == 2){ // si la case est un beignet
        pacman.score += 10;
        --pacman.beignetToEat;
    }
    else if (mat[pos.first][pos.second] == 3){ // si la case est une pacgum
        pacman.score += 50;
        --pacman.beignetToEat;
    }
    else if (mat[pos.first][pos.second] ==  4){ // si la case est un fruit (les fruits n'ont pas été implanté pour l'instant)
        pacman.score += 100;
        --pacman.beignetToEat;
    }
}

void majATH (string & scoreStr, string & stockStr, sPacman & pacman){
    scoreStr = "score : " + std::to_string(pacman.score);
    stockStr = "vie : " + std::to_string(pacman.stock);
}
