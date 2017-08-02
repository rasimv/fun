#include "vertex.h"

GLuint loadShader(GLenum a_shaderType, const char *a_source)
{
    GLuint l_shader = glCreateShader(a_shaderType);
    if (!l_shader)
        return 0;

    glShaderSource(l_shader, 1, &a_source, NULL);
    glCompileShader(l_shader);
    GLint l_compiled = 0;
    glGetShaderiv(l_shader, GL_COMPILE_STATUS, &l_compiled);
    if (l_compiled == GL_TRUE)
        return l_shader;

    glDeleteShader(l_shader);
    return 0;
}

GLuint createProgram(const char* a_vertexSource, const char* a_fragmentSource)
{
    GLuint l_vertexShader = loadShader(GL_VERTEX_SHADER, a_vertexSource);
    if (!l_vertexShader)
        return 0;

    GLuint l_pixelShader = loadShader(GL_FRAGMENT_SHADER, a_fragmentSource);
    if (!l_pixelShader)
    {
        glDeleteShader(l_vertexShader);
        return 0;
    }

    GLuint l_program = glCreateProgram();
    if (!l_program)
    {
        glDeleteShader(l_pixelShader);
        glDeleteShader(l_vertexShader);
        return 0;
    }

    glAttachShader(l_program, l_vertexShader);
    glAttachShader(l_program, l_pixelShader);

    glBindAttribLocation(l_program, 0, "position");
    glBindAttribLocation(l_program, 1, "vertexColor");

    glLinkProgram(l_program);
    GLint l_linkStatus = GL_FALSE;
    glGetProgramiv(l_program, GL_LINK_STATUS, &l_linkStatus);
    if (l_linkStatus == GL_TRUE)
        return l_program;

    glDeleteShader(l_pixelShader);
    glDeleteShader(l_vertexShader);
    glDeleteProgram(l_program);
    return 0;
}

void drawBuffer(GLuint a_id, GLint a_first, GLsizei a_count)
{
    glBindBuffer(GL_ARRAY_BUFFER, a_id);
    //Задать параметры атрибута 0 (координаты вершины): 2 компонента типа GL_FLOAT (x, y)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), NULL);
    //Задать параметры атрибута 1 (цвет вершины): 3 компонента типа GL_FLOAT (rgb)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex),
                          (char *)(2 * sizeof(GLfloat)));   //Пропустить компоненты атрибута 0
    glDrawArrays(GL_TRIANGLES, a_first, a_count);
}
