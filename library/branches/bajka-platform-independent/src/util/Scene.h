/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SCENE_H_
#define BAJKA_SCENE_H_

namespace Model {
class IModelManager;
class IModel;
class AbstractModelManager; // Wywołuje prywatne handlery.
}

namespace View {
class GLContext;
}

namespace Event {
class UpdateEvent;
class PointerInsideIndex;
class EventIndex;
}

namespace Util {
class Config;

/**
 *
 */
class Scene {
public:

        Scene (Model::IModelManager *modelManager, Config *c, View::GLContext *gl);
        ~Scene ();

        void onStep (Event::UpdateEvent *updateEvent);
        void reset ();

        void setModel (Model::IModel *m);
        Model::IModel *getModel ();

        Event::EventIndex *getEventIndex ();
        Event::PointerInsideIndex *getPointerInsideIndex ();

private:

        void updateLayout ();
        friend class Model::AbstractModelManager;
        void onManagerLoadModel ();
        void onManagerUnloadModel ();

private:

        struct Impl;
        Impl *impl;
};

} /* namespace Util */
#endif /* SCENE_H_ */
