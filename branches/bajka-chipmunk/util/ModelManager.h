/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA1_SCENEMANAGER_H_
#define BAJKA1_SCENEMANAGER_H_

#include <string>
#include <Object.h>
#include "../model/IModel.h"
#include "ReflectionMacros.h"

namespace Util {
class BajkaApp;

/**
 * Przyporządkowuje nazwy modelom i ułatwia ich tworzenie i wyświetlanie.
 */
class ModelManager : public Core::Object {
public:

        C__ (void)
        virtual ~ModelManager () {}

        m_ (play) virtual void play (/*std::string const &parent, */std::string const &name);
        m_ (pause) virtual void pause (std::string const &name);
        m_ (stop) virtual void stop (std::string const &name);
        m_ (cut) virtual void cut (std::string const &name);

        void set (std::string const &key, Model::IModel *m) { models[key] = m; }
        Model::IModel *get (std::string const &key) const
        {
                Model::ModelMap::const_iterator i = models.find (key);
                return (i != models.end ()) ? (i->second) : (NULL);
        }

        m_ (setModels) void setModels (Model::ModelMap const& models) { this->models = models; }
        m_ (getModels) Model::ModelMap const &getModels () const { return models; }

        BajkaApp *getApp () { return app; }
        void setApp (BajkaApp *a) { app = a; }

protected:

        Model::ModelMap models;
        BajkaApp *app;

        E_ (ModelManager)
};

} /* namespace Util */

#	endif /* SCENEMANAGER_H_ */
