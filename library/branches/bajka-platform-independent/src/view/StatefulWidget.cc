/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <algorithm>
#include "StatefulWidget.h"
#include "util/Exceptions.h"

namespace View {
using namespace std;

double StatefulWidget::getWidthHint () const
{
        if (widgets.empty ()) {
                return 0;
        }

        return widgets.front ()->getWidthHint ();
}

/****************************************************************************/

double StatefulWidget::getHeightHint () const
{
        if (widgets.empty ()) {
                return 0;
        }

        return widgets.front ()->getHeightHint ();
}

/****************************************************************************/

void StatefulWidget::update (Model::IModel *m, Event::UpdateEvent *e)
{
        if (current) {
                current->update (m, e);
        }
}

/****************************************************************************/

void StatefulWidget::setState (int i)
{
        current = getWidget (i);
        state = i;
        assertThrow (current, "StatefulWidget::setCurrent : no such widget : " + boost::lexical_cast <std::string> (i) + ". Number of widgets : " + boost::lexical_cast <std::string> (widgets.size ()));
}

} // namespace
