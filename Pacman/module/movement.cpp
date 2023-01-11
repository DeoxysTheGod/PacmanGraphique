#include "movement.h"

bool caseExist (const UIntMat & mat, const Position & pos){
    return ((pos.first<mat[0].size() && (pos.second<mat.size())) && (mat[pos.first][pos.second] != 1));
}

void move (UIntMat & mat, Position & posStart, Position & posEnd){
    if (mat[posEnd.first][posEnd.second] == 7)
       tp(mat, posEnd);
    mat[posEnd.first][posEnd.second] = mat[posStart.first][posStart.second];
    mat[posStart.first][posStart.second] = 0;
    posStart.first = posEnd.first;
    posStart.second = posEnd.second;
}

void move (UIntMat & mat, Position & posStart, Position & posEnd, sGhost & ghost)
{
    unsigned tmp = mat[posEnd.first][posEnd.second];
    mat[posEnd.first][posEnd.second] = mat[posStart.first][posStart.second];
    mat[posStart.first][posStart.second] = ghost.previousCase;
    ghost.previousCase = tmp;
    posStart.first = posEnd.first;
    posStart.second = posEnd.second;
}

void tp (const UIntMat & mat, Position & pos){
    if (pos.first == 0)
        pos.first = mat.size() -2;
    else if (pos.first == mat.size() -1)
        pos.first = 1;
    else if (pos.second == 0)
        pos.second = mat.size() -2;
    else if (pos.second == mat.size() -1)
        pos.second = 1;
}

void movementDirection (UIntMat & mat, char & pressedKey, sPacman & pac, const unsigned & caseSize) {
    if (pac.currentMove == 'p' && (pressedKey == 'z' || pressedKey == 's' || pressedKey == 'q' || pressedKey == 'd')) {
        if (pac.cooldown == 0) {
            pac.cooldown = caseSize/pac.speed;
            if (pressedKey == 'z') {
                pac.rotation = 1;
                if (caseExist(mat, {pac.posMat.first-1, pac.posMat.second}))
                    pac.currentMove = 'z';
                else
                    pac.currentMove = 'p';
            }
            else if (pressedKey == 's') {
                pac.rotation = 3;
                if (caseExist(mat, {pac.posMat.first+1, pac.posMat.second}))
                    pac.currentMove = 's';
                else
                    pac.currentMove = 'p';
            }
            else if (pressedKey == 'q') {
                pac.rotation = 2;
                if (caseExist(mat, {pac.posMat.first, pac.posMat.second-1}))
                    pac.currentMove = 'q';
                else
                    pac.currentMove = 'p';
            }
            else if (pressedKey == 'd') {
                pac.rotation = 0;
                if (caseExist(mat, {pac.posMat.first, pac.posMat.second+1}))
                    pac.currentMove = 'd';
                else
                    pac.currentMove = 'p';
            }
            if (pac.currentMove == 'p')
                pac.cooldown = 0;
        }
    }

    else if (pac.cooldown == 1) {
        if (pac.currentMove == 'z')
            pac.nextPos = {pac.posMat.first-1, pac.posMat.second};
        else if (pac.currentMove == 's')
            pac.nextPos = {pac.posMat.first+1, pac.posMat.second};
        else if (pac.currentMove == 'q')
            pac.nextPos = {pac.posMat.first, pac.posMat.second-1};
        else if (pac.currentMove == 'd')
            pac.nextPos = {pac.posMat.first, pac.posMat.second+1};
        move(mat, pac.posMat, pac.nextPos);
        pac.currentMove = 'p';
        pac.cooldown = 0;
    }

    else if (pac.cooldown != 0) {
        if (pac.currentMove == 'z')
            pac.pos = {pac.pos.first, pac.pos.second-pac.speed};
        else if (pac.currentMove == 's')
            pac.pos = {pac.pos.first, pac.pos.second+pac.speed};
        else if (pac.currentMove == 'q')
            pac.pos = {pac.pos.first-pac.speed, pac.pos.second};
        else if (pac.currentMove == 'd')
            pac.pos = {pac.pos.first+pac.speed, pac.pos.second};
        --pac.cooldown;
    }
}

void movementDirectionGhost (UIntMat & mat, char & pressedKey, sGhost & ghost, const unsigned & caseSize) {
    if (ghost.currentMove == 'p' && (pressedKey == 'o' || pressedKey == 'l' || pressedKey == 'k' || pressedKey == 'm')) {
        if (ghost.cooldown == 0) {
            ghost.cooldown = caseSize/ghost.speed;
            if (pressedKey == 'o') {
                if (caseExist(mat, {ghost.posMat.first-1, ghost.posMat.second}))
                    ghost.currentMove = 'o';
                else
                    ghost.currentMove = 'p';
            }
            else if (pressedKey == 'l') {
                if (caseExist(mat, {ghost.posMat.first+1, ghost.posMat.second}))
                    ghost.currentMove = 'l';
                else
                    ghost.currentMove = 'p';
            }
            else if (pressedKey == 'k') {
                if (caseExist(mat, {ghost.posMat.first, ghost.posMat.second-1}))
                    ghost.currentMove = 'k';
                else
                    ghost.currentMove = 'p';
            }
            else if (pressedKey == 'm') {
                if (caseExist(mat, {ghost.posMat.first, ghost.posMat.second+1}))
                    ghost.currentMove = 'm';
                else
                    ghost.currentMove = 'p';
            }
            if (ghost.currentMove == 'p')
                ghost.cooldown = 0;
        }
    }

    else if (ghost.cooldown == 1) {
        if (ghost.currentMove == 'o')
            ghost.nextPos = {ghost.posMat.first-1, ghost.posMat.second};
        else if (ghost.currentMove == 'l')
            ghost.nextPos = {ghost.posMat.first+1, ghost.posMat.second};
        else if (ghost.currentMove == 'k')
            ghost.nextPos = {ghost.posMat.first, ghost.posMat.second-1};
        else if (ghost.currentMove == 'm')
            ghost.nextPos = {ghost.posMat.first, ghost.posMat.second+1};
        move(mat, ghost.posMat, ghost.nextPos, ghost);
        ghost.currentMove = 'p';
        ghost.cooldown = 0;
    }

    else if (ghost.cooldown != 0) {
        if (ghost.currentMove == 'o')
            ghost.pos = {ghost.pos.first, ghost.pos.second-ghost.speed};
        else if (ghost.currentMove == 'l')
            ghost.pos = {ghost.pos.first, ghost.pos.second+ghost.speed};
        else if (ghost.currentMove == 'k')
            ghost.pos = {ghost.pos.first-ghost.speed, ghost.pos.second};
        else if (ghost.currentMove == 'm')
            ghost.pos = {ghost.pos.first+ghost.speed, ghost.pos.second};
        --ghost.cooldown;
    }
}
