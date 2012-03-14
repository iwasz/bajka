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

using Event::ModelIndex;

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
class BajkaApp : public Core::Object {
public:

       C__ (void)

       BajkaApp ();
       virtual ~BajkaApp ();

       void init ();
       m_ (loop) void loop ();
       m_ (debug) void debug (Core::String const &);
       m_ (destroy) void destroy ();

/*--------------------------------------------------------------------------*/

       Ptr <BajkaConfig> getConfig () const;
       m_ (setConfig) void setConfig (Ptr <BajkaConfig> b);

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

       static BajkaApp *instance ();
       static void setInstance (BajkaApp *i) { instance_ = i; }

       /**
        * Powoduje zawieszenie wykonywania aktualnej iteracji i rozpoczęcie następnej.
        * Wszystkie czekające eventy zostają odrzucone etc.
        */
       void dropIteration ();
       bool getDropIteration () const;

private:

       /// Szuka wśród modeli które mają trafić na które listy.
       unsigned int reindex (unsigned int eventMask, Model::IModel *m);

private:

       Impl *impl;
       static BajkaApp *instance_;

       E_ (BajkaApp)
};

} // nam

extern Util::BajkaApp *app ();
extern Util::BajkaConfig *config ();
extern Util::ModelManager *manager ();

#	endif /* BAJKAAPP_H_ */
