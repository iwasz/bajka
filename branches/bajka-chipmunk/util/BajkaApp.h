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

       BajkaApp () : model (NULL), dropIteration_ (false) {}
       virtual ~BajkaApp () {}

       void init ();
       m_ (loop) void loop ();
       m_ (debug) void debug (Core::String const &);
       m_ (destroy) void destroy ();

/*--------------------------------------------------------------------------*/

       Ptr <BajkaConfig> getConfig () const { return config; }
       m_ (setConfig) void setConfig (Ptr <BajkaConfig> b) { config = b; }

       /// Głowny model.
       Model::IModel *getModel () const { return model; }

       /**
        * 1. Odłącza poprzedni rootControloer od dispatcherów.
        * 2. Ustawia główny kontroler.
        * 3. Podłącza ten nowy do wszystkich dispatcherów.
        */
       S_ (setModel) void setModel (Model::IModel *model);

       Ptr <Event::DispatcherList> getDispatchers () const { return dispatchers; }
       m_ (setDispatchers) void setDispatchers (Ptr <Event::DispatcherList> d);

       Ptr <ModelManager> getManager () { return manager; }
       S_ (setManager) void setManager (Ptr <ModelManager> m);

       static BajkaApp *instance ();
       static void setInstance (BajkaApp *i) { instance_ = i; }

       /**
        * Powoduje zawieszenie wykonywania aktualnej iteracji i rozpoczęcie następnej.
        * Wszystkie czekające eventy zostają odrzucone etc.
        */
       void dropIteration () { dropIteration_ = true;}
       bool getDropIteration () const { return dropIteration_; }

private:

       /// Szuka wśród modeli które mają trafić na które listy.
       unsigned int reindex (unsigned int eventMask, Model::IModel *m);

private:

       Ptr <BajkaConfig> config;
       Model::IModel *model;
       Ptr <Event::DispatcherList> dispatchers;
       Ptr <ModelManager> manager;
       ModelIndex listeners;
       static BajkaApp *instance_;
       bool dropIteration_;

       E_ (BajkaApp)
};

} // nam

extern Util::BajkaApp *app ();
extern Util::BajkaConfig *config ();
extern Util::ModelManager *manager ();

#	endif /* BAJKAAPP_H_ */
