#include "auxiliary.h"
#include <cmath>

namespace Game
{
	const float s_pi = 3.1415926535897932384626433832795f;

	float trif(float a)
	{
		const float q = ::fmodf(a, 2 * s_pi);
		const float p = q >= 0 ? q : q + 2 * s_pi;
		return (p < s_pi / 2 ? p : (p < 3 * s_pi / 2 ? s_pi - p : p - 2 * s_pi))  * 2 / s_pi;
	}

	bool pointInsideRect(float a_x, float a_y, float a_rx, float a_ry, float a_w, float a_h)
	{
		return a_x >= a_rx && a_x <= a_rx + a_w && a_y >= a_ry && a_y <= a_ry + a_h;
	}

	bool pointInsideCirc(float a_x, float a_y, float a_cx, float a_cy, float a_r)
	{
		return a_r * a_r > (a_x - a_cx) * (a_x - a_cx) + (a_y - a_cy) * (a_y - a_cy);
	}

	bool circleIntersectsRect(float a_cx, float a_cy, float a_r, float a_rx, float a_ry, float a_w, float a_h)
	{
		//Лежит ли точка в двух прямоугольниках и четырех кругах образующихся при обкатывании исх.
		//кругом (a_cx, a_cy, a_r) по периметру исходного прямоугольника (a_rx, a_ry, a_w, a_h)
		return pointInsideCirc(a_cx, a_cy, a_rx, a_ry, a_r) ||
			pointInsideCirc(a_cx, a_cy, a_rx + a_w, a_ry, a_r) ||
			pointInsideCirc(a_cx, a_cy, a_rx + a_w, a_ry + a_h, a_r) ||
			pointInsideCirc(a_cx, a_cy, a_rx, a_ry + a_h, a_r) ||
			pointInsideRect(a_cx, a_cy, a_rx - a_r, a_ry, a_w + 2 * a_r, a_h) ||
			pointInsideRect(a_cx, a_cy, a_rx, a_ry - a_r, a_w, a_h + 2 * a_r);
	}
}
