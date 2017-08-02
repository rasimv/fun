#ifndef __OGLES_BLOCKDD_H
#define __OGLES_BLOCKDD_H

#include "../game/drawdata.h"
#include "vertex.h"

namespace Game
{
	//Класс, реализующий объект с данными нужными для отрисовки
	class BlockDD: public DrawData
	{
	public:
		BlockDD();

		void setInited(bool a);
		bool inited() const;

		void genBuf();
		GLuint buf() const;
		void loadBuf();

	private:
		bool m_inited;
		GLuint m_buf;	//Идентификатор буфера (два треугольника, составляющие квадрат со стороной 2 и центром в <0, 0>)
	};
}

#endif //__OGLES_BLOCKDD_H
