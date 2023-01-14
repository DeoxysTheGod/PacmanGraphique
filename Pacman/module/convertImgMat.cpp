#include <iostream>
#include <fstream>
#include <vector>
#include "type.h"
#include "convertImgMat.h"

using namespace std;

UIntMat convertMat (const string & nomImg)
{
    ifstream img(nomImg);
    if (!img.is_open()) {
        UIntMat errorMat (0);
        return errorMat;
    }
    string dump;
    unsigned row(0), column (0);

    rgbPixelColor currentPixel;

    img >> dump;
    img >> row;
    img >> column;
    img >> dump;
    UIntMat mat (column, UIntVec(row, 0));
    for (unsigned i (0); i < mat.size(); ++i) {
        for (unsigned j (0); j < mat[i].size(); ++j) {
            img >> currentPixel.r;
            img >> currentPixel.g;
            img >> currentPixel.b;
            if (currentPixel.r == 0 && currentPixel.g == 0 && currentPixel.b == 0)
                mat[i][j] = 1;
            else if (currentPixel.r == 255 && currentPixel.g == 255 && currentPixel.b == 255)
                mat[i][j] = 2;
            else if (currentPixel.r == 255 && currentPixel.g == 255 && currentPixel.b == 0)
                mat[i][j] = 3;
            else if (currentPixel.r == 255 && currentPixel.g == 0 && currentPixel.b == 255)
                mat[i][j] = 0;
            else if (currentPixel.r == 255 && currentPixel.g == 0 && currentPixel.b == 0)
                mat[i][j] = 9;
            else if (currentPixel.r == 0 && currentPixel.g == 255 && currentPixel.b == 0)
                mat[i][j] = 8;
            else if (currentPixel.r == 0 && currentPixel.g == 255 && currentPixel.b == 255)
                mat[i][j] = 7;
            else if (currentPixel.r == 0 && currentPixel.g == 0 && currentPixel.b == 255)
                mat[i][j] = 5;
            else
                mat[i][j] = 0;
        }
    }
    return mat;
}

void importAllPlot (plotHolder & allPlot, const string & baseName) {
    unsigned cpt (1);
    string fullName;
    UIntMat tmpMat;
    while (true) {
        fullName = "../Pacman/carte/" + baseName + std::to_string(cpt) + ".ppm";
        cout << fullName << endl;
        tmpMat = convertMat(fullName);
        if (tmpMat.size() == 0) {
            cout << "error" << endl;
            break;
        }
        else {
            allPlot[cpt] = tmpMat;
            ++cpt;
        }
    }
}
