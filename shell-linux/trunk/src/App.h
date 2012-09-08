/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/
#if 0
#ifndef BAJKAAPP_H_
#define BAJKAAPP_H_

#include "Geometry.h"
#include "Model.h"
#include "ReflectionMacros.h"
#include "../events/types/IEvent.h"
#include "ModelManager.h"
#include "Config.h"

#ifdef ANDROID
#include <android/input.h>
namespace Util {
struct AndroidEngine;
}
#endif

namespace Util {
class Impl;

/**
 * Bajka application. It is bound to OpenGL and is not meant to
 * be used with any other technologies (i.e. DirectX). Implements
 * the main loop.
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

       Config *getConfig () const;
       m_ (setConfig) void setConfig (Config *b);

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

//       Event::DispatcherList *getDispatchers () const;
//       m_ (setDispatchers) void setDispatchers (Event::DispatcherList *d);

       ModelManager *getManager ();
       S_ (setManager) void setManager (ModelManager *m);

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

#endif /* BAJKAAPP_H_ */
#endif
