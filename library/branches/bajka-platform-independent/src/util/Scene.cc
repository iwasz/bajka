/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Scene.h"
#include "model/IModel.h"
#include "model/manager/IModelManager.h"

namespace Util {
namespace M = Model;

struct Scene::Impl {

        Impl () : model (NULL), modelManager (NULL) {}

        M::IModel *model;
        M::IModelManager *modelManager;
};

/****************************************************************************/

Scene::Scene (M::IModelManager *m) : impl (new Impl)
{
        impl->modelManager = m;
}

/****************************************************************************/

Scene::~Scene ()
{
       delete impl;
}

/****************************************************************************/

void Scene::onStep ()
{
        uint32_t lastMs = getCurrentMs ();

#if 0
        int second = 0, frames = 0;
#endif

        int deltaMs = 0;
        Event::IEventDispather *dispatcher = getEventDispatcher ();

        while (!impl->quit) {
                bool newModelLoaded = impl->modelManager->run (this);

                if (newModelLoaded) {
                        assert (impl->model);
                        updateLayout (impl->model);
                }

                uint32_t currentMs = getCurrentMs ();
                deltaMs = currentMs - lastMs;
                lastMs = currentMs;

#if 0
                second += deltaMs;
                ++frames;

                if (second >= 1000) {
                        std::cerr << "fps=" << frames << std::endl;
                        frames = second = 0;
                }
#endif

                dispatcher->pollAndDispatch (impl->model, impl->eventIndex, &impl->pointerInsideIndex, &impl->glContext);

                impl->updateEvent.setDeltaMs (deltaMs);
                impl->model->update (&impl->updateEvent, this);

                Tween::Manager::getMain ()->update (deltaMs);

        }
}

} /* namespace Util */
