/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "../util/BajkaApp.h"
#include "../model/Space.h"
#include "../model/Body.h"
#include "../view/Circle.h"
#include "../model/Circle.h"

#include <cstdlib>
#include <Container.h>
#include <ContainerFactory.h>
#include "../view/draw/Primitives.h"
#include "../model/Box.h"
#include "../view/Polygon.h"

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


        Ptr <M::Space> space = boost::make_shared <M::Space> ();
        space->setGravity (G::Point (0, -100));

        M::Body *body = new M::Body ();
        body->setMass (1);
        space->addChild (body);


        M::Circle *circle = new M::Circle ();
        circle->setRadius (50);
        circle->setView (new V::Circle ());

//        M::Box *box = new M::Box ();
//        box->setPosition (G::Point (0, -50));
//        box->setWidth (50);
//        box->setHeight (50);
//        box->setView (new V::Rectangle ());

        body->addChild (circle);
//        body->addChild (box);

//        Ptr <M::IModel> model = boost::make_shared <M::Box> (0, 0, 30, 30);
//
//        V::IView *view = new V::Rectangle ();
//        C::IController *c = new C::EmptyController ();
//        model->setView (view);
//        model->setController(c);
//        model->setAngle (1);



        app->setModel (space);

        app->loop ();
        app->destroy ();
        return EXIT_SUCCESS;
}
