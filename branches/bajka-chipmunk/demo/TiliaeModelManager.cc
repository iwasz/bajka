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
        /*
         * Kopię tworzymy, ponieważ podana w argumencie referencja do stringa (nazwa) może
         * wskazywać na obiekt, który przestanie istnieć kiedy skasuje się poprzedni kontnener.
         * Patrz niżej.
         */
        std::string nameCopy = name;
        IModel *m = models[nameCopy];

        if (!m) {
                app->dropIteration ();

                Core::StringMap::const_iterator i = mapping.find (nameCopy);
                assertThrow (i != mapping.end (), "TiliaeModelManager::play : cant find model in mapping.");

                if (currentFile != i->second) {
                        currentFile = i->second;

                        /*
                         * W tym momencie, poniżej, tworzymy nowy kontener, ale stary jest kasowany,
                         * a z nim wszystko co w nim było, a więc i to co mogło wywołać tą metodę
                         * (na przykład guzik). Nawet obiekt stringa zawierający nazwę modelu do
                         * załadowania może przestać istnieć po tej linii. Dlatego mamy kopię.
                         */
                        childContainer = XmlContainerFactory::createContainer (currentFile, false, mainContainer);
                }

                m = ocast <IModel *> (childContainer->getBean (nameCopy));
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
