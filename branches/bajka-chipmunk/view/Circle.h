/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_VIEW_CIRCLE_H_
#define BAJKA_VIEW_CIRCLE_H_

#include "Widget.h"

namespace View {

/**
 * Rysuje prostokąt.
 * \ingroup View
 */
class Circle : public Widget {
public:

        virtual ~Circle () {}
        virtual void update (Model::IModel *model);
};

} /* namespace View */

#	endif /* CIRCLE_H_ */
