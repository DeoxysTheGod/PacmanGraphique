#include "parameters.h"

void loadParameter (sPacman & pacman, authorizedKeyPacman & authKey)
{
    ifstream ifs ("../G1_Beauquier_Rossi_Momy_Portelli_Marie/autre/config.yaml");
    char valChar;
    string buf;
    for (string key ; ifs >> key ; ) {
        ifs >> buf; // remove ':'
        if (authKey.VParamChar.end() != find(authKey.VParamChar.begin(), authKey.VParamChar.end(), key)) {
            ifs >> valChar;
            pacman.MapParamChar[key] = tolower(valChar);
        }
        else
            ifs >> buf;
    }
}

void loadParameter (sGhost & ghost, authorizedKeyGhost & authKey)
{
    ifstream ifs ("../G1_Beauquier_Rossi_Momy_Portelli_Marie/autre/config.yaml");
    char valChar;
    string buf;
    for (string key ; ifs >> key ; ) {
        ifs >> buf; // remove ':'
        if (authKey.VParamChar.end() != find(authKey.VParamChar.begin(), authKey.VParamChar.end(), key)) {
            ifs >> valChar;
            ghost.MapParamChar[key] = tolower(valChar);
        }
        else
            ifs >> buf;
    }
}
