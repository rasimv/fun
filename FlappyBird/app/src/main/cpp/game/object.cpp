#include "object.h"

namespace Game
{
    Object::Object(Core *a_core, DrawData *a_dd)
        :m_core(a_core), m_dd(a_dd)
    {}

    void Object::evol(float a_dt) {}
    void Object::postEvol() {}
    void Object::initDraw(DrawContext *a) {}
    void Object::draw(DrawContext *a) {}
    void Object::pressed() {}
    void Object::released() {}
}
