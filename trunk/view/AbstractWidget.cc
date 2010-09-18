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
//using boost::mem_fun;
//using Util::convertPtr;

namespace View {

// Dla mem_fn - wrzucić do tiliae/Pointer.h
// TODO dlaczego to kurwa nie działa, kiedy jest w Commons.h ?
template <class T>
T *get_pointer (Ptr <T> t)
{
        return t.get ();
}

void AbstractWidget::init ()
{
        for_each (begin (), end (), boost::mem_fn (&IWidget::init));
}

/****************************************************************************/

void AbstractWidget::preDraw ()
{
        glPushMatrix ();
}

/****************************************************************************/

void AbstractWidget::doTransform ()
{
        if (model) {
                glMultMatrixd (model->getMatrix ().data ().begin ());
        }
}

/****************************************************************************/

void AbstractWidget::doChildren ()
{
        for_each (begin (), end (), boost::mem_fn (&IWidget::draw));
}

/****************************************************************************/

void AbstractWidget::postDraw ()
{
        glPopMatrix ();
}

/****************************************************************************/

void AbstractWidget::draw ()
{
        // If render is set to false, we skip drawing this Widget.
        if (!visible) {
                return;
        }

        preDraw ();
        doTransform ();
        doDraw ();
        doChildren ();
        postDraw ();
}

}
