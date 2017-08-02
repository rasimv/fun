#ifndef __GAME_AUXILIARY_H
#define __GAME_AUXILIARY_H

namespace Game
{
	extern const float s_pi;

	//Вспомогательные функции

	//"Треугольная Функция"
	float trif(float a);

	//Лежил ли точка (a_x, a_y) в прямоугольнике (a_rx, a_ry, a_w, a_h)
	bool pointInsideRect(float a_x, float a_y, float a_rx, float a_ry, float a_w, float a_h);

	//Лежит ли точка (a_x, a_y) в круге (a_cx, a_cy, a_r)
	bool pointInsideCirc(float a_x, float a_y, float a_cx, float a_cy, float a_r);

	//Пересекаются ли круг (a_cx, a_cy, a_r) и прямоугольник (a_rx, a_ry, a_w, a_h)
	bool circleIntersectsRect(float a_cx, float a_cy, float a_r, float a_rx, float a_ry, float a_w, float a_h);
}

#endif //__GAME_AUXILIARY_H
