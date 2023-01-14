#include "remplissageMat.h"

using namespace std ;

bool coordIsForbiddenIn (vector<unsigned> & listForbidden , unsigned & coord1 , unsigned & coord2)
{
    bool checkCoord1 (true);
    bool checkCoord2 (true);

    for (unsigned i(0) ; i < listForbidden.size() ; ++i)
    {
        if (coord1 == listForbidden[i])
            checkCoord1 = false ;
        if (coord2 == listForbidden[i])
            checkCoord2 = false ;
    }
    if (checkCoord1 || checkCoord2)
        return false ;
    else
        return true ;
}

void fillMat (UIntMat & Mat)
{
    vector<unsigned> forbiddencoord {12 ,13 ,14 ,15 ,16 ,17 ,18} ;

    for (unsigned i(0) ; i < Mat.size() ; ++i)
    {
        for (unsigned j(0) ; j < Mat[i].size() ; ++j)
        {
            if (((i == 0) || (i == Mat.size() - 1)) && (Mat[i][j] == 0)) //cas de case vide en haut de map (tp)
                Mat[i][j] = 7;
            else if (((j == 0) || (j == Mat.size() - 1))&& (Mat[i][j] == 0)) //cas de case vide en coté de map (tp)
                Mat[i][j] = 7 ;

            else if (coordIsForbiddenIn(forbiddencoord , i , j) && (Mat[i][j] == 0))
                continue ;

            else if (Mat[i][j] == 2)
                Mat[i][j] = 3 ;

            else if (Mat[i][j] == 0)
                Mat[i][j] = 2 ;
        }
    }
    Mat[27][15] = 8 ;
    Mat[15][15] = 9 ;
}
