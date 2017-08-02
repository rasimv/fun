package com.example.rasim.flappybird;

//Класс игры (обертка)
public class Game implements Callbacks
{
    public Game()
    {
        m_instance = GameJNI.createGame();
    }

    void onPause() {}

    void onResume()
    {
        m_fix = java.lang.System.nanoTime();
    }

    void onDestroy()
    {
        GameJNI.destroyGame(m_instance);
    }

    //========== Реализация интерфейса Callbacks ==========
    @Override public void onDrawFrame(Object a_gl)
    {
        //Получить текущее значение отметки времени
        long l_fix = java.lang.System.nanoTime();
        //Вычисление временного интервала и вызов функции рассчета нового состояния игры
        GameJNI.evol(m_instance, (float)((l_fix - m_fix) / 1000000000.0));
        //Вызов функции отрисовки
        GameJNI.onDrawFrame(m_instance, a_gl);
        //Сохранить текущее значение отметки времени
        m_fix = l_fix;
    }

    @Override public void onSurfaceChanged(Object a_gl, int a_w, int a_h)
    {
        GameJNI.onSurfaceChanged(m_instance, a_gl, a_w, a_h);
    }

    @Override public void onSurfaceCreated(Object a_gl, Object a_config)
    {
        GameJNI.onSurfaceCreated(m_instance, a_gl, a_config);
    }

    @Override public void pressed() { GameJNI.pressed(m_instance); }
    @Override public void released() { GameJNI.released(m_instance); }

    //=====================================================
    private long m_instance = 0;    //Численное значение указателя на C++-объект класса Game::Game
    private long m_fix = 0;         //Отметка времени
}
