/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "GLContext.h"
#include <boost/numeric/ublas/matrix.hpp>

namespace View {
using namespace boost::numeric::ublas;

/****************************************************************************/

Geometry::AffineMatrix const &GLContext::pushMatrix (Geometry::AffineMatrix const &m)
{
        if (matrixStack.empty ()) {
                matrixStack.push_back (m);
                return matrixStack.back ();
        }

        Geometry::AffineMatrix const &top = matrixStack.back ();
        matrixStack.push_back (prod (top, m));
        return matrixStack.back ();
}

/****************************************************************************/

void GLContext::popMatrix ()
{
        matrixStack.pop_back ();
}

/****************************************************************************/

Geometry::AffineMatrix const &GLContext::getCurrentMatrix () const
{
        return matrixStack.back ();
}

} /* namespace Common */
