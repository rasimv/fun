#ifndef __FLAPPYBIRD_GAME_H
#define __FLAPPYBIRD_GAME_H

#include <jni.h>
#include "ogles/dcimpl.h"

namespace Game
{
    class Core;

    //Класс игры (opengl es)
    class Game
    {
    public:
        Game();
        ~Game();

        void evol(JNIEnv *a_env, jobject a_obj, float a_dt);
        void onDrawFrame(JNIEnv *a_env, jobject a_obj, jobject a_gl);
        void onSurfaceChanged(JNIEnv *a_env, jobject a_obj, jobject a_gl, jint a_w, jint a_h);
        void onSurfaceCreated(JNIEnv *a_env, jobject a_obj, jobject a_gl, jobject a_config);
        void pressed();
        void released();

    private:
        void cleanup();

        Core *m_core;
        DCImpl *m_context;
    };
}

#endif //__FLAPPYBIRD_GAME_H
