/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <algorithm>
#include "StatefulWidget.h"

namespace View {
using namespace std;

void StatefulWidget::setWidgets (StringWidgetMap const &w)
{
        widgets = w;

        for (StringWidgetMap::iterator i = widgets.begin () ; i != widgets.end (); ++i) {
                AbstractWidget::addChild (i->second);
        }
}

/****************************************************************************/

void StatefulWidget::addWidget (Core::String const &key, Ptr <IWidget> widget)
{
        widgets[key] = widget;
        AbstractWidget::addChild (widget);
}

/****************************************************************************/

Ptr <IWidget> StatefulWidget::getWidget (Core::String const &key) const
{
        StringWidgetMap::const_iterator i = widgets.find (key);
        return (i == widgets.end ()) ? (Ptr <IWidget> ()) : (i->second);
}

/****************************************************************************/

void StatefulWidget::setCurrentWidget (Core::String const &key)
{
        for (StringWidgetMap::iterator i = widgets.begin () ; i != widgets.end (); ++i) {
                if (i->first == key) {
                        i->second->setVisible (true);
                }
                else {
                        i->second->setVisible (false);
                }
        }
}

} // namespace
