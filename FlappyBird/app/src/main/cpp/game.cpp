#include "game.h"
#include "game/defs.h"
#include <cassert>
#include "game/core.h"
#include "ogles/oglaux.h"
#include <memory>
#include "ogles/coredd.h"

//Текст тривиального вершинного шейдера:
//transf - матрица для преобразований координат при отрисовке (сдвиг, масштабирование),
//projection - матрица проецирования игрового пространства (Game::s_width x Game::s_height) на область отображения (2 x 2)
static const char *s_vertexShader =     "attribute vec2 position;"
                                        "attribute vec3 vertexColor;"
                                        "varying vec3 theColor;"
                                        "uniform mat4 transf;"
                                        "uniform mat4 projection;"
                                        "void main()"
                                        "{"
                                            "vec4 q = transf * vec4(position, 0.0, 1.0);"
                                            "gl_Position = projection * q;"
                                            "theColor = vertexColor;"
                                        "}";

//Текст тривиального фрагментного шейдера
static const char *s_pixelShader =      "precision mediump float;"
                                        "varying vec3 theColor;"
                                        "void main()"
                                        "{"
                                            "gl_FragColor = vec4(theColor, 0);"
                                        "}";

namespace Game
{
    Game::Game()
        :m_core(nullptr), m_context(nullptr)
    {
        std::unique_ptr<CoreDD> l_coreDD(new CoreDD());
        std::unique_ptr<Core> l_core(new Core(l_coreDD.get()));
        l_coreDD.release();
        std::unique_ptr<DCImpl> l_context(new DCImpl());
        m_core = l_core.release();
        m_context = l_context.release();
    }

    Game::~Game()
    {
        cleanup();
        delete m_core;
        delete m_context;
    }

    void Game::evol(JNIEnv *a_env, jobject a_obj, float a_dt)
    {
        assert(m_core != nullptr && m_context != nullptr);
        m_core->evol(a_dt);
    }

    void Game::onDrawFrame(JNIEnv *a_env, jobject a_obj, jobject a_gl)
    {
        assert(m_core != nullptr && m_context != nullptr);
        if (m_context->transf() < 0)
            return;

        //Очищение
        ::glClearColor(0, 0, 0, 1.0f);
        ::glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        m_core->draw(m_context);
    }

    void Game::onSurfaceChanged(JNIEnv *a_env, jobject a_obj, jobject a_gl, jint a_w, jint a_h)
    {
        assert(m_core != nullptr && m_context != nullptr);
        const float l_scrRat = float(a_w) / a_h;
        const float l_gamRat = s_width / s_height;
        if (l_scrRat < l_gamRat)                    //Область вывода более вытянута по вертикали,
        {                                           //чем игровое пространство?
            const float l_newH = a_w / l_gamRat;
            ::glViewport(0, GLint((float(a_h) - l_newH) / 2), a_w, GLint(l_newH));
        }
        else                                        //Область вывода более вытянута по горизонтали,
        {                                           //чем игровое пространство (или они эквивалентны)
            const float l_newW = a_h * l_gamRat;
            ::glViewport(GLint((float(a_w) - l_newW) / 2), 0, GLint(l_newW), a_h);
        }
    }

    void Game::onSurfaceCreated(JNIEnv *a_env, jobject a_obj, jobject a_gl, jobject a_config)
    {
        assert(m_core != nullptr && m_context != nullptr);
        m_context->setProg(::createProgram(s_vertexShader, s_pixelShader));
        if (!m_context->prog()) { m_context->setTransf(-1); return; }
        ::glUseProgram(m_context->prog());

        //Установка матрицы проецирования
        const GLint l_loc = ::glGetUniformLocation(m_context->prog(), "projection");
        const GLfloat l_matrix[] =  { 2 / s_width, 0, 0, 0,
                                      0, 2 / s_height, 0, 0,
                                      0, 0, 1, 0,
                                      0, 0, 0, 1 };
        ::glUniformMatrix4fv(l_loc, 1, GL_FALSE, l_matrix);

        //Начальная установка матрицы преобразований
        m_context->setTransf(::glGetUniformLocation(m_context->prog(), "transf"));
        const GLfloat l_transf[] =  { 1, 0, 0, 0,
                                      0, 1, 0, 0,
                                      0, 0, 1, 0,
                                      0, 0, 0, 1 };
        ::glUniformMatrix4fv(m_context->transf(), 1, GL_FALSE, l_transf);

        m_core->initDraw(m_context);
    }

    void Game::pressed()
    {
        assert(m_core != nullptr);
        m_core->pressed();
    }

    void Game::released()
    {
        assert(m_core != nullptr);
        m_core->released();
    }

    void Game::cleanup()
    {}
}
