/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IMODELMANAGER_H_
#define IMODELMANAGER_H_

#include <string>
#include <core/Object.h>
#include "model/IModel.h"

namespace Util {
struct Scene;
}

namespace Model {

/**
 * Ładuje modele.
 */
struct IModelManager : public Core::Object {

        virtual ~IModelManager () {}

        virtual void load (std::string const &param1, std::string const &param2) = 0;
        virtual Model::IModel *get (std::string const &param1, std::string const &param2) = 0;

        /*
         * Metoda dla Shella. Zwraca true gdy załadowano nowy model.
         *
         */
        virtual bool run (Util::Scene *scene) = 0;
};

} /* namespace Model */
#endif /* IMODELMANAGER_H_ */
