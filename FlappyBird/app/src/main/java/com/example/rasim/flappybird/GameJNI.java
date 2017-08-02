package com.example.rasim.flappybird;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GameJNI
{
    static
    {
        System.loadLibrary("gamejni");
    }

    //Промежуточные функции (для привидения типов)
    public static void evol(long a_instance, float a_dt)
    {
        evolN(a_instance, a_dt);
    }

    public static void onDrawFrame(long a_instance, Object a_gl)
    {
        onDrawFrame(a_instance, (GL10)a_gl);
    }

    public static void onSurfaceChanged(long a_instance, Object a_gl, int a_w, int a_h)
    {
        onSurfaceChanged(a_instance, (GL10)a_gl, a_w, a_h);
    }

    public static void onSurfaceCreated(long a_instance, Object a_gl, Object a_config)
    {
        onSurfaceCreated(a_instance, (GL10)a_gl, (EGLConfig)a_config);
    }

    public static void pressed(long a_instance)
    {
        pressedN(a_instance);
    }

    public static void released(long a_instance)
    {
        releasedN(a_instance);
    }

    //Java-объявления для native-функций
    //Создает C++-объект класса Game::Game и возвращает численное значение указателя
    public static native long createGame();
    //Уничтожает C++-объект класса Game::Game, a - численное значение указателя
    public static native void destroyGame(long a);

    //a_instance - численное значение указателя на C++-объект класса Game::Game
    public static native void evolN(long a_instance, float a_dt);
    public static native void onDrawFrame(long a_instance, GL10 a_gl);
    public static native void onSurfaceChanged(long a_instance, GL10 a_gl, int a_w, int a_h);
    public static native void onSurfaceCreated(long a_instance, GL10 a_gl, EGLConfig a_config);
    public static native void pressedN(long a_instance);
    public static native void releasedN(long a_instance);
}
