/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 26, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef GLUTIL_H_
#define GLUTIL_H_

#include "Point.h"
#include "Color.h"

namespace OpenGL {

struct GLUtil {

        static void init ();
        static void drawPoint (const Model::Point &point, const Model::Color &color);

private:

        static Model::PointList pointCircle;

};

}

#	endif /* GLUTIL_H_ */
