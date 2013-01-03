/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ReloadableXmlModelManager.h"
#ifndef ANDROID
#include <boost/filesystem.hpp>
#endif
#include <iostream>
#include <model/IModel.h>
#include <Platform.h>
#include <tween/Manager.h>
#include <container/Container.h>

/****************************************************************************/

#ifndef ANDROID
bool ReloadableXmlModelManager::run (Util::Scene *scene)
{
        uint32_t currentMs = getCurrentMs ();
        std::time_t currentFileTime;

        if (!requestedFile.empty () && currentMs - lastMs > 500u) {
                currentFileTime = boost::filesystem::last_write_time (requestedFile);

                if (currentFileTime != lastFileTime) {
                        dirty = true;
                }

                lastMs = currentMs;
        }

        if (!dirty) {
                return false;
        }

        if (!childContainer && requestedFile.empty ()) {
                requestedFile = this->file;
                requestedName = this->name;
        }

        dirty = false;
        lastFileTime = boost::filesystem::last_write_time (requestedFile);

        scene->onManagerUnloadModel ();
        Model::IModel *m = get (requestedFile, requestedName);

        if (m) {
                shell->setModel (m);
                shell->onManagerLoadModel ();
        }

        return true;
}
#endif

