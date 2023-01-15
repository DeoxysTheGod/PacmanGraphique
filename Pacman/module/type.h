#ifndef TYPE_H
#define TYPE_H

#include "mingl/mingl.h"

#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"

#include <vector>
#include <map>
#include <string>


using namespace std;
using namespace nsShape;
using namespace nsGraphics;

typedef pair<pair<unsigned, unsigned>, pair<unsigned,unsigned>> pacMousePos;
typedef pair<unsigned, unsigned> Position;

typedef vector<unsigned> UIntVec;
typedef vector<UIntVec> UIntMat;
typedef map<unsigned, UIntMat> plotHolder;

//Ces types appartiennent à Monsieur Casali
typedef std::vector <char> CVLine;
typedef std::vector <CVLine> CMat;

/*!
 * \brief The rgbPixelColor class : elle permet de grouper les trois valeurs d'un pixel
 */
struct rgbPixelColor {
    unsigned r, g, b;
};

/*!
 * \brief The authorizedKeyPacman class : permet de dire qu'elles sont les touches à lire pour le pacman dans le fichier
 * config.yaml
 */
struct authorizedKeyPacman {
    const std::vector <std::string> VParamChar {"PKeyUp", "PKeyDown", "PKeyLeft", "PKeyRight"};
};

/*!
 * \brief The authorizedKeyGhost class : permet de dire qu'elles sont les touches à lire pour le fantome dans le fichier
 * config.yaml
 */
struct authorizedKeyGhost {
    const std::vector <std::string> VParamChar {"GKeyUp", "GKeyDown", "GKeyLeft", "GKeyRight"};
};

#endif // TYPE_H
