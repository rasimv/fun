#include "dcimpl.h"

namespace Game
{
    DCImpl::DCImpl(GLuint a_prog, GLint a_transf) :m_prog(a_prog), m_transf(a_transf) {}
    void DCImpl::setProg(GLuint a_prog) { m_prog = a_prog; }
    GLuint DCImpl::prog() const { return m_prog; }
    void DCImpl::setTransf(GLint a_transf) { m_transf = a_transf; }
    GLint DCImpl::transf() const { return m_transf; }
}
