package com.example.rasim.flappybird;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

public class GameGLSV extends GLSurfaceView
{
    //Класс фабрики контекстов
    private static class ContextFactory implements GLSurfaceView.EGLContextFactory
    {
        public EGLContext createContext(EGL10 a_egl, EGLDisplay a_display, EGLConfig a_eglConfig)
        {
            //Версия opengl es 2
            int[] l_attribList = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL10.EGL_NONE };
            return a_egl.eglCreateContext(a_display, a_eglConfig, EGL10.EGL_NO_CONTEXT, l_attribList);
        }

        public void destroyContext(EGL10 a_egl, EGLDisplay a_display, EGLContext a_context)
        {
            a_egl.eglDestroyContext(a_display, a_context);
        }
    }

    //Рендерер
    private class Renderer implements GLSurfaceView.Renderer
    {
        public void onDrawFrame(GL10 gl)
        {
            m_callbacks.onDrawFrame(gl);
        }

        public void onSurfaceChanged(GL10 gl, int width, int height)
        {
            m_callbacks.onSurfaceChanged(gl, width, height);
        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config)
        {
            m_callbacks.onSurfaceCreated(gl, config);
        }
    }

    //Класс фиктивного объекта с методами-обработчиками (для GameGLSV.GameGLSV(Context))
    private class Stub implements Callbacks
    {
        @Override public void onDrawFrame(Object a_gl) {}
        @Override public void onSurfaceChanged(Object a_gl, int a_w, int a_h) {}
        @Override public void onSurfaceCreated(Object a_gl, Object a_config) {}
        @Override public void pressed() {}
        @Override public void released() {}
    }

    //Класс выборщика конфигураций
    private static class ConfigChooser implements GLSurfaceView.EGLConfigChooser
    {
        //Нужно определить функцию выбора конфигурации
        @Override public EGLConfig chooseConfig(EGL10 a_egl, EGLDisplay a_display)
        {
            int[] l_configCount = new int[1];
            EGLConfig[] l_configs = new EGLConfig[1];       //Первая подходящая конфигурация
            a_egl.eglChooseConfig(a_display, s_configAttribs, l_configs, l_configs.length, l_configCount);
            return l_configCount[0] > 0 ? l_configs[0] : null;
        }
    }

    public GameGLSV(Context a_context)
    {
        super(a_context);
        m_callbacks = new Stub();
        init();
    }

    public GameGLSV(Context a_context, Callbacks a_callbacks)
    {
        super(a_context);
        m_callbacks = a_callbacks;
        init();
    }

    private void init()
    {
        //Задать объект фабрики контекстов
        setEGLContextFactory(new GameGLSV.ContextFactory());
        //Задать объект-выборщик конфигураций
        setEGLConfigChooser(new GameGLSV.ConfigChooser());
        //Задать объект-рендерер
        setRenderer(new GameGLSV.Renderer());
    }

    //Переопределение метода-обработчика прикосновений
    @Override public boolean onTouchEvent(MotionEvent e)
    {
        switch (e.getAction())
        {
            case MotionEvent.ACTION_DOWN:       //Нажатие
                queueEvent(new Runnable() { public void run() { m_callbacks.pressed(); } });
                break;
            case MotionEvent.ACTION_UP:         //Отпускание
                queueEvent(new Runnable() { public void run() { m_callbacks.released(); } });
        }
        return true;
    }

    private Callbacks m_callbacks;

    private static int EGL_CONTEXT_CLIENT_VERSION = 0x3098;
    private static int EGL_OPENGL_ES2_BIT = 4;
    private static int[] s_configAttribs =
            {
                    EGL10.EGL_RED_SIZE, 5,
                    EGL10.EGL_GREEN_SIZE, 6,
                    EGL10.EGL_BLUE_SIZE, 5,
                    EGL10.EGL_ALPHA_SIZE, 0,
                    EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                    EGL10.EGL_NONE
            };
}
