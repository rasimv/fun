#include "coredd.h"

namespace Game
{
    const Vertex CoreDD::s_charTri[] =
            {
#include "chartri.inc"      //См. ConsoleApplication2.cpp
            };

    const std::pair<size_t, size_t> CoreDD::s_charBE[] =
            {
#include "charbe.inc"       //См. ConsoleApplication2.cpp
            };

    const Vertex CoreDD::s_rectTri[] =
            {
                    { -1, -1, 0, 0, 1 }, { 1, -1, 0, 0, 1 }, { 1, 1, 0, 0, 1 },
                    { -1, -1, 0, 0, 1 }, { 1, 1, 0, 0, 1 }, { -1, 1, 0, 0, 1 }
            };
}
