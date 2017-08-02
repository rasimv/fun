package com.example.rasim.flappybird;

//"View-интерфейс" игры
public interface Callbacks
{
    void onDrawFrame(Object a_gl);
    void onSurfaceChanged(Object a_gl, int a_w, int a_h);
    void onSurfaceCreated(Object a_gl, Object a_config);
    void pressed();
    void released();
}
