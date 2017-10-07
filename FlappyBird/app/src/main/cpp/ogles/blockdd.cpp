#include "blockdd.h"

namespace Game
{
    BlockDD::BlockDD() :m_inited(false), m_buf(GLuint(-1)) {}

    void BlockDD::setInited(bool a) { m_inited = a; }
    bool BlockDD::inited() const { return m_inited; }

    void BlockDD::genBuf() { ::glGenBuffers(1, &m_buf); }
    GLuint BlockDD::buf() const { return m_buf; }

    void BlockDD::loadBuf()
    {
        ::glBindBuffer(GL_ARRAY_BUFFER, m_buf);
        //Вершины треугольников составляющих квадрат
        static const Vertex s_rectTri[] =
            {
                { -1, -1, 0, 0.6f, 0 }, { 1, -1, 0, 0.6f, 0 }, { 1, 1, 0, 0.6f, 0 },
                { -1, -1, 0, 0.6f, 0 }, { 1, 1, 0, 0.6f, 0 }, { -1, 1, 0, 0.6f, 0 }
            };
        ::glBufferData(GL_ARRAY_BUFFER, sizeof(s_rectTri), s_rectTri, GL_STATIC_DRAW);
    }
}
