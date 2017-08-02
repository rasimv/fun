#include "birddd.h"

namespace Game
{
    BirdDD::BirdDD() :m_inited(false), m_buf1(GLuint(-1)), m_buf2(GLuint(-1)) {}

    void BirdDD::setInited(bool a) { m_inited = a; }
    bool BirdDD::inited() const { return m_inited; }

    void BirdDD::genBuf()
    {
        ::glGenBuffers(1, &m_buf1);
        ::glGenBuffers(1, &m_buf2);
    }

    GLuint BirdDD::buf1() const { return m_buf1; }
    GLuint BirdDD::buf2() const { return m_buf2; }

    void BirdDD::loadBuf()
    {
        ::glBindBuffer(GL_ARRAY_BUFFER, m_buf1);
        ::glBufferData(GL_ARRAY_BUFFER, sizeof(s_tri), s_tri, GL_STATIC_DRAW);
        ::glBindBuffer(GL_ARRAY_BUFFER, m_buf2);
        ::glBufferData(GL_ARRAY_BUFFER, sizeof(s_wingTri), s_wingTri, GL_STATIC_DRAW);
    }
}
