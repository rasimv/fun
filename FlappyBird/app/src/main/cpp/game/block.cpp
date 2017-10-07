#include "block.h"
#include "defs.h"
#include <cassert>
#include <cstdlib>
#include "core.h"

namespace Game
{
    Block::Block(Core *a, float a_x, float a_y, float a_w, float a_h)
        :Object(a, createDD()), m_x(a_x), m_y(a_y), m_w(a_w), m_h(a_h)
    {}

    Block::~Block() { delete m_dd; }

    std::pair<float, float> Block::center() const
    {
        return std::pair<float, float>(m_x + m_w / 2, m_y + m_h / 2);
    }

    void Block::evol(float a_dt)
    {
        assert(m_core != nullptr);
        const float l_x = m_x - m_core->hv() * a_dt;
        if (l_x + m_w >= -s_width / 2)
            m_x = l_x;
        else    //Если блок вышел за пределы левого края игровой области...
        {
            Block *const l_right = m_core->mostRight(this);     //Найти самый крайний справа блок:
                                                                //верхний, если this верхний;
                                                                //нижний, если this нижний
            assert(l_right != nullptr);
            m_x = l_right->x() + s_blockWidth / 2 + s_blocksHGap;   //Перестановка блока в конец
            Block *const l_pair = m_core->findPair(this);           //Найти пару
            const bool l_top = center().second > 0;                 //true -- этот блок верхний
            if (l_pair == nullptr)
            {   //Если пары нет, то при перестановке в конец задать новую (случайную) высоту
                const float l_new = s_height / 2 * ((float(::rand()) / RAND_MAX) - 0.5f);
                m_y = l_top ? l_new + s_blocksVGap / 2 : -s_height / 2;
                m_h = l_top ? s_height / 2 - m_y : l_new - s_blocksVGap / 2 + s_height / 2;
            }
            else
            {   //Если пара уже есть, то при перестановке в конец согласовать высоту с парой
                m_y = l_top ? l_pair->y() + l_pair->h() + s_blocksVGap : -s_height / 2;
                m_h = l_top ? s_height / 2 - m_y : l_pair->y() - s_blocksVGap - m_y;
            }
        }
    }
}
