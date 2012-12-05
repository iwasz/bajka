/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AbstractShell.h"
#include "AbstractShellImpl.h"
#include <container/Container.h>
#include <container/ContainerFactory.h>
#include <container/inputFormat/compact/CompactMetaService.h>
#include <container/metaStructure/model/MetaContainer.h>
#include "geometry/Point.h"
#include "geometry/Point3.h"
#include "geometry/LineString.h"
#include "model/layout/Align.h"
#include "model/layout/LinearGroup.h"
#include "model/IGroup.h"
#include "model/layout/LayerProperties.h"
#include "events/types/ManagerEvent.h"
#include "tween/Manager.h"
#include "Platform.h"
#include "model/manager/IModelManager.h"
#include "common/dataSource/DataSource.h"

namespace Util {
using namespace Container;
using Reflection::Manager;
namespace M = Model;
namespace V = View;
namespace C = Controller;
namespace E = Event;
namespace U = Util;

/****************************************************************************/

AbstractShell::AbstractShell () : impl (new AbstractShellImpl) {}
AbstractShell::~AbstractShell () { delete impl; }

/****************************************************************************/

int AbstractShell::run (Util::ShellConfig const &cfg, void *userData)
{
        impl->userData = userData;
        Common::DataSource *ds = newDataSource ();

        try {
                {
                        Ptr <MetaContainer> metaContainer = CompactMetaService::parseFile (ds, cfg.configFile);
                        Ptr <BeanFactoryContainer> container = ContainerFactory::create (metaContainer, true);

                        container->addConversion (typeid (Geometry::Point), Geometry::stringToPointVariant);
                        container->addConversion (typeid (Geometry::Point3), Geometry::stringToPoint3Variant);
                        container->addConversion (typeid (Geometry::LineString), Geometry::stringToLineStringVariant);
                        container->addConversion (typeid (Model::HAlign), Model::stringToHAlign);
                        container->addConversion (typeid (Model::VAlign), Model::stringToVAlign);
                        container->addConversion (typeid (Model::HGravity), Model::stringToHGravity);
                        container->addConversion (typeid (Model::VGravity), Model::stringToVGravity);
                        container->addConversion (typeid (Model::LinearGroup::Type), Model::stringToLinearGroupType);

                        ContainerFactory::init (container.get (), metaContainer.get ());
                        impl->config = vcast <U::Config *> (container->getBean ("config"));
                        overrideConfig (cfg);

                        init ();

                        Ptr <BeanFactoryContainer> container2 = Container::ContainerFactory::createAndInit (Container::CompactMetaService::parseFile (ds, cfg.definitionFile), true, container.get ());
                        impl->modelManager = ocast <M::IModelManager *> (container2->getBean ("modelManager"));

                        loop ();
                }

                destroy ();
        }
        catch (Core::Exception const &e) {
                printlog ("Core::Exception caught : %s\n", e.getMessage ().c_str ());
        }
        catch (std::exception const &e) {
                printlog ("std::exception caught : %s\n", e.what ());
        }
        catch (...) {
                printlog ("Unknown exception caught");
        }

        deleteDataSource (ds);
        return EXIT_SUCCESS;
}

/****************************************************************************/

void AbstractShell::loop ()
{
        uint32_t lastMs = getCurrentMs ();

#if 0
        int second = 0, frames = 0;
#endif

        int loopDelayMs = impl->config->loopDelayMs;
        int deltaMs = 0;

        while (impl->loopActive) {
                if (!impl->loopPaused) {

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
                }

                dispatchEvents ();

                static int i = 0;
                if (!impl->loopPaused) {
                        if (++i > 3) {
                                impl->updateEvent.setDeltaMs (deltaMs);
                                impl->model->update (&impl->updateEvent, this);

                                Tween::Manager::getMain ()->update (deltaMs);

                                // swap buffers to display, since we're double buffered.
                                swapBuffers ();
                        }
                }

                // Tak śmiga, że damy delay
                delayMs (loopDelayMs); // 60fps
        }
}

/****************************************************************************/

void AbstractShell::init ()
{
        srand (time (NULL));
        Tween::init ();

#ifndef ANDROID // TODO To nie może tak być!
        impl->glContext.init (impl->config);
#endif
}

/****************************************************************************/

void AbstractShell::destroy ()
{
        Tween::destroy ();
}

/****************************************************************************/

void AbstractShell::overrideConfig (Util::ShellConfig const &cfg)
{
        if (cfg.fullScreen) {
                impl->config->fullScreen = true;
        }

        if (cfg.showAABB) {
                impl->config->showAABB = true;
        }

        if (cfg.viewportWidth > 0) {
                impl->config->viewportWidth = cfg.viewportWidth;
        }

        if (cfg.viewportHeight > 0) {
                impl->config->viewportHeight = cfg.viewportHeight;
        }

        if (cfg.loopDelayMs > 0) {
                impl->config->loopDelayMs = cfg.viewportHeight;
        }
}

/****************************************************************************/

void AbstractShell::quit ()
{
        impl->loopActive = false;
}

/****************************************************************************/

Model::IModel *AbstractShell::getModel ()
{
        return impl->model;
}

/****************************************************************************/

void AbstractShell::setModel (Model::IModel *m)
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

void AbstractShell::reset ()
{
        impl->eventIndex.clear ();
        impl->pointerInsideIndex.clear ();
}

/****************************************************************************/

Util::Config *AbstractShell::getConfig ()
{
        return impl->config;
}

/****************************************************************************/

void AbstractShell::onManagerLoadModel ()
{
        M::IModel *m = impl->model;
        Event::ManagerEvent event;

        if (m && m->getController () && m->getController ()->getEventMask () & Event::MANAGER_EVENT) {
                m->getController ()->onManagerLoad (&event, m, m->getView ());
        }
}

/****************************************************************************/

void AbstractShell::onManagerUnloadModel ()
{
        Tween::Manager::getMain ()->killAll ();

        M::IModel *m = impl->model;
        Event::ManagerEvent event;

        if (m && m->getController () && m->getController ()->getEventMask () & Event::MANAGER_EVENT) {
                m->getController ()->onManagerUnload (&event, m, m->getView ());
        }
}

/****************************************************************************/

void AbstractShell::updateLayout (Model::IModel *root)
{
        M::IGroupProperties const *props = root->getGroupProps ();

        if (!props) {
                return;
        }

        M::LayerProperties const *scrProps = dynamic_cast <M::LayerProperties const *> (props);

        if (!scrProps) {
                return;
        }

        Model::IBox *box = dynamic_cast <Model::IBox *> (root);

        if (!box) {
                return;
        }

        if (scrProps->fillW) {
                box->setWidth (impl->config->projectionWidth);
        }

        if (scrProps->fillH) {
                box->setHeight (impl->config->projectionHeight);

        }

        if (!scrProps->centerGroup || !root->isGroup ()) {
                return;
        }

        M::IGroup *group = dynamic_cast <M::IGroup *> (root);

        if (group->getCoordinateSystemOrigin () == M::IGroup::BOTTOM_LEFT) {
                Geometry::Point t;
                t.x = -box->getWidth () / 2.0;
                t.y = -box->getHeight () / 2.0;
                root->setTranslate (t);
        }
        else {
                root->setTranslate (Geometry::ZERO_POINT);
        }
}

/****************************************************************************/

View::GLContext *AbstractShell::getGLContext ()
{
        return &impl->glContext;
}

/****************************************************************************/

void AbstractShell::pause ()
{
        impl->loopPaused = true;
}

/****************************************************************************/

void AbstractShell::resume ()
{
        impl->loopPaused = false;
}

/****************************************************************************/

bool AbstractShell::isPaused () const
{
        return impl->loopPaused;
}

} /* namespace Util */
