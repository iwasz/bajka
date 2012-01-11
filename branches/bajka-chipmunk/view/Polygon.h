/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_VIEW_POLYGON_H_
#define BAJKA_VIEW_POLYGON_H_

#include "Widget.h"

namespace View {

class Polygon : public Widget {
public:
        virtual ~Polygon () {}
        virtual void update (Model::IModel *model);
};

} // namespace

#	endif /* POLYGON_H_ */
