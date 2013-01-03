/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#if 0
#ifndef GLESWIDGET_H_
#define GLESWIDGET_H_

#include <view/Primitive.h>

class GLESWidget : public View::Primitive {
public:
        C__ (void)
        b_ ("Primitive")

        GLESWidget ();
        virtual ~GLESWidget ();

        m_ (init) void init ();
        void update (Model::IModel *model, Event::UpdateEvent *e);
private:

        class Impl;
        Impl *impl;
        std::string P_ (vertex);
        std::string P_ (fragment);
        E_ (GLESWidget)

};

#endif /* GLESWIDGET_H_ */
#endif
