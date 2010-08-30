/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef STATEFULWIDGET_H_
#define STATEFULWIDGET_H_

#include "AbstractWidget.h"

namespace View {

/**
 * Widget zawierający kilka innych widgetów i wyświetlający tylko jeden z nich. Zawierane
 * widgety są indeksowane poprzez napisy. Każdy ma przyporzadkowany klucz i można wybrać,
 * który ma być aktualnie pokazywany.
 * \ingroup View
 */
class StatefulWidget : public AbstractWidget {
public:
        __c (void)
        _b ("AbstractWidget")

        virtual ~StatefulWidget () {}

        virtual void init ();

        _m (getWidgets) StringWidgetMap const &getWidgets () const { return widgets; }
        _m (setWidgets) void setWidgets (StringWidgetMap const &w) { widgets = w; }

        void addWidget (Core::String const &key, Ptr <IWidget> widget) { widgets[key] = widget; }
        Ptr <IWidget> getWidget (Core::String const &key) const;

        bool hasWidget (Core::String const &key) const { return widgets.find (key) != widgets.end (); }
        _m (setCurrentWidget) void setCurrentWidget (Core::String const &key);

        virtual void draw ();
        virtual void preDraw ();
        virtual void postDraw ();
        virtual void doDraw () {}

private:

        StringWidgetMap widgets;

        _e (StatefulWidget)
};

} // namespace

#	endif /* STATEFULWIDGET_H_ */
