/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BajkaService.h"
#include "IShell.h"
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

using Model::IModelManager;

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

BajkaService::BajkaService () : impl (new Impl) {}

/****************************************************************************/

BajkaService::~BajkaService ()
{
        delete impl;
}

/****************************************************************************/

U::Config *BajkaService::loadConfig (Common::DataSource *ds, Util::ShellConfig const &cfg)
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
        printlog ("BajkaService::loadConfig : done.");
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

Util::Config *BajkaService::loadAndOverrideConfig (Common::DataSource *dataDource, Util::ShellConfig const &cfg)
{
        U::Config *c = loadConfig (dataDource, cfg);
        return overrideConfig (cfg, c);
}

/****************************************************************************/

void BajkaService::init (U::Config *config)
{
        srand (time (NULL));
        Tween::init ();

        if (ttfInit () < 0) {
                throw U::InitException ("TTF_Init failed");
        }

        impl->glContext.init (config);
}

/****************************************************************************/

void BajkaService::initProjectionMatrix (Util::Config *config)
{
        impl->glContext.initProjectionMatrix (config);
}

/****************************************************************************/

Util::Scene *BajkaService::loadScene (Common::DataSource *ds, Util::ShellConfig const &cfg)
{
        impl->mainContainer = Container::ContainerFactory::createAndInit (Container::CompactMetaService::parseFile (ds, cfg.definitionFile), true, impl->configContainer.get ());
        M::IModelManager *modelManager = ocast <M::IModelManager *> (impl->mainContainer->getBean ("modelManager"));
        U::Scene *scene = new U::Scene (modelManager);
        return scene;
}

} /* namespace Util */
