/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef RELOADABLE_XMLMODELMANAGER_H_
#define RELOADABLE_XMLMODELMANAGER_H_

#include <model/manager/XmlModelManager.h>
#include <container/Container.h>

class ReloadableXmlModelManager : public Model::XmlModelManager {
public:

        C__ (void)
        b_ ("XmlModelManager")

        ReloadableXmlModelManager () : lastFileTime (0), lastMs (0) {}
        virtual ~ReloadableXmlModelManager () {}

        virtual Model::IModel *get (std::string const &file, std::string const &name);
        virtual bool run (Util::IShell *shell);

private:

        std::time_t lastFileTime;
        uint32_t lastMs;

        E_ (ReloadableXmlModelManager)
};

#endif /* XMLMODELMANAGER_H_ */
