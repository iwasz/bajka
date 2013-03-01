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
#include "util/ReflectionMacros.h"

/**
 *
 */
class ReloadableXmlModelManager : public Model::XmlModelManager {
public:

        C__ (void)
        b_ ("XmlModelManager")

        ReloadableXmlModelManager () : lastFileTime (0), lastMs (0) {}
        virtual ~ReloadableXmlModelManager () {}

#ifndef ANDROID
        virtual bool run (Util::Scene *scene);
#endif

private:

        std::time_t lastFileTime;
        uint32_t lastMs;

        E_ (ReloadableXmlModelManager)
};

#endif /* XMLMODELMANAGER_H_ */
