/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TILIAEMODELMANAGER_H_
#define TILIAEMODELMANAGER_H_

#include <Container.h>
#include "../util/ModelManager.h"
#include "../util/ReflectionMacros.h"

namespace Demo {

class TiliaeModelManager : public Util::ModelManager {
public:
        C__ (void)
        b_ ("ModelManager")

        virtual ~TiliaeModelManager () {}

        virtual void play (/*std::string const &parent, */std::string const &name);
        virtual void pause (std::string const &name);
        virtual void stop (std::string const &name);
        virtual void cut (std::string const &name);

        void setMainContainer (Ptr <Container::BeanFactoryContainer> mc) { mainContainer = mc; }

        Core::StringMap const &getMapping () const { return mapping; }

        /// Nazwa modelu -> plik.
        m_ (setMapping) void setMapping (Core::StringMap const &m) { mapping = m; }

private:

        // TODO żeby IoC umiał sam to ustawiać.
        Ptr <Container::BeanFactoryContainer> mainContainer;
        Ptr <Container::BeanFactoryContainer> childContainer;
        Core::StringMap mapping;
        std::string currentFile;

        E_ (TiliaeModelManager)
};

} /* namespace Demo */

#	endif /* TILIAEMODELMANAGER_H_ */
