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
#include "ModelManager.h"
#include "Config.h"

namespace Util {
class Impl;

/**
 * Bajka application. It is bound to OpenGL and is not meant to
 * be used with any other technologies (i.e. DirectX). Implements
 * the main loop.
 *
 * CR : Kiedyś kiedyś : umożliwić stosowanie czegoś innego niż SDL.
 * Można z tego dziedziczyć i dodawać swoje metody game-specific.
 */
class App : public Core::Object {
public:

       C__ (void)

       App ();
       virtual ~App ();

       void init ();
       m_ (loop) void loop ();
       m_ (destroy) void destroy ();

/*--------------------------------------------------------------------------*/

       Ptr <Config> getConfig () const;
       m_ (setConfig) void setConfig (Ptr <Config> b);

       /// Głowny model.
       Model::IModel *getModel () const;

       /**
        * 1. Odłącza poprzedni rootControloer od dispatcherów.
        * 2. Ustawia główny kontroler.
        * 3. Podłącza ten nowy do wszystkich dispatcherów.
        */
       S_ (setModel) void setModel (Model::IModel *model);

       /**
        * Resetuje stan, dropuje iterację, resetuje dispatchery,
        * resetuje tweeny etc.
        */
       void reset ();

       Ptr <Event::DispatcherList> getDispatchers () const;
       m_ (setDispatchers) void setDispatchers (Ptr <Event::DispatcherList> d);

       Ptr <ModelManager> getManager ();
       S_ (setManager) void setManager (Ptr <ModelManager> m);

       static App *instance ();
       static void setInstance (App *i) { instance_ = i; }

       /**
        * Powoduje zawieszenie wykonywania aktualnej iteracji i rozpoczęcie następnej.
        * Wszystkie czekające eventy zostają odrzucone etc.
        */
       void dropIteration ();
       bool getDropIteration () const;

private:

       Impl *impl;
       static App *instance_;

       E_ (App)
};

} // nam

extern Util::App *app ();
extern Util::Config *config ();
extern Util::ModelManager *manager ();

#	endif /* BAJKAAPP_H_ */
