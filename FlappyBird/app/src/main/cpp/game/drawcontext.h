#ifndef __GAME_DRAWCONTEXT_H
#define __GAME_DRAWCONTEXT_H

namespace Game
{
    //Базовый класс объекта, предоставляющего контекст отрисовки
    class DrawContext
    {
        DrawContext(const DrawContext &) = delete;
        DrawContext &operator =(const DrawContext &) = delete;

    public:
        DrawContext();
        virtual ~DrawContext();
    };
}

#endif //__GAME_DRAWCONTEXT_H
