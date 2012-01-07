/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <Container.h>
#include <ContainerFactory.h>

#include "../../util/BajkaApp.h"
#include "PlatformerApp.h"
#include "SimpleController.h"
#include "../../controller/IController.h"

using namespace Container2;
using Controller::IController;

void PlatformerApp::load (Core::String const &xmlFile, Core::String const &controller)
{
        doLoad = true;
        this->xmlFile = xmlFile;
        this->controller = controller;
}

/****************************************************************************/

void PlatformerApp::afterEvents ()
{
        if (doLoad) {
                // Załaduj plik z levelem, czy z czymś tam.
                levelContainer = XmlContainerFactory::createContainer (xmlFile, false, mainContainer);

                // Pobierz z nieg wskazany kontroler.
                Ptr <IController> levelCtr = vcast <Ptr <IController> > (levelContainer->getBean (controller));

                // Ustaw jako główny kontroler.
                setRootController (levelCtr);
                doLoad = false;
        }
}
