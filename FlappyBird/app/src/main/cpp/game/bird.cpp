#include "bird.h"
#include "defs.h"
#include <cassert>
#include "core.h"
#include "auxiliary.h"
#include <cmath>

namespace Game
{
	Bird::Bird(Core *a, float a_x, float a_y, float a_r, float a_v, float a_a)
		:Object(a, createDD()), m_pressedPrev(false), m_pressed(false),
		 m_x(a_x), m_y(a_y), m_r(a_r), m_v(a_v), m_a(a_a), m_prev(false), m_wingA(s_sa)
	{}

	Bird::~Bird() { delete m_dd; }

	float Bird::wing() const { return Game::trif(m_wingA); }

	void Bird::evol(float a_dt)
	{
		assert(m_core != nullptr);
		if (a_dt == 0)
			return;
		m_y += m_v * a_dt;
		m_v += m_a * a_dt;
		if (m_y + m_r > s_height / 2)					//Не дать птице взлететь выше игровой области
			m_y = s_height / 2 - m_r;					//
		const BoolPair l_hit(m_core->hit(this));		//Проверить на столкновение с блоком (first)
														//и на нахождение птицы в зазоре (second)
		if (m_y - m_r < -s_height / 2 || l_hit.first)	//Если есть падение на нижнюю границу
		{												//игровой области или столкновение с блоком, то
			m_core->hit(true);							//известить об этом "ядро" и
			m_a = -s_g;									//начать падение
			if (m_v > 0) m_v = 0;						//прекратив взлет
		}
		if (m_prev && !l_hit.second && !m_core->hit())	//Проверка на пролет очередного зазора
			m_core->score();							//Увеличить счетчик, если есть пролет
		m_prev = l_hit.second;							//Вести признак
		if (m_y + m_r < -s_height / 2)					//При выпадении из игр. области после 
			m_core->fell(true);							//столкновения или падения известить "ядро"

		if (m_core->hit())								//Если было столкновение с блоков или
			return;										//падение на нижнюю границу...

		const float l_wingA = m_wingA + s_w * a_dt;		//Новое положение крыла
		if (l_wingA > 3 * s_pi / 2)						//
			m_wingA = s_sa;								//
		else if (m_pressed)								//Если состояние нажатия,
		{												//
			m_wingA = l_wingA;							//то продолжать махать крылом
			if (m_wingA >= s_pi)						//Поддерживать фактор положения крыла в
				m_wingA -= 2 * s_pi;					//диапазоне [-π; π)
		}

		if (!m_pressedPrev && m_pressed)
		{
			m_a = 0;				//Равномерный набор высоты при нажатии
			m_v = s_v;				//
			m_wingA = s_sa;
		}
		if (m_pressedPrev && !m_pressed)
		{
			m_a = -s_g;				//Падение при отпускании
			m_v = 0;				//
			m_wingA = s_sa;
		}

		m_pressedPrev = m_pressed;
	}

	void Bird::pressed() { m_pressed = true; }
	void Bird::released() { m_pressed = false; }
}
