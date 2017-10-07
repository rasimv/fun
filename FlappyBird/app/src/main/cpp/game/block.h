#ifndef __GAME_BLOCK_H
#define __GAME_BLOCK_H

#include "object.h"
#include <utility>

namespace Game
{
    //Класс реализующий блок (препятствие)
    class Block : public Object
    {
    public:
        Block(Core *a = 0, float a_x = 0, float a_y = 0, float a_w = 0, float a_h = 0);
        virtual ~Block();

        float x() const { return m_x; }
        float y() const { return m_y; }
        float w() const { return m_w; }
        float h() const { return m_h; }
        std::pair<float, float> center() const;     //Вернуть координаты центра блока

        virtual void evol(float a_dt) override;
        virtual void postEvol() override;
        virtual void initDraw(DrawContext *a) override;
        virtual void draw(DrawContext *a) override;

    private:
        DrawData *createDD();   //Функция создания объекта, содержащего данные
                                //нужные для отрисовки

        float m_x, m_y;         //Координаты левого нижнего угла блока 
        float m_w, m_h;         //Толщина и высота блока
    };
}

#endif //__GAME_BLOCK_H
