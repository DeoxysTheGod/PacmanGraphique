#ifndef TYPE_H
#define TYPE_H

#include "mingl/mingl.h"

#include "mingl/shape/rectangle.h"
#include "mingl/shape/circle.h"
#include "mingl/shape/line.h"
#include "mingl/shape/triangle.h"

#include <vector>


using namespace std;
using namespace nsShape;
using namespace nsGraphics;

typedef pair<pair<unsigned, unsigned>, pair<unsigned,unsigned>> pacMousePos;
typedef pair<unsigned, unsigned> Position;

#endif // TYPE_H
