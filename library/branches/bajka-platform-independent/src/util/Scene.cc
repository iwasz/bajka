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
#include "events/types/UpdateEvent.h"
#include "model/layout/LayerProperties.h"
#include "model/IBox.h"
#include "model/IGroup.h"
#include "Config.h"
#include "events/EventIdex.h"
#include "events/PointerInsideIndex.h"
#include "tween/Manager.h"
#include "events/types/ManagerEvent.h"
#include "util/UpdateContext.h"

namespace Util {
namespace M = Model;

struct Scene::Impl {

        Impl () : model (NULL), modelManager (NULL), config (NULL) {}

        M::IModel *model;
        M::IModelManager *modelManager;
        Config *config;
        Event::EventIndex eventIndex;
        Event::PointerInsideIndex pointerInsideIndex;
        Util::UpdateContext updateContext;
};

/****************************************************************************/

Scene::Scene (M::IModelManager *m, Config *c, View::GLContext *gl) : impl (new Impl)
{
        impl->modelManager = m;
        impl->config = c;
        impl->updateContext.config = c;
        impl->updateContext.glContext = gl;
}

/****************************************************************************/

Scene::~Scene ()
{
       delete impl;
}

/****************************************************************************/

void Scene::onStep (Event::UpdateEvent *updateEvent)
{
        bool newModelLoaded = impl->modelManager->run (this);

        if (newModelLoaded) {
                assert (impl->model);
                updateLayout ();
        }

        impl->model->update (updateEvent, &impl->updateContext);
        Tween::Manager::getMain ()->update (updateEvent->getDeltaMs ());
}

/****************************************************************************/

void Scene::setModel (Model::IModel *m)
{
        impl->model = m;
        impl->eventIndex.clear ();
        impl->pointerInsideIndex.clear ();
        impl->eventIndex.add (0xFFFFu & ~Event::MOUSE_EVENTS, m);

        if (m->isGroup ()) {
                Model::IGroup *g = dynamic_cast <Model::IGroup *> (m);
                g->setIndices (&impl->eventIndex, &impl->pointerInsideIndex);
        }
}

/****************************************************************************/

void Scene::reset ()
{
        impl->eventIndex.clear ();
        impl->pointerInsideIndex.clear ();
}

/****************************************************************************/

void Scene::onManagerLoadModel ()
{
        M::IModel *m = impl->model;
        Event::ManagerEvent event;

        if (m && m->getController () && m->getController ()->getEventMask () & Event::MANAGER_EVENT) {
                m->getController ()->onManagerLoad (&event, m, m->getView ());
        }
}

/****************************************************************************/

void Scene::onManagerUnloadModel ()
{
        Tween::Manager::getMain ()->killAll ();

        M::IModel *m = impl->model;
        Event::ManagerEvent event;

        if (m && m->getController () && m->getController ()->getEventMask () & Event::MANAGER_EVENT) {
                m->getController ()->onManagerUnload (&event, m, m->getView ());
        }
}

/****************************************************************************/

void Scene::updateLayout ()
{
        M::IGroupProperties const *props = impl->model->getGroupProps ();

        if (!props) {
                return;
        }

        M::LayerProperties const *scrProps = dynamic_cast <M::LayerProperties const *> (props);

        if (!scrProps) {
                return;
        }

        Model::IBox *box = dynamic_cast <Model::IBox *> (impl->model);

        if (!box) {
                return;
        }

        if (scrProps->fillW) {
                box->setWidth (impl->config->projectionWidth);
        }

        if (scrProps->fillH) {
                box->setHeight (impl->config->projectionHeight);

        }

        if (!scrProps->centerGroup || !impl->model->isGroup ()) {
                return;
        }

        M::IGroup *group = dynamic_cast <M::IGroup *> (impl->model);

        if (group->getCoordinateSystemOrigin () == M::IGroup::BOTTOM_LEFT) {
                Geometry::Point t;
                t.x = -box->getWidth () / 2.0;
                t.y = -box->getHeight () / 2.0;
                impl->model->setTranslate (t);
        }
        else {
                impl->model->setTranslate (Geometry::ZERO_POINT);
        }
}

} /* namespace Util */
