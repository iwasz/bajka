/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "TiliaeModelManager.h"
#include "../util/Exceptions.h"
#include "../util/App.h"
#include <ContainerFactory.h>
#include <inputFormat/mxml/MXmlMetaService.h>

namespace Util {
using namespace Model;
using namespace Container;

void TiliaeModelManager::load (std::string const &name, bool cut)
{
        bool isCut = cut;
        app->dropIteration ();

        /*
         * Kopię tworzymy, ponieważ podana w argumencie referencja do stringa (nazwa) może
         * wskazywać na obiekt, który przestanie istnieć kiedy skasuje się poprzedni kontnener.
         * Patrz niżej.
         */
        std::string nameCopy = name;

        Core::StringMap::const_iterator i = mapping.find (nameCopy);
        assertThrow (i != mapping.end (), "TiliaeModelManager::play : cant find model in mapping.");

        if (currentFile != i->second) {

                Model::IModel *currentModel = mainModel->getTop ();

                // Wywołaj handler eventu w kontrolerze.
                if (currentModel && currentModel->getController () && currentModel->getController ()->getEventMask () & Event::MANAGER_EVENT) {
                        currentModel->getController ()->onManagerUnload (&event, currentModel, currentModel->getView ());
                }

                // Zdejmujemy stary model, bo on zaraz przestanie istnieć.
                mainModel->popChild ();

                // Ustawiam isCunt na false, żeby nie zrobić popChild drugi raz.
                isCut = false;
                currentFile = i->second;

                /*
                 * W tym momencie, poniżej, tworzymy nowy kontener, ale stary jest kasowany,
                 * a z nim wszystko co w nim było, a więc i to co mogło wywołać tą metodę
                 * (na przykład guzik). Nawet obiekt stringa zawierający nazwę modelu do
                 * załadowania może przestać istnieć po tej linii. Dlatego mamy kopię.
                 */
                childContainer = ContainerFactory::createContainer (MXmlMetaService::parseFile (currentFile), false, mainContainer);

/*--------------poniżej tej linii stary model już nie istnieje----------------------------------------------------------------------------------------------------------------------------------------------------*/
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

        // Wywołaj handler eventu w kontrolerze.
        if (m && m->getController () && m->getController ()->getEventMask () & Event::MANAGER_EVENT) {
                m->getController ()->onManagerLoad (&event, m, m->getView ());
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

} /* namespace Util */
