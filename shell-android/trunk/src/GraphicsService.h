/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef GRAPHICSSERVICE_H_
#define GRAPHICSSERVICE_H_

#include <EGL/egl.h>

struct android_app;
class ShellFactory;

namespace Util {
class Config;
}

/**
 *
 */
class GraphicsService {
public:

        /**
         * Metoda inicjująca EGL, którą można wywoływac wiele razy na róznych etapach
         * i ona zawsze sprawdza co jest do zainichowania. Czyli śmiało można wywoływać
         * wiele razy.
         * Zwraca true, gdy operacja się powiedzie i ekran jest zainicjowany. False, gdy
         * się nie powiodła, ale jest szansa, że nastęþnym razem będzie OK. Zrzuca wyjątki
         * gdy sytuacja jest krytyczna.
         */
        bool initDisplay (Util::Config *config);
        void termDisplay ();
        void unbindSurfaceAndContext ();

        /**
         * Zwraca true gdy powodzenie.
         */
        bool saveScreenDimensionsInConfig (Util::Config *config);
        void swapBuffers ();

private:

        GraphicsService (android_app *app);
        friend class ShellFactory;

private:

        android_app *app;
        EGLDisplay display;
        EGLSurface surface;
        EGLContext context;
};

#endif /* GRAPHICSSERVICE_H_ */
