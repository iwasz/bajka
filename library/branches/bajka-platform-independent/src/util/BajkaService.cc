/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BajkaService.h"
#include "view/openGl/GLContext.h"
#include <container/beanFactory/BeanFactoryContainer.h>
#include <container/metaStructure/model/MetaContainer.h>
#include <container/inputFormat/compact/CompactMetaService.h>
#include <common/dataSource/DataSource.h>
#include <container/ContainerFactory.h>
#include "geometry/Point.h"
#include "geometry/Point3.h"
#include "geometry/LineString.h"
#include "model/layout/Align.h"
#include "model/layout/LinearGroup.h"
#include "Config.h"
#include "tween/Manager.h"
#include <view/freetype/Freetype.h>
#include "Platform.h"
#include "Scene.h"
#include "model/manager/IModelManager.h"
#include "ShellConfig.h"

/****************************************************************************/

static Util::Config *config_ = NULL;

Util::Config *config () { return config_; }
void config (Util::Config *c) { config_ = c; }

/****************************************************************************/

namespace Util {
using namespace Container;
namespace U = Util;
namespace M = Model;

/**
 * PIMPL
 */
struct BajkaService::Impl {

        Impl () : config (NULL) {}

        View::GLContext glContext;
        Ptr <Container::BeanFactoryContainer> configContainer;
        Ptr <Container::BeanFactoryContainer> mainContainer;
        Util::Config *config;

};

/****************************************************************************/

BajkaService::BajkaService () : impl (new Impl)
{
}

/****************************************************************************/

BajkaService::~BajkaService ()
{
        delete impl;
}

/****************************************************************************/

U::Config *BajkaService::loadConfig (std::string const &configFile, Core::VariantMap const &externalSingletons)
{
        Common::DataSource *ds = newDataSource ();

        try {
                printlog ("1");
                Ptr <MetaContainer> metaContainer = CompactMetaService::parseFile (ds, configFile);
                printlog ("2");
                impl->configContainer = ContainerFactory::create (metaContainer, true);
                printlog ("3");

                impl->configContainer->addConversion (typeid (Geometry::Point), Geometry::stringToPointVariant);
                impl->configContainer->addConversion (typeid (Geometry::Point3), Geometry::stringToPoint3Variant);
                impl->configContainer->addConversion (typeid (Geometry::LineString), Geometry::stringToLineStringVariant);
                impl->configContainer->addConversion (typeid (Model::HAlign), Model::stringToHAlign);
                impl->configContainer->addConversion (typeid (Model::VAlign), Model::stringToVAlign);
                impl->configContainer->addConversion (typeid (Model::HGravity), Model::stringToHGravity);
                impl->configContainer->addConversion (typeid (Model::VGravity), Model::stringToVGravity);
                impl->configContainer->addConversion (typeid (Model::LinearGroup::Type), Model::stringToLinearGroupType);
                printlog ("4");

                for (Core::VariantMap::const_iterator i = externalSingletons.begin (); i != externalSingletons.end (); ++i) {
                        impl->configContainer->addSingleton (i->first.c_str (), i->second);
                }
                printlog ("5");

                ContainerFactory::init (impl->configContainer.get (), metaContainer.get ());
                printlog ("6");

                impl->config = vcast <U::Config *> (impl->configContainer->getBean ("config"));
                printlog ("7");

                config (impl->config);

                printlog ("BajkaService::loadConfig : done.");
        }
        catch (std::exception const &e) {
                deleteDataSource (ds);
                throw;
        }

        deleteDataSource (ds);
        return impl->config;
}

/****************************************************************************/

U::Config *BajkaService::overrideConfig (Util::ShellConfig const &shellConfig, U::Config *config)
{
        if (shellConfig.fullScreen) {
                config->fullScreen = true;
                printlog ("BajkaService::overrideConfig : fullScreen turned on.");
        }

        if (shellConfig.showAABB) {
                config->showAABB = true;
                printlog ("BajkaService::overrideConfig : showAABB turned on.");
        }

        if (shellConfig.viewportWidth > 0) {
                config->viewportWidth = shellConfig.viewportWidth;
                printlog ("BajkaService::overrideConfig : viewportWidth overrided to %d.", shellConfig.viewportWidth);
        }

        if (shellConfig.viewportHeight > 0) {
                config->viewportHeight = shellConfig.viewportHeight;
                printlog ("BajkaService::overrideConfig : viewportHeight overrided to %d.", shellConfig.viewportHeight);
        }

        if (shellConfig.loopDelayMs > 0) {
                config->loopDelayMs = shellConfig.loopDelayMs;
                printlog ("BajkaService::overrideConfig : loopDelayMs overrided to %d.", shellConfig.loopDelayMs);
        }

        return config;
}

/****************************************************************************/

Util::Config *BajkaService::loadAndOverrideConfig (Util::ShellConfig const &cfg, Core::VariantMap const &externalSingletons)
{
        U::Config *c = loadConfig (cfg.configFile, externalSingletons);
        return overrideConfig (cfg, c);
}

/****************************************************************************/

void BajkaService::init (U::Config *config)
{
        srand (time (NULL));
        Tween::init ();

#ifdef WITH_FREETYPE
        if (ttfInit () < 0) {
                throw U::InitException ("TTF_Init failed");
        }
#endif

        impl->glContext.init (config);
}

/****************************************************************************/

void BajkaService::initProjectionMatrix (Util::Config *config)
{
        impl->glContext.initProjectionMatrix (config);
}

/****************************************************************************/

Util::Scene *BajkaService::loadScene (std::string const &sceneFile)
{
        Common::DataSource *ds = newDataSource ();
        U::Scene *scene = NULL;

        try {
                impl->mainContainer = Container::ContainerFactory::createAndInit (Container::CompactMetaService::parseFile (ds, sceneFile), true, impl->configContainer.get ());
                M::IModelManager *modelManager = ocast <M::IModelManager *> (impl->mainContainer->getBean ("modelManager"));
                scene = new U::Scene (modelManager, impl->config, &impl->glContext);
        }
        catch (std::exception const &e) {
                deleteDataSource (ds);
                throw;
        }

        deleteDataSource (ds);
        return scene;
}

/****************************************************************************/

View::GLContext *BajkaService::getGLContext ()
{
        return &impl->glContext;
}

} /* namespace Util */
