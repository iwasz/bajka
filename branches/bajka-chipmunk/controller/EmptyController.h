/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef EMPTYCONTROLLER_H_
#define EMPTYCONTROLLER_H_

#include "IController.h"

namespace Controller {

struct EmptyController : public IController {

        virtual ~EmptyController () {}

        virtual bool preUpdate (Model::IModel *m, View::IView *v) {}
        virtual bool update (Model::IModel *m, View::IView *v) {}
        virtual bool postUpdate (Model::IModel *m, View::IView *v) {}

};

} /* namespace Controller */

#	endif /* EMPTYCONTROLLER_H_ */
