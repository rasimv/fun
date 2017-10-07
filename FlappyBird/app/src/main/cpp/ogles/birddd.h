#ifndef __OGLES_BIRDDD_H
#define __OGLES_BIRDDD_H

#include "../game/drawdata.h"
#include "vertex.h"

namespace Game
{
    //Класс, реализующий объект с данными нужными для отрисовки
    class BirdDD : public DrawData
    {
    public:
        BirdDD();

        void setInited(bool a);
        bool inited() const;

        void genBuf();
        GLuint buf1() const;
        GLuint buf2() const;
        void loadBuf();

    private:
        static const Vertex s_tri[3 + 3 + 3 * 40 + 3 + 3];  //Вершины: 3 - хвост, 3 - клюв,
                                                            //3 * 40 - круг тела, 3 - глаз, 3 - зрачок
        static const Vertex s_wingTri[3];   //Вершины крыла

        bool m_inited;
        GLuint m_buf1, m_buf2;  //Буферы: m_buf1 - для статич. части, m_buf2 - для крыла
    };
}

#endif //__OGLES_BIRDDD_H
