/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_VIEW_RECT_H_
#define BAJKA_VIEW_RECT_H_

#include "Widget.h"

namespace View {

/**
 * Rysuje prostokąt.
 * \ingroup View
 */
class Rectangle : public Widget {
public:

        virtual ~Rectangle () {}
        virtual void update (Model::IModel *model);
};

} /* namespace View */

#	endif /* CIRCLE_H_ */
