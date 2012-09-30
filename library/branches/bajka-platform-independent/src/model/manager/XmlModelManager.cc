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
                childContainer.reset ();
                childContainer = Container::ContainerFactory::createAndInit (Container::CompactMetaService::parseFile (param1), false, mainContainer);
                IModel *m = ocast <IModel *> (childContainer->getBean (param2));
                return m;
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

        shell->notifyUnloadModel ();
        IModel *m = get (requestedFile, requestedName);

        if (m) {
                shell->setModel (m);
                shell->notifyLoadModel ();
        }

        return true;
}

} /* namespace Model */
