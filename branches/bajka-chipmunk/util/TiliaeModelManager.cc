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

namespace Util {
using namespace Model;
using namespace Container;

void TiliaeModelManager::load (std::string const &name, bool cut)
{
        bool isCut = cut;

        /*
         * Kopię tworzymy, ponieważ podana w argumencie referencja do stringa (nazwa) może
         * wskazywać na obiekt, który przestanie istnieć kiedy skasuje się poprzedni kontnener.
         * Patrz niżej.
         */
        std::string nameCopy = name;

        Core::StringMap::const_iterator i = mapping.find (nameCopy);
        assertThrow (i != mapping.end (), "TiliaeModelManager::play : cant find model in mapping.");

        if (currentFile != i->second) {
                isCut = true;
                app->reset ();
                currentFile = i->second;

                /*
                 * W tym momencie, poniżej, tworzymy nowy kontener, ale stary jest kasowany,
                 * a z nim wszystko co w nim było, a więc i to co mogło wywołać tą metodę
                 * (na przykład guzik). Nawet obiekt stringa zawierający nazwę modelu do
                 * załadowania może przestać istnieć po tej linii. Dlatego mamy kopię.
                 */
                childContainer = XmlContainerFactory::createContainer (currentFile, false, mainContainer);
        }

        IModel *m = ocast <IModel *> (childContainer->getBean (nameCopy));

        if (!mainModel) {
                app->setModel (m);
        }
        else {
                if (isCut) {
                        mainModel->popChild ();
                }

                mainModel->addChild (m);
        }
}

/****************************************************************************/

void TiliaeModelManager::play (std::string const &name)
{
        load (name, false);
}

/****************************************************************************/

void TiliaeModelManager::cut (std::string const &name)
{
        load (name, true);
}

//void TiliaeModelManager::pause (std::string const &name)
//{
//
//}
//
//void TiliaeModelManager::stop (std::string const &name)
//{
//
//}



} /* namespace Util */
