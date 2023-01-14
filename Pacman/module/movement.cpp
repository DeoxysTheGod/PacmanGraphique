#include "movement.h"
#include "score.h"

bool caseExistForGhost (const UIntMat & mat, const Position & pos){
    return ((pos.first<mat.size() && pos.second<mat[0].size()) && mat[pos.first][pos.second] != 1);
}

bool caseExistForPacman (const UIntMat & mat, const Position & pos){
    return ((pos.first<mat.size() && pos.second<mat[0].size()) && mat[pos.first][pos.second] != 1 && mat[pos.first][pos.second] != 5);
}

bool ghostHitPacman (UIntMat & mat, Position & pos) {
    return mat[pos.first][pos.second] == 8;
}

void move (UIntMat & mat, Position & posStart, Position & posEnd, sPacman & pac){
    if (mat[posEnd.first][posEnd.second] == 3) {
        pac.eatCooldown = pac.fps * 8;
        pac.canEat = true;
        pac.color = KWhite;
    }
    if (mat[posEnd.first][posEnd.second] == 7)
       tp(mat, posEnd);
    if (mat[posEnd.first][posEnd.second] == 9)
        pac.hitGhost = true;
    addScore(mat, posEnd, pac);
    mat[posEnd.first][posEnd.second] = mat[posStart.first][posStart.second];
    mat[posStart.first][posStart.second] = 0;
    posStart.first = posEnd.first;
    posStart.second = posEnd.second;
}

void move (UIntMat & mat, Position & posStart, Position & posEnd, sGhost & ghost)
{
    if (ghostHitPacman(mat, posEnd))
        ghost.hitPacman = true;
    unsigned tmp = mat[posEnd.first][posEnd.second];
    mat[posEnd.first][posEnd.second] = mat[posStart.first][posStart.second];
    mat[posStart.first][posStart.second] = ghost.previousCase;
    ghost.previousCase = tmp;
    posStart.first = posEnd.first;
    posStart.second = posEnd.second;
}

void tp (const UIntMat & mat, Position & pos){
    if (pos.first == 0)
        pos.first = mat[1].size() -2;
    else if (pos.first == mat[1].size() -1)
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
    vector<unsigned> canGo (4, 0);
    if (pac.currentMove == 'p' && (pressedKey == kUp || pressedKey == kDown || pressedKey == kRight || pressedKey == kLeft)) {
        if (pac.cooldown == 0) {
            pac.cooldown = caseSize/pac.speed;
            if (caseExistForPacman(mat, {pac.posMat.first-1, pac.posMat.second})) // haut
                canGo[0] = 1;
            if (caseExistForPacman(mat, {pac.posMat.first+1, pac.posMat.second})) // bas
                canGo[1] = 1;
            if (caseExistForPacman(mat, {pac.posMat.first, pac.posMat.second-1})) // gauche
                canGo[2] = 1;
            if (caseExistForPacman(mat, {pac.posMat.first, pac.posMat.second+1})) // droite
                canGo[3] = 1;
            // haut
            if (pressedKey == kUp && canGo[0] == 1) {
                pac.rotation = 1;
                pac.currentMove = kUp;
                pac.lastMove = kUp;
            }
            // bas
            else if (pressedKey == kDown && canGo[1] == 1) {
                pac.rotation = 3;
                pac.currentMove = kDown;
                pac.lastMove = kDown;
            }
            // gauche
            else if (pressedKey == kLeft && canGo[2] == 1) {
                pac.rotation = 2;
                pac.currentMove = kLeft;
                pac.lastMove = kLeft;
            }
            // droite
            else if (pressedKey == kRight && canGo[3] == 1) {
                pac.rotation = 0;
                pac.currentMove = kRight;
                pac.lastMove = kRight;
            }
            // haut
            else if (pac.lastMove == kUp && canGo[0] == 1) {
                pac.rotation = 1;
                pac.currentMove = kUp;
            }
            // bas
            else if (pac.lastMove == kDown && canGo[1] == 1) {
                pac.rotation = 3;
                pac.currentMove = kDown;
            }
            // gauche
            else if (pac.lastMove == kLeft && canGo[2] == 1) {
                pac.rotation = 2;
                pac.currentMove = kLeft;
            }
            // droite
            else if (pac.lastMove == kRight && canGo[3] == 1) {
                pac.rotation = 0;
                pac.currentMove = kRight;
            }
            else {
                pac.lastMove = 'p';
                pac.cooldown = 0;
                pac.mouthSize = pac.triangleAmount/5;
                pac.mouthStart = pac.triangleAmount-pac.mouthSize/2;
                pac.currentAnimation = 0;
            }
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
        move(mat, pac.posMat, pac.nextPos, pac);
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
        pacmanAnimation(pac);
        --pac.cooldown;
    }
    // invincibilite pacman
    if (pac.eatCooldown != 0) {
        --pac.eatCooldown;
    }
    else {
        pac.color = KYellow;
        pac.canEat = false;
    }
}


void movementDirectionGhost (UIntMat & mat, char & pressedKey, sGhost & ghost, const unsigned & caseSize) {
    char kUp = ghost.MapParamChar.find("GKeyUp")->second;
    char kDown = ghost.MapParamChar.find("GKeyDown")->second;
    char kRight = ghost.MapParamChar.find("GKeyRight")->second;
    char kLeft = ghost.MapParamChar.find("GKeyLeft")->second;
    vector<unsigned> canGo (4,0);
    cout << mat[0].size() <<  ", " << mat.size() << endl;

    if (ghost.currentMove == 'p' && (pressedKey == kUp || pressedKey == kDown || pressedKey == kLeft || pressedKey == kRight)) {
        if (ghost.cooldown == 0) {
            ghost.cooldown = caseSize/ghost.speed;
            if (caseExistForGhost(mat, {ghost.posMat.first-1, ghost.posMat.second})) // haut
                canGo[0] = 1;
            if (caseExistForGhost(mat, {ghost.posMat.first+1, ghost.posMat.second})) // bas
                canGo[1] = 1;
            if (caseExistForGhost(mat, {ghost.posMat.first, ghost.posMat.second-1})) // gauche
                canGo[2] = 1;
            if (caseExistForGhost(mat, {ghost.posMat.first, ghost.posMat.second+1})) // droite
                canGo[3] = 1;
            // haut
            if (pressedKey == kUp && canGo[0] == 1) {
                ghost.currentMove = kUp;
                ghost.lastMove = kUp;
            }
            // bas
            else if (pressedKey == kDown && canGo[1] == 1) {
                ghost.currentMove = kDown;
                ghost.lastMove = kDown;
            }
            // gauche
            else if (pressedKey == kLeft && canGo[2] == 1) {
                ghost.currentMove = kLeft;
                ghost.lastMove = kLeft;
            }
            // droite
            else if (pressedKey == kRight && canGo[3] == 1) {
                ghost.currentMove = kRight;
                ghost.lastMove = kRight;
            }
            // haut
            else if (ghost.lastMove == kUp && canGo[0] == 1) {
                ghost.currentMove = kUp;
            }
            // bas
            else if (ghost.lastMove == kDown && canGo[1] == 1) {
                ghost.currentMove = kDown;
            }
            // gauche
            else if (ghost.lastMove == kLeft && canGo[2] == 1) {
                ghost.currentMove = kLeft;
            }
            // droite
            else if (ghost.lastMove == kRight && canGo[3] == 1) {
                ghost.currentMove = kRight;
            }
            else {
                ghost.lastMove = 'p';
                ghost.cooldown = 0;
            }
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
