/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cstdlib>
#include <Container.h>
#include <ContainerFactory.h>
#include "ReflectionMacros.h"
#include "../util/BajkaApp.h"
#include "../model/Space.h"
#include "../model/Body.h"
#include "../view/Circle.h"
#include "../model/Circle.h"
#include "../view/draw/Primitives.h"
#include "../model/Box.h"
#include "../view/Polygon.h"
#include "../view/Rectangle.h"
#include "../controller/EmptyController.h"
#include "../model/StaticBody.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/trim.hpp>

#include<boost/tokenizer.hpp>

namespace M = Model;
namespace V = View;
namespace C = Controller;
namespace G = Geometry;

/**
 * Main entry.
 */
int main (int argc, char **argv)
{
        std::string fileName;

        if (argc > 1) {
                fileName = *(argv + 1);
        }
        else {
                fileName = "examples/chipmunk.xml";
        }

        // Nie robimy try-catch, bo i tak info zostanie wypisane.
        Ptr <Container::BeanFactoryContainer> container = Container::XmlContainerFactory::createContainer (fileName, true);
        Ptr <Util::BajkaApp> app = vcast <Ptr <Util::BajkaApp> > (container->getBean ("app"));

//        Ptr <M::Space> space = boost::make_shared <M::Space> ();
//        C::IController *controller = new C::EmptyController ();
//        controller->setEventMask (0xFFFF);
//        space->setController (controller);
//        space->setGravity (G::Point (0, -100));
//
//        M::Body *body = new M::Body ();
//        body->setMass (1);
//        space->addChild (body);
//
//        M::Circle *circle = new M::Circle ();
//        circle->setRadius (50);
//
//        V::Circle *circlev = new V::Circle ();
//        circlev->setForeground (V::Color (true));
//        circlev->setBackground (V::Color (true));
//        circle->setView (circlev);
//
//        M::Box *box = new M::Box ();
//        box->setPosition (G::Point (0, -50));
//        box->setWidth (50);
//        box->setHeight (50);
//        box->setView (new V::Rectangle ());
//
//        body->addChild (circle);
//        body->addChild (box);
//
//
//        body = new M::StaticBody (true);
//        body->setPosition (G::Point (-320, -140));
//        space->addChild (body);
//
//        box = new M::Box ();
//        box->setWidth (640);
//        box->setHeight (10);
//        box->setView (new V::Rectangle ());
//
//        body->addChild (box);
//
//        app->setModel (space);

        try {
                app->loop ();
                app->destroy ();
        }
        catch (std::exception const &e) {
                std::cerr << "Exception caught : " << e.what () << std::endl;
        }
        catch (...) {
                std::cerr << "Unknown exception." << std::endl;
        }


        return EXIT_SUCCESS;
}
