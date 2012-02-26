/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "../util/BajkaApp.h"
#include <cstdlib>
#include <Container.h>
#include <ContainerFactory.h>
#include "TiliaeModelManager.h"
#include "LoadButtonController.h"

using Demo::TiliaeModelManager;

/**
 * Main entry.
 */
int main (int argc, char **argv)
{
        Model::Box *mb = new Model::Box;
        std::cerr << "Model::Box " << std::hex << (unsigned long int)mb << std::endl;

        Model::IModel *m = mb;
        std::cerr << "Model::IModel " << std::hex << (unsigned long int)m << std::endl;

        assert (m == mb);
//        assert ((unsigned long)m == (unsigned long)mb);


        Core::Object *o = mb;
        std::cerr << "Core::Object " << std::hex << (unsigned long int)o << std::endl;

        assert (dynamic_cast <Model::AbstractModel *> (m));

        void *ptr = static_cast <Core::Object *> (m);
        assert (dynamic_cast <Model::AbstractModel *> (static_cast <Core::Object *> (ptr)));


        Core::Variant v (o);
        Model::AbstractModel *a = ocast <Model::AbstractModel *> (v);
        assert (a);

        std::cerr << v.toString () << ", " << typeid (Model::AbstractModel).name () << std::endl;

        std::string fileName;

        if (argc > 1) {
                fileName = *(argv + 1);
        }
        else {
                fileName = "examples/chipmunk.xml";
        }

        try {
                Ptr <Container::BeanFactoryContainer> container = Container::XmlContainerFactory::createContainer (fileName, true);
                Ptr <Util::BajkaApp> app = vcast <Ptr <Util::BajkaApp> > (container->getBean ("app"));
                app->setInstance (app.get ());
                // TODO to się powinno samo ustawiać w XML.
                Demo::TiliaeModelManager *manager = vcast <Demo::TiliaeModelManager *> (container->getBean ("modelManager"));
                manager->setMainContainer (container);
                manager->play ("space2");

                app->init ();
                app->loop ();
                app->destroy ();
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


        return EXIT_SUCCESS;
}
