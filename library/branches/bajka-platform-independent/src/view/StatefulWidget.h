/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef STATEFULWIDGET_H_
#define STATEFULWIDGET_H_

#include "Widget.h"
#include "util/Exceptions.h"

namespace View {

/**
 * Widget zawierający kilka innych widgetów i wyświetlający tylko jeden z nich. Zawierane
 * widgety są indeksowane poprzez napisy. Każdy ma przyporzadkowany klucz i można wybrać,
 * który ma być aktualnie pokazywany.
 * TODO to powinna być klasa abstrakcyjna, a z tą listą widgetów konkretna. A co by było
 * gdybym chciał zrobić podświetlany prostokąt (wystarczy zmieinć kolor, a nie podmieniać
 * całe widgety). Zastanowić się. Patrz CustomRect. IMHO : nic nie zaszkodzi jeśli to będzie
 * klasa abstrakcyjna + kokretna.
 * \ingroup View
 */
class StatefulWidget : public Widget {
public:
        C__ (void)
        b_ ("Widget")

        StatefulWidget () : current (NULL), state (0) {}
        virtual ~StatefulWidget () {}

/*--------------------------------------------------------------------------*/

        virtual void update (Model::IModel *m, Event::UpdateEvent *e);

/*--------------------------------------------------------------------------*/

        /// \name Settery/gettery od widgetów
        //\{

        m_ (getWidgets) WidgetVector *getWidgets () { return &widgets; }
        m_ (setWidgets) void setWidgets (WidgetVector const &w) { widgets = w; }

        void addWidget (Widget *widget) { widgets.push_back (widget); }
        Widget *getWidget (int i) { assertThrow (widgets.size () -1 >= (unsigned)(i), "StatefulWidget::getWidget : No such widget"); return widgets[i]; }
        void setState (int s);

        double getWidthHint () const;
        double getHeightHint () const;

        //\}current

private:

        WidgetVector widgets;
        Widget *current;
        int state;

        E_ (StatefulWidget)
};

} // namespace

#	endif /* STATEFULWIDGET_H_ */
