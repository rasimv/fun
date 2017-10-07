#ifndef __GAME_CORE_H
#define __GAME_CORE_H

#include "object.h"
#include "drawcontext.h"
#include "defs.h"
#include <list>

namespace Game
{
    class Object;
    class Bird;
    class Block;

    //Класс "ядра" игры
    class Core
    {
        friend class Object;
        friend class Bird;
        friend class Block;

        Core(const Core &) = delete;
        Core &operator =(const Core &) = delete;

    public:
        //Текущее состояние
        enum State
        {
            S_PRESTART,             //Ожидание начала игры (предстартовое состояние)
            S_PRESTART_PRESSED,     //Ожидание отпускания после нажатия (для запуска игр. процесса)
            S_ACTION,               //Игра
            S_HIT,                  //Падение после столкновения с блоком или касания нижнего края
            S_RESTART,              //Ожидание перезапуска игры 
            S_RESTART_PRESSED       //Ожидание отпускания (для перезапуска игрового процесса)
        };

        Core(DrawData *a_dd);
        ~Core();

        void evol(float a_dt);              //См. Game::Object
        void initDraw(DrawContext *a);      //
        void draw(DrawContext *a);          //
        void pressed();                     //
        void released();                    //

        //Объявления методов, который должны быть реализованы вовне (в "клиенте")
        void prepareDraw(DrawContext *a_dc, DrawData *a_dd);    //Подготовка отрисовки
        void drawScore(DrawContext *a_dc, DrawData *a_dd);      //Отрисовка очков
        void drawStart(DrawContext *a_dc, DrawData *a_dd);      //Отрисовка экрана запуска
        void drawRestart(DrawContext *a_dc, DrawData *a_dd);    //Отрисовка экрана перезапуска

    private:
        float hv() const { return m_state == S_ACTION ? s_hv : 0; }     //Горизонтальная скорость:
                                                                        //движение только в состоянии
                                                                        //S_ACTION
        void clear();       //Уничтожить все объекты
        void generate();    //Сформировать исходную конфигурацию объектов
        void init();        //Инициализация нового сеанса игры

        Block *mostRight(Block *a);     //Найти крайний справа блок: верхн. -- если этот (this) верхн.,
                                        //нижн. -- если этот (this) нижн.
        Block *findPair(Block *a);      //Найти пару: верхн. -- если этот (this) блок нижн.,
                                        //нижн. -- если этот (this) блок верхн.

        static bool hit(Bird *a_one, Block *a_another);     //Проверить птицу на столкновение с блоком

        BoolPair hit(Bird *a);          //Проверить на столкн. (first) и на нахожд. в зазоре (second)
        void score() { m_score++; }     //Нарастить очки
        void hit(bool a) { m_hit = a; }     //Уведомление о столкновении
        bool hit() const { return m_hit; }  //Получить признак столкновения
        void fell(bool a) { m_fell = a; }   //Уведомление о конце падения после столкновения или
                                            //касания нижн. края игровой области

        State m_state;                  //Переменная состояния
        std::list<Object *> m_list;     //Список игровых объектов
        long m_score;                   //Очки
        bool m_hit, m_fell;             //Признаки столкновения/касания нижн. края и падения

        DrawData *m_dd;
    };
}

#endif //__GAME_CORE_H
