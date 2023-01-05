#include <iostream>
#include <fstream>
#include <vector>
#include "type.h"

using namespace std;

void convertMat (CMat & Mat , const string & nomImg)
{
    ifstream img(nomImg);
    string dump ;
    unsigned cpt(0) , row(0) , count(0);
    char currentTile;

    Mat.resize(21);
    for (unsigned i(0) ; i < Mat.size() ; ++i)
        Mat[i].resize(21);

    for (unsigned i(0) ; i < 3 ; ++i)
        getline(img , dump);

    for (string line ; getline(img , line) ; )
    {
        while (cpt < line.size())
        {
            currentTile = line[cpt];
            if (currentTile == '2')
            {
                Mat[row][count] = '0' ;
                cpt += 12 ;
            }
            else if (currentTile == '0')
            {
                Mat[row][count] = '1' ;
                cpt += 6 ;
            }
            count += 1 ;
        }
        cpt = 0;
        count = 0;
        ++row;
    }
}
