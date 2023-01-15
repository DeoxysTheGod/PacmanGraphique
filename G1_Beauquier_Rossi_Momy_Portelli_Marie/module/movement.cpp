#include "movement.h"
#include "score.h"

bool caseExistForGhost (const UIntMat & mat, const Position & pos){
    return ((pos.first<mat.size() && pos.second<mat[0].size()) && mat[pos.first][pos.second] != 1);
}

bool caseExistForPacman (const UIntMat & mat, const Position & pos){
    return ((pos.first<mat.size() && pos.second<mat[0].size()) && mat[pos.first][pos.second] != 1 && mat[pos.first][pos.second] != 5);
}

bool ghostHitPacman (const UIntMat & mat, const Position & pos) {
    return mat[pos.first][pos.second] == 8;
}

bool pacmanHitGhost (const UIntMat & mat, const Position & pos) {
    return mat[pos.first][pos.second] == 9;
}

void move (UIntMat & mat, Position & posStart, Position & posEnd, sPacman & pac){
    if (mat[posEnd.first][posEnd.second] == 3) { // si la case est une pacgum
        pac.eatCooldown = pac.fps * 8; // la pacgum est active pendant 8sec
        pac.canEat = true;
    }
    if (mat[posEnd.first][posEnd.second] == 7) // si la case est un téléporteur
       tp(mat, posEnd);
    if (pacmanHitGhost(mat, posEnd)) // si la case est un fantome
        pac.hitGhost = true;
    addScore(mat, posEnd, pac);
    mat[posEnd.first][posEnd.second] = mat[posStart.first][posStart.second]; // déplace pacman sur la nouvelle case
    mat[posStart.first][posStart.second] = 0; // remplace l'ancienne case par une case vide
    posStart = posEnd;
}

void move (UIntMat & mat, Position & posStart, Position & posEnd, sGhost & ghost)
{
    if (ghostHitPacman(mat, posEnd)) // si la case est pacman
        ghost.hitPacman = true;
    unsigned tmp = mat[posEnd.first][posEnd.second];
    mat[posEnd.first][posEnd.second] = mat[posStart.first][posStart.second]; // déplace pacman sur la nouvelle case
    mat[posStart.first][posStart.second] = ghost.previousCase; // remplace l'ancienne case pas son ancienne valeur
    ghost.previousCase = tmp; // on stock la valeur de la case sur laquelle on est
    posStart = posEnd;
}

void tp (const UIntMat & mat, Position & pos){
    // si le tp est vertical
    if (pos.first == 0) // si nous sommes sur le tp du haut
        pos.first = mat.size() -2;
    else if (pos.first == mat.size() -1) // si nous sommes sur le tp du bas
        pos.first = 1;
    // si le tp est horizontal
    else if (pos.second == 0) // si nous sommes sur le tp de gauche
        pos.second = mat[0].size() -2;
    else if (pos.second == mat[0].size() -1) // si nous sommes sur le tp de droite
        pos.second = 1;
}

void movementDirection (UIntMat & mat, char & pressedKey, sPacman & pac, const unsigned & caseSize) {
    // les touches de déplacement
    char kUp = pac.MapParamChar.find("PKeyUp")->second;
    char kDown = pac.MapParamChar.find("PKeyDown")->second;
    char kRight = pac.MapParamChar.find("PKeyRight")->second;
    char kLeft = pac.MapParamChar.find("PKeyLeft")->second;
    // ce vecteur permet de stocker les mouvements possibles depuis la case où nous sommes
    vector<unsigned> canGo (4, 0);
    // si notre pacman n'est pas en train de faire un mouvement et qu'une touche valide est pressée
    if (pac.currentMove == 'p' && (pressedKey == kUp || pressedKey == kDown || pressedKey == kRight || pressedKey == kLeft)) {
        if (pac.cooldown == 0) {
            pac.cooldown = caseSize/pac.speed;
            // vérifie si les cases adjacentes au pacman sont disponibles
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
            // mouvement enregistré
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
            else { // dans les cas où aucun déplacement n'est possible
                pac.lastMove = 'p';
                pac.cooldown = 0;
                pac.mouthSize = pac.triangleAmount/5;
                pac.mouthStart = pac.triangleAmount-pac.mouthSize/2;
                pac.currentAnimation = 0;
            }
        }
    }

    // si le pacman est sur son dernier déplacement fictif
    else if (pac.cooldown == 1) {
        if (pac.currentMove == kUp)
            pac.nextPos = {pac.posMat.first-1, pac.posMat.second};
        else if (pac.currentMove == kDown)
            pac.nextPos = {pac.posMat.first+1, pac.posMat.second};
        else if (pac.currentMove == kLeft)
            pac.nextPos = {pac.posMat.first, pac.posMat.second-1};
        else if (pac.currentMove == kRight)
            pac.nextPos = {pac.posMat.first, pac.posMat.second+1};
        move(mat, pac.posMat, pac.nextPos, pac); // déplacement réel
        pac.currentMove = 'p';
        pac.cooldown = 0;
    }

    // si le cooldown n'est pas fini faire des déplacements fictif
    else if (pac.cooldown != 0) {
        if (pac.currentMove == kUp)
            pac.pos = {pac.pos.first, pac.pos.second-pac.speed};
        else if (pac.currentMove == kDown)
            pac.pos = {pac.pos.first, pac.pos.second+pac.speed};
        else if (pac.currentMove == kLeft)
            pac.pos = {pac.pos.first-pac.speed, pac.pos.second};
        else if (pac.currentMove == kRight)
            pac.pos = {pac.pos.first+pac.speed, pac.pos.second};
        pacmanAnimation(pac); // faire les animations
        --pac.cooldown;
    }
    // invincibilite pacman
    if (pac.eatCooldown != 0) { // gére le cooldown de pacman sous pacgum
        if (pac.eatCooldown%2 == 0)
            pac.color = KWhite;
        else
            pac.color = KYellow;
        --pac.eatCooldown;
    }
    else {
        pac.color = KYellow;
        pac.canEat = false;
    }
}


void movementDirectionGhost (UIntMat & mat, char & pressedKey, sGhost & ghost, const unsigned & caseSize) {
    // les touches de déplacement
    char kUp = ghost.MapParamChar.find("GKeyUp")->second;
    char kDown = ghost.MapParamChar.find("GKeyDown")->second;
    char kRight = ghost.MapParamChar.find("GKeyRight")->second;
    char kLeft = ghost.MapParamChar.find("GKeyLeft")->second;
    // ce vecteur permet de stocker les mouvements possibles depuis la case où nous sommes
    vector<unsigned> canGo (4,0);
    // si notre fantome n'est pas en train de faire un mouvement et qu'une touche valide est pressée
    if (ghost.currentMove == 'p' && (pressedKey == kUp || pressedKey == kDown || pressedKey == kLeft || pressedKey == kRight)) {
        if (ghost.cooldown == 0) {
            ghost.cooldown = caseSize/ghost.speed;
            // vérifie si les cases adjacentes au pacman sont disponibles
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
            // mouvement enregistré
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
            else { // dans les cas où aucun déplacement n'est possible
                ghost.lastMove = 'p';
                ghost.cooldown = 0;
            }
        }
    }

    // si le fantome est sur son dernier déplacement fictif
    else if (ghost.cooldown == 1) {
        if (ghost.currentMove == kUp)
            ghost.nextPos = {ghost.posMat.first-1, ghost.posMat.second};
        else if (ghost.currentMove == kDown)
            ghost.nextPos = {ghost.posMat.first+1, ghost.posMat.second};
        else if (ghost.currentMove == kLeft)
            ghost.nextPos = {ghost.posMat.first, ghost.posMat.second-1};
        else if (ghost.currentMove == kRight)
            ghost.nextPos = {ghost.posMat.first, ghost.posMat.second+1};
        move(mat, ghost.posMat, ghost.nextPos, ghost); // déplacement réel
        ghost.currentMove = 'p';
        ghost.cooldown = 0;
    }

    // si le cooldown n'est pas fini faire des déplacements fictif
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
