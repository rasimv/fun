#ifndef __GAME_DEFS_H
#define __GAME_DEFS_H

#include <utility>

namespace Game
{
    typedef std::pair<bool, bool> BoolPair;

    extern const float s_width;         //Ширина области вывода, "м"
    extern const float s_height;        //Высота области вывода, "м"

    extern const float s_g;             //Ускорение свободного падения, "м"/с^2
    extern const float s_v;             //Скороподъемность птицы, "м"/с

    extern const float s_hv;            //Скорость полета птицы, "м"/с

    extern const float s_r;             //Радиус птицы, "м"

    extern const float s_birdPos;       //Положение птицы на экране (по горизонтали), "м"

    extern const float s_blockWidth;    //Толщина блока, "м"
    extern const float s_blocksVGap;    //Зазор между верхним и нижним блоками, "м"
    extern const float s_blocksHGap;    //Расстояние между блоками по горизонтали
                                        //(s_blockWidth + s_blocksHGap -- шаг блоков по горизонтали),
                                        //"м"

    extern const float s_blockCount;    //Число пар блоков
                                        //(минимальное количество видимых одновременно)

    extern const float s_sa;            //Фактор положения крыла по-умолчанию, радиан
    extern const float s_w;             //Скорость изменения фактора положения крыла
                                        //("быстрота" махания крыла), радиан/с.
                                        //2π - один цикл в секунду
}

#endif //__GAME_DEFS_H
