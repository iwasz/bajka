/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKAAPP_H_
#define BAJKAAPP_H_

#include <chipmunk.h>
#include "Geometry.h"
#include "Model.h"
#include "IDispatcher.h"
#include "ReflectionMacros.h"
#include "../events/types/IEvent.h"

using Event::ModelIndex;

namespace Util {

/*
 * Ta klasa jest tylko po to, żeby ułatwoć stosowanie bajki z kontenerem.
 * Otóż kolejność pracy programu musi być następująca:
 * - Utworzenie BajkaConfig.
 * - Ustawienie jej pól.
 * - Uruchomienie init ().
 * Treaz OpenGL i SDL są zainicjowane, można dodawać obiekty. I dopero teraz
 * można uruchomić pętlę programu:
 * - BajkaApp run.
 * INICJUJE OpenGL!
 */
class BajkaConfig {
public:
        C__ (void)

        BajkaConfig ();
        ~BajkaConfig ();

/*--------------------------------------------------------------------------*/

        m_ (init) void init ();

/*------access methods------------------------------------------------------*/

        bool getFullScreen () const { return fullScreen; }
        m_ (setFullScreen) void setFullScreen (bool fullScreen) { this->fullScreen = fullScreen; }

        int getResX () const { return resX; }
        m_ (setResX) void setResX (int resX) { this->resX = resX; }

        int getResY () const { return resY; }
        m_ (setResY)  void setResY (int resY) { this->resY = resY; }

        const std::string &getWindowCaption () const { return windowCaption; }
        m_ (setWindowCaption) void setWindowCaption (const std::string &windowCaption) { this->windowCaption = windowCaption; }

private:

        bool fullScreen;
        int resX;
        int resY;
        std::string windowCaption;

        E_ (BajkaConfig)
};

/**
 * Bajka application. It is bound to OpenGL and is not meant to
 * be used with any other technologies (i.e. DirectX). Implements
 * the main loop.
 *
 * CR : Kiedyś kiedyś : umożliwić stosowanie czegoś innego niż SDL.
 * Można z tego dziedziczyć i dodawać swoje metody game-specific.
 */
class BajkaApp : public Core::Object {
public:

       C__ (void)

       BajkaApp () /*: dispatchers (new Event::DispatcherList)*/ {}
       virtual ~BajkaApp () {}

       m_ (loop) void loop ();
       m_ (debug) void debug (Core::String const &);
       m_ (debug) void destroy ();

/*--------------------------------------------------------------------------*/

       /**
        * Wykonywane w głównej pętli PO wykonaniu wszystkich procedur obsługi eventow.
        * Domyślnie ta metoda jest pusta, ale można ją oczywiście przedefiniować.
        */
       virtual void afterEvents () {}

       Ptr <BajkaConfig> getConfig () const { return config; }
       m_ (setConfig) void setConfig (Ptr <BajkaConfig> b) { config = b; }

       /// Głowny model.
       Ptr <Model::IModel> getModel () const { return model; }

       /**
        * 1. Odłącza poprzedni rootControloer od dispatcherów.
        * 2. Ustawia główny kontroler.
        * 3. Podłącza ten nowy do wszystkich dispatcherów.
        */
       s_ (setModel) void setModel (Ptr <Model::IModel> model);

       Ptr <Event::DispatcherList> getDispatchers () const { return dispatchers; }
       m_ (setDispatchers) void setDispatchers (Ptr <Event::DispatcherList> d) { dispatchers = d; }

private:

       /// Szuka wśród modeli które mają trafić na które listy.
       unsigned int reindex (unsigned int eventMask, Model::IModel *m);

private:

       Ptr <BajkaConfig> config;
       Ptr <Model::IModel> model;
       Ptr <Event::DispatcherList> dispatchers;
       ModelIndex listeners;

       E_ (BajkaApp)
};

} // nam

#	endif /* BAJKAAPP_H_ */
