#include "coredd.h"
#include <cassert>

namespace Game
{
    CoreDD::CoreDD()
        :m_bufIDs{(GLuint)-1}, m_rectBuf(0)
    {}

    void CoreDD::init(DCImpl *a)
    {
        assert(a != nullptr);
        for (size_t i = 0; i < 256; i++)
        {
            const size_t l_size = sizeof(*s_charTri) * size(i);
            if (l_size == 0) continue;
            ::glGenBuffers(1, &m_bufIDs[i]);
            ::glBindBuffer(GL_ARRAY_BUFFER, m_bufIDs[i]);
            ::glBufferData(GL_ARRAY_BUFFER, l_size, s_charTri + s_charBE[i].first, GL_STATIC_DRAW);
        }

        ::glGenBuffers(1, &m_rectBuf);
        ::glBindBuffer(GL_ARRAY_BUFFER, m_rectBuf);
        ::glBufferData(GL_ARRAY_BUFFER, sizeof(s_rectTri), s_rectTri, GL_STATIC_DRAW);
    }

    GLuint CoreDD::buf(size_t a) const { return m_bufIDs[a]; }
    GLuint CoreDD::rectBuf() const { return m_rectBuf; }
    size_t CoreDD::size(size_t a) const { return s_charBE[a].second - s_charBE[a].first; }
}
