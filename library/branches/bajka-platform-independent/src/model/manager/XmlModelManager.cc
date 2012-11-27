/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "XmlModelManager.h"
#include "util/IShell.h"
#include <container/ContainerFactory.h>
#include <iostream>

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

bool XmlModelManager::run (Util::IShell *shell)
{
        if (!dirty) {
                return false;
        }

        dirty = false;

        if (!childContainer && requestedFile.empty ()) {
                requestedFile = this->file;
                requestedName = this->name;
        }

        shell->onManagerUnloadModel ();
        IModel *m = get (requestedFile, requestedName);

        if (m) {
                shell->setModel (m);
                shell->onManagerLoadModel ();
        }

        return true;
}

} /* namespace Model */
