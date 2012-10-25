/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef GLESWIDGET_H_
#define GLESWIDGET_H_

#include <view/Primitive.h>

class GLESWidget : public View::Primitive {
public:
        C__ (void)
        b_ ("Primitive")

        virtual ~GLESWidget () {}
        m_ (init) void init ();
        void update (Model::IModel *model, Event::UpdateEvent *e);

        E_ (GLESWidget)

};

#endif /* GLESWIDGET_H_ */
