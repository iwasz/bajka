/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ReloadableXmlModelManager.h"
#include <boost/filesystem.hpp>
#include <iostream>
#include <util/IShell.h>
#include <model/IModel.h>
#include <Platform.h>
#include <tween/Manager.h>

/****************************************************************************/

Model::IModel *ReloadableXmlModelManager::get (std::string const &param1, std::string const &param2)
{
        try {
                Ptr <Container::BeanFactoryContainer> newContainer = Container::ContainerFactory::createAndInit (Container::CompactMetaService::parseFile (param1), false, mainContainer);
                Model::IModel *m = ocast <Model::IModel *> (newContainer->getBean (param2));

                // Tu następuje skasowanie starego modelu.
                childContainer = newContainer;
                return m;
        }
        catch (Core::Exception const &e) {
                std::cerr << "Exception caught : \n" << e.getMessage () << std::endl;
        }
        catch (std::exception const &e) {
                std::cerr << "exception caught : " << e.what () << std::endl;
        }
        catch (...) {
                std::cerr << "Unknown exception." << std::endl;
        }

        return NULL;
}

/****************************************************************************/

bool ReloadableXmlModelManager::run (Util::IShell *shell)
{
        uint32_t currentMs = getCurrentMs ();
        std::time_t currentFileTime;

        if (!requestedFile.empty () && currentMs - lastMs > 500u) {
                currentFileTime = boost::filesystem::last_write_time (requestedFile);

                if (currentFileTime != lastFileTime) {
                        dirty = true;
                }

                lastMs = currentMs;
        }

        if (!dirty) {
                return false;
        }

        if (!childContainer && requestedFile.empty ()) {
                requestedFile = this->file;
                requestedName = this->name;
        }

        dirty = false;
        lastFileTime = boost::filesystem::last_write_time (requestedFile);

        shell->onManagerUnloadModel ();
        Model::IModel *m = get (requestedFile, requestedName);

        if (m) {
                shell->setModel (m);
                shell->onManagerLoadModel ();
        }

        return true;
}

