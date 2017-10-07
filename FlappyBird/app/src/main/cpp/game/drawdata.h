#ifndef __GAME_DRAWDATA_H
#define __GAME_DRAWDATA_H

namespace Game
{
    //Базовый класс объекта, содержащего вспомогательные данные, используемые при отрисовке
    class DrawData
    {
        DrawData(const DrawData &) = delete;
        DrawData &operator =(const DrawData &) = delete;

    public:
        DrawData();
        virtual ~DrawData();
    };
}

#endif //__GAME_DRAWDATA_H
