/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CLEARSCREEN_GRID_H_
#define CLEARSCREEN_GRID_H_

#include "util/ReflectionMacros.h"
#include "Widget.h"
#include "draw/Color.h"

namespace View {

/**
 * Czyści cały ekran. Czyli tak jakby całą możliwą przestrzeń (widoczną i niewidoczną)
 * przykryła płaszczyzna o jednolitym kolorze.
 */
class ClearScreenGrid : public Widget {
public:

        C__ (void)
        ClearScreenGrid () : density (20) {}
        virtual ~ClearScreenGrid () {}

        void update (Model::IModel *, Event::UpdateEvent *e);

private:

        View::Color P_ (color);
        View::Color P_ (gridColor);
        double p_ (density);

        E_ (ClearScreenGrid)
};

} /* namespace View */
#endif /* CLEARSCREEN_H_ */
