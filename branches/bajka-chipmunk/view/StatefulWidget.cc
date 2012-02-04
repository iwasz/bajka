/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <algorithm>
#include "StatefulWidget.h"
#include "../util/Exceptions.h"

namespace View {
using namespace std;

void StatefulWidget::update (Model::IModel *m)
{
        if (current) {
                current->update (m);
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
