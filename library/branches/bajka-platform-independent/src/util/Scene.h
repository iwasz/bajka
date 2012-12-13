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
class XmlModelManager; // Wywołuje prywatne handlery.
}

namespace Event {
class UpdateEvent;
}

namespace Util {
class Config;

/**
 *
 */
class Scene {
public:

        Scene (Model::IModelManager *modelManager, Config *c);
        ~Scene ();

        void onStep (Event::UpdateEvent *updateEvent);
        void setModel (Model::IModel *m);
        void reset ();

private:

        void updateLayout ();
        friend class Model::XmlModelManager;
        void onManagerLoadModel ();
        void onManagerUnloadModel ();

private:

        struct Impl;
        Impl *impl;
};

} /* namespace Util */
#endif /* SCENE_H_ */
