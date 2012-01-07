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
 * TODO to powinna być klasa abstrakcyjna, a z tą listą widgetów konkretna. A co by było
 * gdybym chciał zrobić podświetlany prostokąt (wystarczy zmieinć kolor, a nie podmieniać
 * całe widgety). Zastanowić się. Patrz CustomRect. IMHO : nic nie zaszkodzi jeśli to będzie
 * klasa abstrakcyjna + kokretna.
 * \ingroup View
 */
class StatefulWidget : public AbstractWidget {
public:
        __c (void)
        _b ("AbstractWidget")

        virtual ~StatefulWidget () {}

/*--------------------------------------------------------------------------*/

        virtual void doDraw () {}

/*--------------------------------------------------------------------------*/

        /// \name Settery/gettery od widgetów
        //\{

        _m (getWidgets) StringWidgetMap const &getWidgets () const { return widgets; }
        _m (setWidgets) void setWidgets (StringWidgetMap const &w);

        void addWidget (Core::String const &key, Ptr <IWidget> widget);
        Ptr <IWidget> getWidget (Core::String const &key) const;
        bool hasWidget (Core::String const &key) const { return widgets.find (key) != widgets.end (); }
        _m (setCurrentWidget) void setCurrentWidget (Core::String const &key);

        //\}

private:

        StringWidgetMap widgets;

        _e (StatefulWidget)
};

} // namespace

#	endif /* STATEFULWIDGET_H_ */
