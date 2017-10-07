#include "core.h"
#include <cassert>
#include "bird.h"
#include "block.h"
#include "auxiliary.h"
#include <memory>

namespace Game
{
    Core::Core(DrawData *a_dd)
        :m_dd(a_dd), m_state(S_PRESTART)
    {
        assert(m_dd != nullptr);
    }

    Core::~Core()
    {
        delete m_dd;
        clear();
    }

    void Core::evol(float a_dt)
    {
        if (m_state == S_ACTION || m_state == S_HIT)
        {   //Перерасчет сост. объектов нужен в процессе игры (S_ACTION) и падения птицы (S_HIT)
            for (auto i : m_list) i->evol(a_dt);
            for (auto i : m_list) i->postEvol();
            if (m_hit) m_state = S_HIT;         //Столкн. или касание нижн. края -- перейти в S_HIT
            if (m_fell) m_state = S_RESTART;    //Падение закончилось -- перейти в S_RESTART
        }
    }

    void Core::initDraw(DrawContext *a)
    {
        //Инициализация средств отрисовки
        prepareDraw(a, m_dd);
        for (auto i : m_list) i->initDraw(a);
    }

    void Core::draw(DrawContext *a)
    {
        //Отрисовка объектов в состояниих игрового процесса, падения птицы или ожидания перезапуска
        if (m_state == S_ACTION || m_state == S_HIT || m_state == S_RESTART)
        {
            for (auto i : m_list) i->draw(a);
            drawScore(a, m_dd);
        }
        if (m_state == S_PRESTART) drawStart(a, m_dd);
        if (m_state == S_RESTART) drawRestart(a, m_dd);
    }

    void Core::pressed()
    {
        if (m_state == S_PRESTART)                  //Нажатие в процессе ожидания начала игры --
            m_state = S_PRESTART_PRESSED;           //перейти в состояние S_PRESTART_PRESSED
        else if (m_state == S_ACTION)               //Известить объекты о нажатии
            for (auto i : m_list) i->pressed();     //в процессе игры (S_ACTION)
        else if (m_state == S_RESTART)              //Нажатие в процессе ожидания перезапуска --
            m_state = S_RESTART_PRESSED;            //перейти в состояние S_RESTART_PRESSED
    }

    void Core::released()
    {
        if (m_state == S_PRESTART_PRESSED)          //Отпускание в состоянии ожидания начала игры --
        {                                           //
            init();                                 //инициализация сеанса игры,
            m_state = S_ACTION;                     //перейти в состояние игр. процесса (S_ACTION)
        }
        else if (m_state == S_ACTION)               //Известить объекты об отпускании
            for (auto i : m_list) i->released();    //в процессе игры (S_ACTION)
        else if (m_state == S_RESTART_PRESSED)      //Отпускание произошло в сост. ожид. перезапуска --
        {                                           //
            init();                                 //инициализация сеанса игры,
            m_state = S_ACTION;                     //перейти в состояние игр. процесса
        }
    }

    //Уничтожение всех объектов и очищение списка объектов
    void Core::clear() { for (auto i : m_list) delete i; m_list.clear(); }

    //Сгенерировать исходную конфигурацию объектов
    void Core::generate()
    {
        //Создать блоки
        for (int i = 0; i < s_blockCount; i++)
        {
            const float l_shift = s_width / 2 + i * (s_blocksHGap + s_blockWidth / 2);
            std::unique_ptr<Block> l_new(new Block(this, l_shift, -s_height / 2, s_blockWidth, (s_height - s_blocksVGap) / 2));
            m_list.push_back(l_new.get());  l_new.release();
            l_new.reset(new Block(this, l_shift, s_blocksVGap / 2, s_blockWidth, (s_height - s_blocksVGap) / 2));
            m_list.push_back(l_new.get());  l_new.release();
        }
        //Создать птицу
        std::unique_ptr<Bird> l_new(new Bird(this, s_birdPos, 0, s_r, 0, -Game::s_g));
        m_list.push_back(l_new.get()); l_new.release();
    }

    //Инициализция сеанса игры
    void Core::init()
    {
        clear();                                                //Уничтожение ранее созданных объектов,
        generate();                                             //создание новых
        m_score = 0;                                            //Сброс очков
        m_hit = false; m_fell = false;                          //Сбросить признаки
    }

    //Найти крайний справа блок: верхний, если этот блок (this) верхний;
    //соответственно нижний, если этот блок нижний
    Block *Core::mostRight(Block *a)
    {
        assert(a != nullptr);
        Block *r = nullptr;
        for (auto i : m_list)
        {
            Block *const b = dynamic_cast<Block *>(i);
            if (b == nullptr) continue;                         //Пропустить, если объект -- не блок
            if (a->center().second * b->center().second < 0)    //Если верт. координаты центров блоков
                continue;                                       //разного знака, то значит
                                                                //один -- верхний, другой -- нижний
            if (r == nullptr || r->x() <= b->x())               //Если тек. блок (b) правее, то
                r = b;                                          //запомнить
        }
        assert(a != r);
        return r;
    }

    //Поиск пары: найти нижний, если этот блок (this) верхний;
    //найти верхний, если этот блок (this) нижний
    Block *Core::findPair(Block *a)
    {
        assert(a != nullptr);
        for (auto i : m_list)
        {
            Block *const b = dynamic_cast<Block *>(i);      //Пропустить объект,
            if (b == nullptr || a == b) continue;           //если он не блок или тот же самый
            if (a->x() == b->x())
                return b;
        }
        return nullptr;
    }

    //Выявление пересечения птицы (a_one) и блока (a_another)
    bool Core::hit(Bird *a_one, Block *a_another)
    {
        assert(a_one != nullptr && a_another != nullptr);
        return Game::circleIntersectsRect(a_one->x(), a_one->y(), a_one->r(),
            a_another->x(), a_another->y(), a_another->w(), a_another->h());
    }

    //Выявление пересечения птицы с блоком (first) и проверка на нахождение в зазоре (second)
    BoolPair Core::hit(Bird *a)
    {
        assert(a != nullptr);
        BoolPair r;
        for (auto i : m_list)
        {
            Block *const b = dynamic_cast<Block *>(i);
            if (b == nullptr) continue;                     //Пропустить, если не блок
            if (hit(a, b))                                  //Тек. блок пересекается с птицей?
                return BoolPair(true, r.second);
            //Проверка на нахождение птицы в зазоре между верхним и нижним блоками
            if (b->center().second < 0 && a->x() > b->x() && a->x() < b->x() + b->w())
                r.second = true;
        }
        return r;
    }
}
