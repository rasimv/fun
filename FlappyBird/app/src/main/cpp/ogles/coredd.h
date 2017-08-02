#ifndef __OGLES_COREDD_H
#define __OGLES_COREDD_H

#include "../game/drawdata.h"
#include "vertex.h"
#include <utility>

namespace Game
{
	class DCImpl;

	//Класс, реализующий объект с данными нужными для отрисовки
	class CoreDD: public DrawData
	{
	public:
		CoreDD();
		void init(DCImpl *a);
		GLuint buf(size_t a) const;			//Возвращает идентификатор буфера для символа a
		GLuint rectBuf() const;				//Возвращает идентификатор буфера квадрата
		size_t size(size_t a) const;		//Возвращает число вершин для символа a

		//Параметры пиксельного шрифта:
		static const size_t s_charW = 5;	//число столбцов,
		static const size_t s_charWI = 1;	//интервал между символами,
		static const size_t s_charH = 7;	//число строк

	private:
		static const Vertex s_charTri[2 * 3 * 227];		//Массив вершин символов: 227 квадратов (пикселей),
														//каждый из которых состоит из двух треугольников
		static const std::pair<size_t, size_t> s_charBE[256];	//Пары индексов (в s_charTri) символов:
						//first - индекс начальной вершины символа (begin),
						//second - индекс вершины следующей после последней вершины символа (end)
		static const Vertex s_rectTri[2 * 3];	//Вершины, квадрата состоящего из двух треугольников

		GLuint m_bufIDs[256];	//Идентификаторы буферов символов пиксельного шрифта
		GLuint m_rectBuf;		//Идентификатор буфера (два треугольника, составляющие квадрат со стороной 2 и центром в <0, 0>)
	};
}

#endif //__OGLES_COREDD_H
