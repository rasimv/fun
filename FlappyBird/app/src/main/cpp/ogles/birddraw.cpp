#include "../game/bird.h"
#include <cassert>
#include "birddd.h"
#include "dcimpl.h"
#include "../game/defs.h"
#include "../game/auxiliary.h"
#include "oglaux.h"

namespace Game
{
    DrawData *Bird::createDD()
    {
        return new BirdDD();
    }

    void Bird::postEvol()
    {}

    void Bird::initDraw(DrawContext *a)
    {
        assert(dynamic_cast<BirdDD *>(m_dd) != nullptr);
        BirdDD *const l_dd = static_cast<BirdDD *>(m_dd);
        l_dd->genBuf();
        l_dd->loadBuf();
        l_dd->setInited(true);
    }

    void Bird::draw(DrawContext *a)
    {
        assert(dynamic_cast<DCImpl *>(a) != nullptr);
        assert(dynamic_cast<BirdDD *>(m_dd) != nullptr);
        BirdDD *const l_dd = static_cast<BirdDD *>(m_dd);
        if (!l_dd->inited()) initDraw(a);
        DCImpl *l_dc = static_cast<DCImpl *>(a);

        //Отрисовка статич. части
        const GLfloat l_transf1[] = { Game::s_r, 0, 0, 0,
                                      0, Game::s_r, 0, 0,
                                      0, 0, 1, 0,
                                      m_x, m_y, 0, 1 };
        ::glUniformMatrix4fv(l_dc->transf(), 1, GL_FALSE, l_transf1);
        ::drawBuffer(l_dd->buf1(), 0, 3 + 3 + 3 * 40 + 3 + 3);

        //Отрисовка статич. крыла
        const GLfloat l_transf2[] = { Game::s_r, 0, 0, 0,
                                      0, Game::s_r * wing(), 0, 0,
                                      0, 0, 1, 0,
                                      m_x, m_y, 0, 1 };
        ::glUniformMatrix4fv(l_dc->transf(), 1, GL_FALSE, l_transf2);
        ::drawBuffer(l_dd->buf2(), 0, 3);
    }
}
