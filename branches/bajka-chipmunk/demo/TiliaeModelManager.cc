/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "TiliaeModelManager.h"
#include "../util/Exceptions.h"
#include "../util/BajkaApp.h"

namespace Demo {
using namespace Model;
using namespace Container;

void TiliaeModelManager::play (/*std::string const &parent, */std::string const &name)
{
        IModel *m = models[name];

        if (!m) {
                app->dropIteration ();

                Core::StringMap::const_iterator i = mapping.find (name);
                assertThrow (i != mapping.end (), "TiliaeModelManager::play : cant find model in mapping.");

                if (currentFile != i->second) {
                        currentFile = i->second;
                        childContainer = XmlContainerFactory::createContainer (currentFile, false, mainContainer);
                }

                m = ocast <IModel *> (childContainer->getBean (name));
        }

        app->setModel (m);
}

void TiliaeModelManager::pause (std::string const &name)
{

}

void TiliaeModelManager::stop (std::string const &name)
{

}

void TiliaeModelManager::cut (std::string const &name)
{

}


} /* namespace Demo */
