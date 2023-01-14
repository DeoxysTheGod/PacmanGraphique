#ifndef REMPLISSAGEMAT_H
#define REMPLISSAGEMAT_H

#include <iostream>
#include <string>
#include <vector>
#include "type.h"

bool coordIsForbiddenIn (std::vector<unsigned> & listForbidden , unsigned & coord1 , unsigned & coord2) ;

void fillMat (UIntMat & Mat) ;

#endif // REMPLISSAGEMAT_H
