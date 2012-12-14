/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTMODELMANAGER_H_
#define ABSTRACTMODELMANAGER_H_

#include "IModelManager.h"

namespace Model {

class AbstractModelManager : public IModelManager {
public:

        virtual ~AbstractModelManager () {}

        /**
         * Derived classes can use this.
         */
        void callOnManagerUnloadModel (Util::Scene *scene);
        void callOnManagerLoadModel (Util::Scene *scene);

};

} /* namespace Model */
#endif /* ABSTRACTMODELMANAGER_H_ */
