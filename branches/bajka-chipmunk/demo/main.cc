/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cstdlib>
//#include "IWidget.h"

#include "BajkaApp.h"

#include <Container.h>
#include <ContainerFactory.h>

//#include "sequence/ConstSequence.h"

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


        Ptr <M::CPSpace> space = boost::make_shared <M::CPSpace> ();
        space->setGravity (G::Vector (0, -100));

        M::CPBody *body = new M::CPBody ();
        body->setMass (1);
        V::IView *view = new V::Circle ();
        body->setView (view);
        space->addChild (body);


        M::CPCircle *circle = new M::CPCircle ();
        circle->setRadius (5);
        circle->setView (view);

        body->addChild (circle);




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
