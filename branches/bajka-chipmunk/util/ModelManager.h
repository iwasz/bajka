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
#include "../model/IGroup.h"
#include "ReflectionMacros.h"

namespace Util {
class BajkaApp;

/**
 * Przyporządkowuje nazwy modelom i ułatwia ich tworzenie i wyświetlanie.
 */
class ModelManager : public Core::Object {
public:

        d__
        ModelManager () : mainModel (NULL), app (NULL) {}
        virtual ~ModelManager () {}

        m_ (play) virtual void play (std::string const &name) = 0;
//        m_ (pause) virtual void pause (std::string const &name) = 0;
//        m_ (stop) virtual void stop (std::string const &name) = 0;
        m_ (cut) virtual void cut (std::string const &name) = 0;

        void set (std::string const &key, Model::IModel *m) { models[key] = m; }
        Model::IModel *get (std::string const &key) const
        {
                Model::ModelMap::const_iterator i = models.find (key);
                return (i != models.end ()) ? (i->second) : (NULL);
        }

        m_ (setModels) void setModels (Model::ModelMap const& models) { this->models = models; }
        m_ (getModels) Model::ModelMap const &getModels () const { return models; }

        m_ (getMainModel) Model::IGroup *getMainModel () { return mainModel; }
        S_ (setMainModel) void setMainModel (Model::IGroup *g) { mainModel = g; }

        BajkaApp *getApp () { return app; }
        void setApp (BajkaApp *a) { app = a; }

protected:

        Model::ModelMap models;
        Model::IGroup *mainModel;
        BajkaApp *app;

        E_ (ModelManager)
};

} /* namespace Util */

#	endif /* SCENEMANAGER_H_ */
