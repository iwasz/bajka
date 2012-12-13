/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "XmlModelManager.h"
#include "util/Scene.h"
#include <container/ContainerFactory.h>
#include <iostream>
#include "Platform.h"
#include "util/IDataSourceService.h"

namespace Model {

void XmlModelManager::load (std::string const &param1, std::string const &param2)
{
        requestedFile = param1;
        requestedName = param2;
        dirty = true;
}

/****************************************************************************/

IModel *XmlModelManager::get (std::string const &param1, std::string const &param2)
{
        try {
                Common::DataSource *ds = dataSourceService->newDataSource ();
                Ptr <Container::BeanFactoryContainer> newContainer = Container::ContainerFactory::createAndInit (Container::CompactMetaService::parseFile (ds, param1), false, mainContainer);
                dataSourceService->deleteDataSource (ds);
                Model::IModel *m = ocast <Model::IModel *> (newContainer->getBean (param2));

                // Tu następuje skasowanie starego modelu.
                childContainer = newContainer;
                return m;
        }
        catch (Core::Exception const &e) {
                printlog ("Manager : Core::Exception caught : %s\n", e.getMessage ().c_str ());
        }
        catch (std::exception const &e) {
                printlog ("Manager : std::exception caught : %s\n", e.what ());
        }
        catch (...) {
                printlog ("Manager : Unknown exception caught");
        }

        return NULL;
}

/****************************************************************************/

bool XmlModelManager::run (Util::Scene *scene)
{
        if (!dirty) {
                return false;
        }

        dirty = false;

        if (!childContainer && requestedFile.empty ()) {
                requestedFile = this->file;
                requestedName = this->name;
        }

        callOnManagerUnloadModel (scene);
        IModel *m = get (requestedFile, requestedName);

        if (m) {
                scene->setModel (m);
                callOnManagerLoadModel (scene);
        }

        return true;
}

/****************************************************************************/

void XmlModelManager::callOnManagerUnloadModel (Util::Scene *scene)
{
        scene->onManagerUnloadModel ();
}

/****************************************************************************/

void XmlModelManager::callOnManagerLoadModel (Util::Scene *scene)
{
        scene->onManagerUnloadModel ();
}

} /* namespace Model */
