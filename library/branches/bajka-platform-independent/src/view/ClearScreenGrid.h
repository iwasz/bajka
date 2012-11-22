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
#include "view/openGl/OpenGl.h"

namespace View {

/**
 * Czyści cały ekran. Czyli tak jakby całą możliwą przestrzeń (widoczną i niewidoczną)
 * przykryła płaszczyzna o jednolitym kolorze. Ustawić kolor siatki na przezroczysty aby
 * ukryć siatkę (rysowanie nie uruchamia się).
 */
class ClearScreenGrid : public Widget {
public:

        C__ (void)
        ClearScreenGrid ();
        virtual ~ClearScreenGrid ();

        void update (Model::IModel *, Event::UpdateEvent *e, View::GLContext *ctx);

private:

        View::Color P_ (color);
        View::Color P_ (gridColor);
        double p_ (density); // TODO to do konstruktora
        GLuint gridBuffer;
        GLuint axesBuffer;
        unsigned int gridVertsCount;

        E_ (ClearScreenGrid)
};

} /* namespace View */
#endif /* CLEARSCREEN_H_ */
