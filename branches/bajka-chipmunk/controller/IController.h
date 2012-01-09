/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_ICONTROLLER_H_
#define BAJKA_ICONTROLLER_H_

#include <Object.h>

namespace Model {
class IModel;
}

namespace View {
class IView;
}

namespace Controller {

/**
 *
 */
struct IController : public Core::Object {

        virtual ~IController () {}

        virtual bool preUpdate (Model::IModel *m, View::IView *v) = 0;
        virtual bool update (Model::IModel *m, View::IView *v) = 0;
        virtual bool postUpdate (Model::IModel *m, View::IView *v) = 0;

};

} /* namespace Controller1 */

#	endif /* ICONTROLLER_H_ */
