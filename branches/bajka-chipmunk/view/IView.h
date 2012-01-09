/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IVIEW_H_
#define IVIEW_H_

#include <Object.h>

namespace Model {
class IModel;
}

namespace View {

/**
 * Widok.
 */
struct IView : public Core::Object {

        virtual ~IView () {}

        virtual void preUpdate (Model::IModel *) = 0;
        virtual void update (Model::IModel *) = 0;
        virtual void postUpdate (Model::IModel *) = 0;

};

} /* namespace View */

#	endif /* IVIEW_H_ */
