#ifndef REMPLISSAGEMAT_H
#define REMPLISSAGEMAT_H

#include "../PacMan/Correc_Prof/type.h"
#include <string>
#include <vector>

bool coordIsForbiddenIn (std::vector<unsigned> & listForbidden , unsigned & coord1 , unsigned & coord2) ;

void fillMat (CMat & Mat) ;

#endif // REMPLISSAGEMAT_H
