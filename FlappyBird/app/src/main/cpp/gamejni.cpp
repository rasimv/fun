#include <jni.h>
#include <cassert>
#include "game.h"

extern "C"
{
    JNIEXPORT jlong JNICALL Java_com_example_rasim_flappybird_GameJNI_createGame(JNIEnv *a_env,
                                                                                 jobject a_obj)
    {
        return reinterpret_cast<jlong>(new Game::Game());
    }

    JNIEXPORT void JNICALL Java_com_example_rasim_flappybird_GameJNI_destroyGame(JNIEnv *a_env,
                                                                                 jobject a_obj,
                                                                                 jlong a_instance)
    {
        auto p = reinterpret_cast<Game::Game *>(a_instance);
        assert(p != nullptr);
        delete p;
    }

    JNIEXPORT void JNICALL Java_com_example_rasim_flappybird_GameJNI_evolN(JNIEnv *a_env,
                                                                           jobject a_obj,
                                                                           jlong a_instance,
                                                                           jfloat a_dt)
    {
        Game::Game *const l_game = reinterpret_cast<Game::Game *>(a_instance);
        assert(l_game != nullptr);
        l_game->evol(a_env, a_obj, a_dt);
    }

    JNIEXPORT void JNICALL Java_com_example_rasim_flappybird_GameJNI_onDrawFrame(JNIEnv *a_env,
                                                                                 jobject a_obj,
                                                                                 jlong a_instance,
                                                                                 jobject a_gl)
    {
        Game::Game *const l_game = reinterpret_cast<Game::Game *>(a_instance);
        assert(l_game != nullptr);
        l_game->onDrawFrame(a_env, a_obj, a_gl);
    }

    JNIEXPORT void JNICALL Java_com_example_rasim_flappybird_GameJNI_onSurfaceChanged(JNIEnv *a_env,
                                                                                      jobject a_obj,
                                                                                      jlong a_instance,
                                                                                      jobject a_gl,
                                                                                      jint a_w,
                                                                                      jint a_h)
    {
        Game::Game *const l_game = reinterpret_cast<Game::Game *>(a_instance);
        assert(l_game != nullptr);
        l_game->onSurfaceChanged(a_env, a_obj, a_gl, a_w, a_h);
    }

    JNIEXPORT void JNICALL Java_com_example_rasim_flappybird_GameJNI_onSurfaceCreated(JNIEnv *a_env,
                                                                                      jobject a_obj,
                                                                                      jlong a_instance,
                                                                                      jobject a_gl,
                                                                                      jobject a_config)
    {
        Game::Game *const l_game = reinterpret_cast<Game::Game *>(a_instance);
        assert(l_game != nullptr);
        l_game->onSurfaceCreated(a_env, a_obj, a_gl, a_config);
    }

    JNIEXPORT void JNICALL Java_com_example_rasim_flappybird_GameJNI_pressedN(JNIEnv *a_env,
                                                                              jobject a_obj,
                                                                              jlong a_instance)
    {
        Game::Game *const l_game = reinterpret_cast<Game::Game *>(a_instance);
        assert(l_game != nullptr);
        l_game->pressed();
    }

    JNIEXPORT void JNICALL Java_com_example_rasim_flappybird_GameJNI_releasedN(JNIEnv *a_env,
                                                                               jobject a_obj,
                                                                               jlong a_instance)
    {
        Game::Game *const l_game = reinterpret_cast<Game::Game *>(a_instance);
        assert(l_game != nullptr);
        l_game->released();
    }
}
