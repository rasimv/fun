#ifndef __GAME_BIRD_H
#define __GAME_BIRD_H

#include "object.h"

namespace Game
{
	class Block;

	//Класс реализующий птицу
	class Bird : public Object
	{
	public:
		Bird(Core *a = 0, float a_x = 0, float a_y = 0, float a_r = 0, float a_v = 0, float a_a = 0);
		virtual ~Bird();

		float x() const { return m_x; }
		float y() const { return m_y; }
		float r() const { return m_r; }
		float wing() const;					//Возвращает положения крыла

		virtual void evol(float a_dt) override;
		virtual void postEvol() override;
		virtual void initDraw(DrawContext *a) override;
		virtual void draw(DrawContext *a) override;
		virtual void pressed() override;
		virtual void released() override;

	private:
		DrawData *createDD();	//Функция создания объекта, содержащего данные
								//нужные для отрисовки

		int m_pressedPrev, m_pressed;

		float m_x, m_y, m_r;	//Координаты центра и радиус окружности птицы
		float m_v;				//Вертикальная скорость птицы
		float m_a;				//Вертикальное ускорение птицы
		bool m_prev;			//Признак: true -- если в последнем цикле птица находилась
								//в зазоре между верхним и нижним блоками
		float m_wingA;			//Фактор положения крыла:
								// -π - крыло в центральном положении (двигается наверх),
								// -π/2 - крыло в верхней мертвой точке,
								// 0 - крыло в центральном положении (двигается вниз),
								// π/2 - крыло в верхней мертвой точке
	};
}

#endif //__GAME_BIRD_H
