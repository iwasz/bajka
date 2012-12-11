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
#include "events/IEventDispather.h"
#include <view/freetype/Freetype.h>

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
        prepare (userData);

        // Datasource
        Common::DataSource *ds = newDataSource ();

        try {
                readConfig (ds, cfg);
                overrideConfig (cfg);
                initIndependent ();
                initDependent ();
                readDefinition (ds, cfg);
                loop ();
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
        printlog ("Exit from AbstractShell.");
        return EXIT_SUCCESS;
}

/****************************************************************************/

void AbstractShell::prepare (void *userData)
{
        impl->userData = userData;
}

/****************************************************************************/

void AbstractShell::readConfig (Common::DataSource *ds, Util::ShellConfig const &cfg)
{
        Ptr <MetaContainer> metaContainer = CompactMetaService::parseFile (ds, cfg.configFile);
        impl->configContainer = ContainerFactory::create (metaContainer, true);

        impl->configContainer->addConversion (typeid (Geometry::Point), Geometry::stringToPointVariant);
        impl->configContainer->addConversion (typeid (Geometry::Point3), Geometry::stringToPoint3Variant);
        impl->configContainer->addConversion (typeid (Geometry::LineString), Geometry::stringToLineStringVariant);
        impl->configContainer->addConversion (typeid (Model::HAlign), Model::stringToHAlign);
        impl->configContainer->addConversion (typeid (Model::VAlign), Model::stringToVAlign);
        impl->configContainer->addConversion (typeid (Model::HGravity), Model::stringToHGravity);
        impl->configContainer->addConversion (typeid (Model::VGravity), Model::stringToVGravity);
        impl->configContainer->addConversion (typeid (Model::LinearGroup::Type), Model::stringToLinearGroupType);

        ContainerFactory::init (impl->configContainer.get (), metaContainer.get ());
        impl->config = vcast <U::Config *> (impl->configContainer->getBean ("config"));
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

void AbstractShell::initIndependent ()
{
        srand (time (NULL));
        Tween::init ();

        if (ttfInit () < 0) {
                throw U::InitException ("TTF_Init failed");
        }
}

/****************************************************************************/

void AbstractShell::readDefinition (Common::DataSource *ds, Util::ShellConfig const &cfg)
{
        impl->mainContainer = Container::ContainerFactory::createAndInit (Container::CompactMetaService::parseFile (ds, cfg.definitionFile), true, impl->configContainer.get ());
        impl->modelManager = ocast <M::IModelManager *> (impl->mainContainer->getBean ("modelManager"));
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

                // swap buffers to display, since we're double buffered.
                swapBuffers ();

                // Tak śmiga, że damy delay
                delayMs (loopDelayMs); // 60fps
        }
}

/****************************************************************************/

void AbstractShell::destroy ()
{
        Tween::destroy ();
}

/****************************************************************************/

void AbstractShell::quit ()
{
        impl->quit = true;
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

} /* namespace Util */
