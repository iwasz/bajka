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
#include <core/Typedefs.h>

class ShellFactory;

namespace Event {
class IEventDispatcher;
}

namespace Util {
class IGraphicsService;
class BajkaService;
class Scene;
class ShellContext;

/**
 *
 */
class LifecycleHandler {
public:

        LifecycleHandler () :
                graphicsService (NULL),
                bajkaService (NULL),
                scene (NULL),
                eventDispatcher (NULL),
                singletons (NULL) {}

        ~LifecycleHandler ();

        /**
         * Tu aplikacja jest gotowa do renderowania, odtwarzania dźwięku, okno jest widoczne, user może
         * klikać. Ale to po raz pierwszy. Tu należy zainicjować kontekst OpenGL, EGL surface i tak dalej.
         */
        void onFirstTimeReadyForRender (Util::ShellContext *ctx);

        /**
         * Aplikacja jest widoczna i gotowa do interakcji. Jeśli firstTime == true, to znaczy, że wykonał się
         * już handler onFirstTimeReadyForRender. Jesli flaga autoPauzy jest ustawiona, to wyświetlić ekran
         * auto pauzy.
         */
        void onGainedFocus (Util::ShellContext *ctx, bool firstTime);

        /**
         * Tu należy
         * - włączyć auto pauzę, ale nie wyłączając renderowania,
         * - wyłączyć dźwięki,
         * - zmniejszyć odświerzanie - jednym słowem zwolnić CPU jak najbardziej.
         * Wartość zwracana : true, jeśli należy włączyć autoPauzę. False, jeśli normalnie kontunuujemy program.
         */
        bool onLostFocus (Util::ShellContext *ctx);

        /**
         * Zatrzymać renderowanie zupełnie. Gra powinna konsumowac 0% CPU.
         */
        void onPause (Util::ShellContext *ctx);

        /**
         * Kiedy dostajemy onsurfaceDestroyed należy prsestać renderować i unbind the EGLSurface and EGLContext (eglMakeCurrent with display, NULL, NULL)
         * and must stop rendering. Nie nalezy jednak niszczyć EGLContext, bo kiedy surface znów będzie dostępne, można ten kontekst zrebindować. Patrz strona 17.
         */
        void onSurfaceDestroyed (Util::ShellContext *ctx);

        /**
         * EGLContext niszczymy zato w onStop.
         */
        void onStop (Util::ShellContext *ctx);

        /**
         * Tu aplikacja kończy swoje działanie definitywnie. Oznacza, to, że należy zwolnić wszelkie zasoby,
         * ktore nie zostały zwolnione już wczesniej.
         */
        void onDestroy (Util::ShellContext *ctx);

        /**
         * Zapisujemy stan gry.
         */
        void onSaveState (Util::ShellContext *ctx);

        /**
         * Odczytujemy stan gry.
         */
        void onLoadState (Util::ShellContext *ctx);

        /**
         * Kiedy na przykład orientacja ekranu się zmienia. Ustawiamy na nowo glViewPort.
         */
        void onConfigChanged (Util::ShellContext *ctx);

        /**
         * Tu gra renderuje.
         */
        void onStep (Util::ShellContext *ctx, bool autoPause, uint32_t deltaMs);

        /**
         * Klawiatura, mysz, dotyk, sensory.
         */
        bool onInputEvent (Util::ShellContext *ctx, void *systemEvent);

/*--------------------------------------------------------------------------*/

        void setBajkaService (Util::BajkaService* bajkaService) { this->bajkaService = bajkaService; }
        void setEventDispatcher (Event::IEventDispatcher* eventDispatcher) { this->eventDispatcher = eventDispatcher; }
        void setGraphicsService (Util::IGraphicsService* graphicsService) { this->graphicsService = graphicsService; }
        void setSingletons (Core::VariantMap* singletons) { this->singletons = singletons; }

private:

        Util::IGraphicsService *graphicsService;
        Util::BajkaService *bajkaService;
        Util::Scene *scene;
        Event::UpdateEvent updateEvent;
        Event::IEventDispatcher *eventDispatcher;
        Core::VariantMap *singletons;

};

}

#endif /* LIFECYCLEHANDLER_H_ */
