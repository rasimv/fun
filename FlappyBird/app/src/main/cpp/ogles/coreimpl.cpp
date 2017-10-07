#include "../game/core.h"
#include <cassert>
#include "coredd.h"
#include "dcimpl.h"
#include <cstdio>
#include "oglaux.h"

namespace Game
{
    //Вспомогательная функция вывода текста пиксельным шрифтом:
    //a_t - текст, a_s - число символов,
    //a_x, a_y, a_w, a_h - координаты лев. нижн. угла и размеры прямоугольной области, куда
    //будет выведен текст
    void drawText(DCImpl *a_dc, CoreDD *a_dd,
                  const char *a_t, size_t a_s, float a_x, float a_y, float a_w, float a_h)
    {
        assert(a_dc != nullptr && a_dd != nullptr && a_t != nullptr);
        for (size_t i = 0; i < a_s; i++)
        {
            const GLfloat l_transf[] = {
                    a_w / (a_s * (CoreDD::s_charWI + CoreDD::s_charW)), 0, 0, 0,
                    0, a_h / CoreDD::s_charH, 0, 0,
                    0, 0, 1, 0,
                    a_x + i * a_w / a_s, a_y, 0, 1 };
            ::glUniformMatrix4fv(a_dc->transf(), 1, GL_FALSE, l_transf);
            auto q = static_cast<const unsigned int>(a_t[i]);
            drawBuffer(a_dd->buf(q), 0, GLsizei(a_dd->size(q)));
        }
    }

    //Реализация функции подготовки отрисовки
    void Core::prepareDraw(DrawContext *a_dc, DrawData *a_dd)
    {
        assert(dynamic_cast<DCImpl *>(a_dc) != nullptr && dynamic_cast<CoreDD *>(a_dd) != nullptr);
        DCImpl *const l_dc = static_cast<DCImpl *>(a_dc);
        CoreDD *const l_dd = static_cast<CoreDD *>(a_dd);
        l_dd->init(l_dc);
    }

    //Реализация функции отрисовки очков
    void Core::drawScore(DrawContext *a_dc, DrawData *a_dd)
    {
        assert(dynamic_cast<DCImpl *>(a_dc) != nullptr && dynamic_cast<CoreDD *>(a_dd) != nullptr);
        DCImpl *const l_dc = static_cast<DCImpl *>(a_dc);
        CoreDD *const l_dd = static_cast<CoreDD *>(a_dd);
        char l_t[20] = { 0 };
        const int l_s = ::sprintf(l_t, "%ld", m_score);
        //Ширина символа будет 1/14 ширины всей области отображения,
        //высота символа - 1/20 высоты всей области отображения
        static const float l_xFrac = s_width / 14, l_yFrac = s_height / 20;
        drawText(l_dc, l_dd, l_t, size_t(l_s),
                 -s_width / 2 + l_xFrac, s_height / 2 - 2 * l_yFrac, l_s * l_xFrac, l_yFrac);
    }

    //Реализация функции отрисовки экрана запуска: текст "START" в прямоугольнике;
    //размеры заданы коэффициентами к размеру всей области отображения
    void Core::drawStart(DrawContext *a_dc, DrawData *a_dd)
    {
        assert(dynamic_cast<DCImpl *>(a_dc) != nullptr && dynamic_cast<CoreDD *>(a_dd) != nullptr);
        DCImpl *const l_dc = static_cast<DCImpl *>(a_dc);
        CoreDD *const l_dd = static_cast<CoreDD *>(a_dd);

        const GLfloat l_transf1[] = { 0.4f * Game::s_width, 0, 0, 0,
                                      0, 0.08f * Game::s_height, 0, 0,
                                      0, 0, 1, 0,
                                      0, 0, 0, 1 };
        ::glUniformMatrix4fv(l_dc->transf(), 1, GL_FALSE, l_transf1);
        ::drawBuffer(l_dd->rectBuf(), 0, 2 * 3);

        drawText(l_dc, l_dd, "START", 5, -0.3f * Game::s_width, -0.045f * Game::s_height,
                 0.6f * Game::s_width, 0.09f * Game::s_height);
    }

    //Реализация функции отрисовки экрана перезапуска: текст "RESTART" в прямоугольнике;
    //размеры заданы коэффициентами к размеру всей области отображения
    void Core::drawRestart(DrawContext *a_dc, DrawData *a_dd)
    {
        assert(dynamic_cast<DCImpl *>(a_dc) != nullptr && dynamic_cast<CoreDD *>(a_dd) != nullptr);
        DCImpl *const l_dc = static_cast<DCImpl *>(a_dc);
        CoreDD *const l_dd = static_cast<CoreDD *>(a_dd);

        const GLfloat l_transf1[] = { 0.4f * Game::s_width, 0, 0, 0,
                                      0, 0.08f * Game::s_height, 0, 0,
                                      0, 0, 1, 0,
                                      0, 0, 0, 1 };
        ::glUniformMatrix4fv(l_dc->transf(), 1, GL_FALSE, l_transf1);
        ::drawBuffer(l_dd->rectBuf(), 0, 2 * 3);

        drawText(l_dc, l_dd, "RESTART", 7, -0.3f * Game::s_width, -0.035f * Game::s_height,
                 0.6f * Game::s_width, 0.07f * Game::s_height);
    }
}
