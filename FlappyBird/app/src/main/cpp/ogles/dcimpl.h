#ifndef __OGLES_DCIMPL_H
#define __OGLES_DCIMPL_H

#include "../game/drawcontext.h"
#include <GLES2/gl2.h>

namespace Game
{
	//Класс, реализующий объект контекста отрисовки посредством opengl es
	class DCImpl : public DrawContext
	{
	public:
		DCImpl(GLuint a_prog = 0, GLint a_transf = -1);
		void setProg(GLuint a_prog);
		GLuint prog() const;
		void setTransf(GLint a_transf);
		GLint transf() const;

	private:
		GLuint m_prog;		//Идентификатор программы
		GLint m_transf;		//Идентификатор матрицы преобразования
	};
}

#endif //__OGLES_DCIMPL_H
