#ifndef __OGLES_OGLAUX_H
#define __OGLES_OGLAUX_H

#include "vertex.h"

extern "C"
{
    //Функция загрузки шейдера: a_shaderType - тип шейдера, a_source - текст
    GLuint loadShader(GLenum a_shaderType, const char *a_source);
    //Функция создания программы: a_vertexSource - текст вершинного шейдера, a_fragmentSource - фрагментного
    GLuint createProgram(const char* a_vertexSource, const char* a_fragmentSource);
    //Функция отрисовки из буфера вершин: a_id - идентификатор буфера,
    //a_first - индекс начальной вершины, a_count - количество вершин
    void drawBuffer(GLuint a_id, GLint a_first, GLsizei a_count);
}

#endif //__OGLES_OGLAUX_H
