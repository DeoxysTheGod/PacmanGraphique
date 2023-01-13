#include "movement.h"
#include "score.h"

bool caseExist (const UIntMat & mat, const Position & pos){
    return ((pos.first<mat[0].size() && (pos.second<mat.size())) && (mat[pos.first][pos.second] != 1));
}

void move (UIntMat & mat, Position & posStart, Position & posEnd, unsigned & score){
    if (mat[posEnd.first][posEnd.second] == 7)
       tp(mat, posEnd);
    addScore(mat, posEnd, score);
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
    char kUp = pac.MapParamChar.find("PKeyUp")->second;
    char kDown = pac.MapParamChar.find("PKeyDown")->second;
    char kRight = pac.MapParamChar.find("PKeyRight")->second;
    char kLeft = pac.MapParamChar.find("PKeyLeft")->second;
    if (pac.currentMove == 'p' && (pressedKey == kUp || pressedKey == kDown || pressedKey == kRight || pressedKey == kLeft)) {
        cout << pressedKey << ", " << pac.currentMove << ", " << pac.lastMove << endl;
        if (pac.cooldown == 0) {
            pac.cooldown = caseSize/pac.speed;
            if (pressedKey == kUp || pac.currentMove == kUp) {
                if (caseExist(mat, {pac.posMat.first-1, pac.posMat.second})) {
                    pac.rotation = 1;
                    pac.currentMove = kUp;
                    pac.lastMove = kUp;
                }
                else if (pressedKey == pac.lastMove)
                    pac.lastMove = 'p';
                else
                    pac.currentMove = pac.lastMove;
            }
            if (pressedKey == kDown || pac.currentMove == kDown) {
                cout << "ok down" << endl;
                if (caseExist(mat, {pac.posMat.first+1, pac.posMat.second})) {
                    cout << "no wall down" << endl;
                    pac.rotation = 3;
                    pac.currentMove = kDown;
                    pac.lastMove = kDown;
                }
                else if (pressedKey == pac.lastMove)
                    pac.lastMove = 'p';
                else
                    pac.currentMove = pac.lastMove;
            }
            if (pressedKey == kLeft || pac.currentMove == kLeft) {
                if (caseExist(mat, {pac.posMat.first, pac.posMat.second-1})) {
                    pac.rotation = 2;
                    pac.currentMove = kLeft;
                    pac.lastMove = kLeft;
                }
                else if (pressedKey == pac.lastMove)
                    pac.lastMove = 'p';
                else
                    pac.currentMove = pac.lastMove;
            }
            if (pressedKey == kRight || pac.currentMove == kRight) {
                cout << "ok right" << endl;
                if (caseExist(mat, {pac.posMat.first, pac.posMat.second+1})) {
                    cout << "no wall right" << endl;
                    pac.rotation = 0;
                    pac.currentMove = kRight;
                    pac.lastMove = kRight;
                }
                else if (pressedKey == pac.lastMove) {
                    cout << "2 right" << endl;
                    pac.lastMove = 'p';
                }
                else {
                    cout << "3 right" << endl;
                    pac.currentMove = pac.lastMove;
                }
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
        move(mat, pac.posMat, pac.nextPos, pac.score);
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
    char kUp = ghost.MapParamChar.find("GKeyUp")->second;
    char kDown = ghost.MapParamChar.find("GKeyDown")->second;
    char kRight = ghost.MapParamChar.find("GKeyRight")->second;
    char kLeft = ghost.MapParamChar.find("GKeyLeft")->second;
    //cout << kUp << ", " << kDown << ", " << kLeft << ", " << kRight << ", " << endl;
    if (ghost.currentMove == 'p' && (pressedKey == kUp || pressedKey == kDown || pressedKey == kLeft || pressedKey == kRight)) {
        if (ghost.cooldown == 0) {
            ghost.cooldown = caseSize/ghost.speed;
            if (pressedKey == kUp) {
                if (caseExist(mat, {ghost.posMat.first-1, ghost.posMat.second})) {
                    ghost.currentMove = kUp;
                    ghost.lastMove = kUp;
                }
                else if (pressedKey == ghost.lastMove)
                    ghost.lastMove = 'p';
                else
                    ghost.currentMove = ghost.lastMove;
            }
            else if (pressedKey == kDown) {
                if (caseExist(mat, {ghost.posMat.first+1, ghost.posMat.second})) {
                    ghost.currentMove = kDown;
                    ghost.lastMove = kDown;
                }
                else if (pressedKey == ghost.lastMove)
                    ghost.lastMove = 'p';
                else
                    ghost.currentMove = ghost.lastMove;
            }
            else if (pressedKey == kLeft) {
                if (caseExist(mat, {ghost.posMat.first, ghost.posMat.second-1})) {
                    ghost.currentMove = kLeft;
                    ghost.lastMove = kLeft;
                }
                else if (pressedKey == ghost.lastMove)
                    ghost.lastMove = 'p';
                else
                    ghost.currentMove = ghost.lastMove;
            }
            else if (pressedKey == kRight) {
                if (caseExist(mat, {ghost.posMat.first, ghost.posMat.second+1})) {
                    ghost.currentMove = kRight;
                    ghost.lastMove = kRight;
                }
                else if (pressedKey == ghost.lastMove)
                    ghost.lastMove = 'p';
                else
                    ghost.currentMove = ghost.lastMove;
            }
            if (ghost.currentMove == 'p')
                ghost.cooldown = 0;
        }
    }

    else if (ghost.cooldown == 1) {
        if (ghost.currentMove == kUp)
            ghost.nextPos = {ghost.posMat.first-1, ghost.posMat.second};
        else if (ghost.currentMove == kDown)
            ghost.nextPos = {ghost.posMat.first+1, ghost.posMat.second};
        else if (ghost.currentMove == kLeft)
            ghost.nextPos = {ghost.posMat.first, ghost.posMat.second-1};
        else if (ghost.currentMove == kRight)
            ghost.nextPos = {ghost.posMat.first, ghost.posMat.second+1};
        move(mat, ghost.posMat, ghost.nextPos, ghost);
        ghost.currentMove = 'p';
        ghost.cooldown = 0;
    }

    else if (ghost.cooldown != 0) {
        if (ghost.currentMove == kUp)
            ghost.pos = {ghost.pos.first, ghost.pos.second-ghost.speed};
        else if (ghost.currentMove == kDown)
            ghost.pos = {ghost.pos.first, ghost.pos.second+ghost.speed};
        else if (ghost.currentMove == kLeft)
            ghost.pos = {ghost.pos.first-ghost.speed, ghost.pos.second};
        else if (ghost.currentMove == kRight)
            ghost.pos = {ghost.pos.first+ghost.speed, ghost.pos.second};
        --ghost.cooldown;
    }
}
