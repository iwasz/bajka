/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef XMLMODELMANAGER_H_
#define XMLMODELMANAGER_H_

#include <container/Container.h>
#include "AbstractModelManager.h"

namespace Model {

/**
 *
 */
class XmlModelManager : public AbstractModelManager {
public:

        C__ (void)
        XmlModelManager () : dirty (true), mainContainer (NULL) {}
        virtual ~XmlModelManager () {}

        virtual void load (std::string const &file, std::string const &name);
        virtual Model::IModel *get (std::string const &file, std::string const &name);
        virtual bool run (Util::Scene *scene);

protected:

        // Wartość początkowa
        std::string p_ (file);
        // Wartość początkowa
        std::string p_ (name);

        // Wartość następna
        std::string requestedFile;
        // Wartość następna
        std::string requestedName;
        bool dirty;

        Container::BeanFactoryContainer *p_ (mainContainer);
        Ptr <Container::BeanFactoryContainer> childContainer;

        E_ (XmlModelManager)
};

} /* namespace Model */
#endif /* XMLMODELMANAGER_H_ */
