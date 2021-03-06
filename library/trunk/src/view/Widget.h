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
#include "ReflectionMacros.h"
#include <map>
#include <string>

namespace View {

class Widget : public IView {
public:

        C__ (void)
        Widget () : visible (true), alpha (1) {}
        virtual ~Widget () {}

        virtual void preUpdate (Model::IModel *, Event::UpdateEvent *e);
        virtual void update (Model::IModel *, Event::UpdateEvent *e) {}
        virtual void postUpdate (Model::IModel *, Event::UpdateEvent *e);

        bool getVisible () const { return visible; }
        m_ (setVisible) void setVisible (bool v) { visible = v; }

        double getAlpha () const { return alpha; }
        m_ (setAlpha) void setAlpha (double d) { alpha = d; }

        m_ (setState) virtual void setState (int) {}
        virtual int getState () const { return 0; }

        virtual double getWidthHint () const { return 0; }
        virtual double getHeightHint () const { return 0; }

        static void defaultPreUpdate (Model::IModel *m);
        static void defaultPostUpdate (Model::IModel *m);

private:

        bool visible;
        double alpha;

        E_ (Widget)
};

/*##########################################################################*/

typedef std::map <std::string, Widget *> StringWidgetMap;
g_ (StringWidgetMap)

typedef std::vector <Widget *> WidgetVector;
g_ (WidgetVector)

} /* namespace View */

#	endif /* WIDGET_H_ */
