#include "birddd.h"

namespace Game
{
    const Vertex BirdDD::s_tri[] =
            {
                    { -1.6f, -0.3f, 0.5f, 0, 0 }, { -0.7f, -0.1f, 0.5f, 0, 0 }, { -1.6f, 0.1f, 0.5f, 0, 0 },
                    { 0.7f, -0.3f, 0.5f, 0, 0 }, { 1.6f, 0.3f, 0.5f, 0, 0 }, { 0.7f, 0.7f, 0.5f, 0, 0 },
#include "circle.inc"       //См. ConsoleApplication3.cpp
                    { 0.3f, 0.5f, 1, 1, 1 }, { 0.5f, 0.7f, 1, 1, 1 }, { 0.1f, 0.7f, 1, 1, 1 },
                    { 0.3f, 0.6f, 0, 0, 0 }, { 0.4f, 0.7f, 0, 0, 0 }, { 0.2f, 0.7f, 0, 0, 0 }
            };

    const Vertex BirdDD::s_wingTri[] =
            { { -0.8f, 0, 0.5f, 0, 0 }, { 0.2f, 0, 0.5f, 0, 0 }, {-0.3f, 0.6f,  0.5f, 0, 0} };
}
