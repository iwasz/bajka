/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL_opengl.h>
#include <algorithm>
#include <boost/mem_fn.hpp>

#include "AbstractWidget.h"
#include "IModel.h"
#include "Commons.h"

using std::for_each;

namespace View {

void AbstractWidget::init ()
{
        for_each (begin (), end (), boost::mem_fn (&IView::init));
}

/****************************************************************************/

void AbstractWidget::preDraw ()
{
        if (!visible) {
                return;
        }

        glPushMatrix ();

#if 1
        if (model) {
                glMultMatrixd (model->getMatrix ().data ().begin ());
        }
#endif
}

/****************************************************************************/

void AbstractWidget::postDraw ()
{
        if (!visible) {
                return;
        }

        if (ownsChildren ()) {
                for_each (begin (), end (), boost::mem_fn (&IWidget::draw));
        }

        glPopMatrix ();
}

/****************************************************************************/

void AbstractWidget::draw ()
{
        // If render is set to false, we skip drawing this Widget.
        if (!visible) {
                return;
        }

        doDraw ();

        if (model) {
                glTranslated (model->getOrigin ().getX (), model->getOrigin ().getY (), 0.0);
        }
}

}
