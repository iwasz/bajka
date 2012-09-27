/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef XMLMODELMANAGER_H_
#define XMLMODELMANAGER_H_

#include "IModelManager.h"
#include <container/Container.h>

namespace Model {

class XmlModelManager : public IModelManager {
public:

        C__ (void)

        XmlModelManager () : dirty (true), mainContainer (NULL) {}
        virtual ~XmlModelManager () {}
        virtual void load (std::string const &file, std::string const &name);
        virtual Model::IModel *get (std::string const &file, std::string const &name);
        virtual bool run (Util::IShell *shell);

private:

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
