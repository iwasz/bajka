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

void StatefulWidget::init ()
{
//        Tak nie, bo przecież to mapa. \todo Ale jak to zrobić algorytmem?
//        std::for_each (widgets.begin (), widgets.end (), mem_fun (&IWidget::init));

        for (StringWidgetMap::iterator i = widgets.begin () ; i != widgets.end (); ++i) {
                i->second->init ();
        }
}

/****************************************************************************/

void StatefulWidget::setWidgets (StringWidgetMap const &w)
{
        widgets = w;
}

/****************************************************************************/

void StatefulWidget::addWidget (Core::String const &key, Ptr <IWidget> widget)
{
        widgets[key] = widget;
}

/****************************************************************************/

void StatefulWidget::draw ()
{
        for (StringWidgetMap::iterator i = widgets.begin () ; i != widgets.end (); ++i) {
                i->second->draw ();
        }
}

void StatefulWidget::preDraw ()
{
        for (StringWidgetMap::iterator i = widgets.begin () ; i != widgets.end (); ++i) {
                i->second->preDraw ();
        }
}

void StatefulWidget::postDraw ()
{
        for (StringWidgetMap::iterator i = widgets.begin () ; i != widgets.end (); ++i) {
                i->second->postDraw ();
        }
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
