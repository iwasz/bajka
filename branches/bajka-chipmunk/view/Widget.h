/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_WIDGET_H_
#define BAJKA_WIDGET_H_

#include "IView.h"

namespace View {

class Widget : public IView {
public:

        Widget () : visible (true) {}
        virtual ~Widget () {}

        virtual void preUpdate (Model::IModel *);
        virtual void update (Model::IModel *) {}
        virtual void postUpdate (Model::IModel *);

        bool getVisible () const { return visible; }
        /*_m (setVisible) */void setVisible (bool v) { visible = v; }

        static void defaultPreUpdate (Model::IModel *m);
        static void defaultPostUpdate (Model::IModel *m);

private:

        bool visible;

};

} /* namespace View */

#	endif /* WIDGET_H_ */
