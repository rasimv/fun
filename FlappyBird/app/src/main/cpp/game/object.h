#ifndef __GAME_OBJECT_H
#define __GAME_OBJECT_H

#include "drawdata.h"
#include "drawcontext.h"

namespace Game
{
    class Core;

    //Базовый класс для игровых объектов
    class Object
    {
        Object(const Object &) = delete;
        Object &operator =(const Object &) = delete;

    public:
        Object(Core *a_core, DrawData *a_dd);
        virtual ~Object() {}

        virtual void evol(float a_dt);              //Функция рассчета нового состояния объекта
        virtual void postEvol();                    //Функция для действий после evol (напр. кэширование)
        virtual void initDraw(DrawContext *a);      //Функция подготовки средств отрисовки
        virtual void draw(DrawContext *a);          //Функция отрисовки
        virtual void pressed();                     //Функция обработки прикосновения
        virtual void released();                    //Функция обработки отпускания

    protected:
        Core *m_core;                       //Указатель на объект "ядра" игры
        DrawData *m_dd;                     //Указатель на объект, содержащий вспомогательные
                                            //данные, используемые при отрисовке
    };
}

#endif //__GAME_OBJECT_H
