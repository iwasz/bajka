/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CLEARSCREEN_H_
#define CLEARSCREEN_H_

#include "util/ReflectionMacros.h"
#include "Widget.h"
#include "draw/Color.h"

namespace View {

/**
 * Czyści cały ekran. Czyli tak jakby całą możliwą przestrzeń (widoczną i niewidoczną)
 * przykryła płaszczyzna o jednolitym kolorze.
 */
class ClearScreen : public Widget {
public:

        C__ (void)

        virtual ~ClearScreen () {}
        void update (Model::IModel *, Event::UpdateEvent *e, View::GLContext *ctx);

private:

        View::Color P_ (color);

        E_ (ClearScreen)
};

} /* namespace View */
#endif /* CLEARSCREEN_H_ */
