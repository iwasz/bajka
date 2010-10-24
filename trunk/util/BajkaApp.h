/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKAAPP_H_
#define BAJKAAPP_H_

#include <String.h>
#include <Reflection.h>

#include "IDispatcher.h"

namespace Controller {
class IController;
}

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
        __c (void)

        BajkaConfig ();

/*--------------------------------------------------------------------------*/

        _m (init) void init ();

/*------access methods------------------------------------------------------*/

        bool getFullScreen () const { return fullScreen; }
        _m (setFullScreen) void setFullScreen (bool fullScreen) { this->fullScreen = fullScreen; }

        int getResX () const { return resX; }
        _m (setResX) void setResX (int resX) { this->resX = resX; }

        int getResY () const { return resY; }
        _m (setResY)  void setResY (int resY) { this->resY = resY; }

        const Core::String &getWindowCaption () const { return windowCaption; }
        _m (setWindowCaption) void setWindowCaption (const Core::String &windowCaption) { this->windowCaption = windowCaption; }

private:

        bool fullScreen;
        int resX;
        int resY;
        Core::String windowCaption;

        _e (BajkaConfig)
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

       __c (void)

       BajkaApp () : dispatchers (new Event::DispatcherList) {}
       virtual ~BajkaApp () {}

       _m (loop) void loop ();
       _m (debug) void debug (Core::String const &);
       _m (debug) void destroy ();

/*--------------------------------------------------------------------------*/

       Ptr <BajkaConfig> getConfig () const { return config; }
       _m (setConfig) void setConfig (Ptr <BajkaConfig> b) { config = b; }

       Ptr <Controller::IController> getRootController () const { return rootController; }
       _m (setRootController) void setRootController (Ptr <Controller::IController> r) { rootController = r; }

       Ptr <Event::DispatcherList> getDispatchers () const { return dispatchers; }
       _m (setDispatchers) void setDispatchers (Ptr <Event::DispatcherList> d) { dispatchers = d; }

private:

       Ptr <BajkaConfig> config;
       Ptr <Controller::IController> rootController;
       Ptr <Event::DispatcherList> dispatchers;

       _e (BajkaApp)
};

} // nam

#	endif /* BAJKAAPP_H_ */
