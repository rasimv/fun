// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <limits>

const float s_r = 1;
const float s_g = 0;
const float s_b = 0;

const size_t s_sectCount = 40;
const float s_pi = 3.1415926535897932384626433832795f;

int main()
{
    std::ofstream l_ofs1("circle.inc", std::ios::binary);
    if (!l_ofs1.is_open())
        return -1;
    l_ofs1 << std::fixed << std::setprecision(std::numeric_limits<float>::max_digits10);
    for (size_t q = 0; q < s_sectCount; q++)
    {
        const float l_angle1 = 2 * s_pi * q / s_sectCount;
        const float l_x1 = ::cos(l_angle1);
        const float l_y1 = ::sin(l_angle1);
        const float l_angle2 = 2 * s_pi * (q + 1) / s_sectCount;
        const float l_x2 = ::cos(l_angle2);
        const float l_y2 = ::sin(l_angle2);
        l_ofs1 << "{ " << 0 << ", " << 0 << ", " << s_r << ", " << s_g << ", " << s_b << " }, "
               << "{ " << l_x1 << "f, " << l_y1 << "f, " << s_r << ", " << s_g << ", " << s_b << " }, "
               << "{ " << l_x2 << "f, " << l_y2 << "f, " << s_r << ", " << s_g << ", " << s_b << " },\r\n";
    }
    return 0;
}
