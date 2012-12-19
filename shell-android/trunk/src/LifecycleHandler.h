/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SHELL_LIFECYCLEHANDLER_H_
#define BAJKA_SHELL_LIFECYCLEHANDLER_H_

#include <stdint.h>
#include <events/types/UpdateEvent.h>
#include "EventDispatcher.h"

class ShellContext;
class ShellFactory;
class GraphicsService;

namespace Sound {
class IDevice;
}

namespace Util {
class BajkaService;
class Scene;
}

/**
 *
 */
class LifecycleHandler {
public:

        ~LifecycleHandler ();

        /**
         * Tu aplikacja jest gotowa do renderowania, odtwarzania dźwięku, okno jest widoczne, user może
         * klikać. Ale to po raz pierwszy. Tu należy zainicjować kontekst OpenGL, EGL surface i tak dalej.
         */
        void onFirstTimeReadyForRender (ShellContext *ctx);

        /**
         * Aplikacja jest widoczna i gotowa do interakcji. Jeśli firstTime == true, to znaczy, że wykonał się
         * już handler onFirstTimeReadyForRender. Jesli flaga autoPauzy jest ustawiona, to wyświetlić ekran
         * auto pauzy.
         */
        void onGainedFocus (ShellContext *ctx, bool firstTime);

        /**
         * Tu należy
         * - włączyć auto pauzę, ale nie wyłączając renderowania,
         * - wyłączyć dźwięki,
         * - zmniejszyć odświerzanie - jednym słowem zwolnić CPU jak najbardziej.
         * Wartość zwracana : true, jeśli należy włączyć autoPauzę. False, jeśli normalnie kontunuujemy program.
         */
        bool onLostFocus (ShellContext *ctx);

        /**
         * Zatrzymać renderowanie zupełnie. Gra powinna konsumowac 0% CPU.
         */
        void onPause (ShellContext *ctx);

        /**
         * Kiedy dostajemy onsurfaceDestroyed należy prsestać renderować i unbind the EGLSurface and EGLContext (eglMakeCurrent with display, NULL, NULL)
         * and must stop rendering. Nie nalezy jednak niszczyć EGLContext, bo kiedy surface znów będzie dostępne, można ten kontekst zrebindować. Patrz strona 17.
         */
        void onSurfaceDestroyed (ShellContext *ctx);

        /**
         * EGLContext niszczymy zato w onStop.
         */
        void onStop (ShellContext *ctx);

        /**
         * Tu aplikacja kończy swoje działanie definitywnie. Oznacza, to, że należy zwolnić wszelkie zasoby,
         * ktore nie zostały zwolnione już wczesniej.
         */
        void onDestroy (ShellContext *ctx);

        /**
         * Zapisujemy stan gry.
         */
        void onSaveState (ShellContext *ctx);

        /**
         * Odczytujemy stan gry.
         */
        void onLoadState (ShellContext *ctx);

        /**
         * Kiedy na przykład orientacja ekranu się zmienia. Ustawiamy na nowo glViewPort.
         */
        void onConfigChanged (ShellContext *ctx);

        /**
         * Tu gra renderuje.
         */
        void onStep (ShellContext *ctx, bool autoPause, uint32_t deltaMs);

        /**
         * Klawiatura, mysz, dotyk, sensory.
         */
        bool onInputEvent (ShellContext *ctx, AInputEvent *event);

private:

        LifecycleHandler () : graphicsService (NULL), soundDevice (NULL), bajkaService (NULL), scene (NULL) {}
        LifecycleHandler (LifecycleHandler const &) {}
        friend class ShellFactory;

private:

        GraphicsService *graphicsService;
        Sound::IDevice *soundDevice;
        Util::BajkaService *bajkaService;
        Util::Scene *scene;
        Event::UpdateEvent updateEvent;
        EventDispatcher eventDispatcher;

};

#endif /* LIFECYCLEHANDLER_H_ */
