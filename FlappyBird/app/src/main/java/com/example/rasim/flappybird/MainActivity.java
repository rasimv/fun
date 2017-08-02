package com.example.rasim.flappybird;

import android.app.Activity;
import android.os.Bundle;
import static android.opengl.GLSurfaceView.RENDERMODE_WHEN_DIRTY;

//Класс главного Activity
public class MainActivity extends Activity
{
    @Override protected void onCreate(Bundle a_savedInstanceState)
    {
        super.onCreate(a_savedInstanceState);
        m_game = new Game();
        m_view = new GameGLSV(getApplication(), m_game);
        setContentView(m_view);
    }

    @Override protected void onPause()
    {
        super.onPause();
        m_view.onPause();
        m_game.onPause();
    }

    @Override protected void onResume()
    {
        super.onResume();
        m_view.onResume();
        m_game.onResume();
    }

    @Override protected void onDestroy()
    {
        m_view.setRenderMode(RENDERMODE_WHEN_DIRTY);                    //Выключить отрисовку
        try { Thread.sleep(3000); } catch (InterruptedException e) {}   //Пауза для завершения уже
                                                                        //запущенных потоков отрисовки
        m_game.onDestroy();
        super.onDestroy();
    }

    private Game m_game;
    private GameGLSV m_view;
}
