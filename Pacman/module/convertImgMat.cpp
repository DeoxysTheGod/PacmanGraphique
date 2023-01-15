#include <iostream>
#include <fstream>
#include <vector>
#include "type.h"
#include "convertImgMat.h"

using namespace std;

UIntMat convertMat (const string & nomImg)
{
    ifstream img(nomImg); // essai d'ouvrir l'image
    if (!img.is_open()) { // si elle ne s'ouvre pas c'est qu'elle n'existe probablement pas
        UIntMat errorMat (0);
        return errorMat; // on retourne une matrice vide pour signifier qu'on arrete la recherche dans le fichier
    }
    string dump; // pour lire les informations inutiles du fichier
    unsigned row(0), column (0); // recupère la taille de la grille qui est contenu dans le fichier .ppm

    rgbPixelColor currentPixel;

    // lit les 3 premières lignes du fichier
    img >> dump;
    img >> row;
    img >> column;
    img >> dump;
    UIntMat mat (column, UIntVec(row, 0));
    for (unsigned i (0); i < mat.size(); ++i) {
        for (unsigned j (0); j < mat[i].size(); ++j) {
            // récupère les 3 valeurs du pixel
            img >> currentPixel.r;
            img >> currentPixel.g;
            img >> currentPixel.b;
            // en fonction de cette valeur on va mettre un chiffre différent dans notre matrice de sortie
            if (currentPixel.r == 0 && currentPixel.g == 0 && currentPixel.b == 0) // Noir
                mat[i][j] = 1; // Mur
            else if (currentPixel.r == 255 && currentPixel.g == 255 && currentPixel.b == 255) // Blanc
                mat[i][j] = 2; // Beignet
            else if (currentPixel.r == 255 && currentPixel.g == 255 && currentPixel.b == 0) // Jaune
                mat[i][j] = 3; // Pacgum
            else if (currentPixel.r == 255 && currentPixel.g == 0 && currentPixel.b == 255) // Magenta
                mat[i][j] = 0; // Case vide
            else if (currentPixel.r == 255 && currentPixel.g == 0 && currentPixel.b == 0) // Rouge
                mat[i][j] = 9; // Position de départ du fantome
            else if (currentPixel.r == 0 && currentPixel.g == 255 && currentPixel.b == 0) // Vert
                mat[i][j] = 8; // Position de d&part du pacman
            else if (currentPixel.r == 0 && currentPixel.g == 255 && currentPixel.b == 255) // Cyan
                mat[i][j] = 7; // Téléporteur
            else if (currentPixel.r == 0 && currentPixel.g == 0 && currentPixel.b == 255) // Bleu
                mat[i][j] = 5; // Mur de fermeture de la zone du fantome
            else // Si la couleur n'est pas connu
                mat[i][j] = 1; // Mur
        }
    }
    return mat; // on retourne notre matrice qui sera une grille de jeu possible pour notre pacman
}

void importAllPlot (plotHolder & allPlot, const string & baseName) {
    unsigned cpt (1);
    string fullName;
    UIntMat tmpMat;
    // crée des chemins pour lire toutes les cartes ("../Pacman/carte/baseName1.ppm", "../Pacman/carte/baseName2.ppm", etc
    while (true) {
        fullName = "../Pacman/carte/" + baseName + std::to_string(cpt) + ".ppm";
        cout << fullName << endl;
        tmpMat = convertMat(fullName);
        if (tmpMat.size() == 0) { // si la matrice est vide c'est qu'il n'y a plus de fichier à lire
            cout << "error" << endl;
            break;
        }
        else {
            allPlot[cpt] = tmpMat; // ajoute chaque carte dans la map allPlot avec comme clé un entier naturel
            ++cpt;
        }
    }
}

void randomPlot (UIntMat & mat, const plotHolder & allPlot) {
    unsigned maxRand = allPlot.size();
    mat = allPlot.find(rand()%maxRand+1)->second;
}

unsigned countBeignet (const UIntMat & mat) {
    unsigned cpt (0);
    for (auto & i : mat) {
        for (auto & j : i) {
            if (j == 2 || j == 3 || j == 4)
                ++cpt;
        }
    }
    return cpt;
}
