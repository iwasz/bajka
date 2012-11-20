/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_LOOPIMAGE_H_
#define BAJKA_LOOPIMAGE_H_

#include "Image.h"
#include "tween/accessor/IAccessor.h"

namespace View {

/**
 * Obrazek, który pokazuje bitmapę w postaci kafelków ułozonych obok siebie.
 * Można podać offset, dzięki czemu powstaje opcja animacji.
 */
class LoopImage : public Image {
public:
        C__ (void)
        b_ ("Image")

        LoopImage () : offsetX (0), offsetY (0) {}
        virtual ~LoopImage () {}
        virtual void update (Model::IModel *model, Event::UpdateEvent *e, View::GLContext *ctx);

                        int getOffsetX () const { return offsetX; }
        m_ (setOffsetX) void setOffsetX (int o) { offsetX = o; }

                        int getOffsetY () const { return offsetY; }
        m_ (setOffsetY) void setOffsetY (int o) { offsetY = o; }

protected:

        void drawTile (double x, double y);

private:

        int offsetX;
        int offsetY;

        E_ (LoopImage)
};

} /* namespace View */

namespace Tween {

/**
 * Accessor dla tweenów.
 * Uawga! Zupełnie nie typesafe - uzywać ostrożnie!
 */
struct LoopImageXAccessor : public IAccessor {
        ~LoopImageXAccessor () {}
        double getValue (void *obj) const { return static_cast <View::LoopImage *> (obj)->getOffsetX (); }
        void setValue (void *obj, double value) const { static_cast <View::LoopImage *> (obj)->setOffsetX (value); }
};

unsigned int const LOOP_X = 4;

/**
 * Accessor dla tweenów.
 * Uawga! Zupełnie nie typesafe - uzywać ostrożnie!
 */
struct LoopImageYAccessor : public IAccessor {
        ~LoopImageYAccessor () {}
        double getValue (void *obj) const { return static_cast <View::LoopImage *> (obj)->getOffsetY (); }
        void setValue (void *obj, double value) const { static_cast <View::LoopImage *> (obj)->setOffsetY (value); }
};

unsigned int const LOOP_Y = 5;

} /* namespace Tween */

#endif /* LOOPIMAGE_H_ */
