/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#if defined (USE_OPENGL) || defined (USE_OPENGLES)
#ifndef OPENGLCOMMONSERVICE_H_
#define OPENGLCOMMONSERVICE_H_

#include "draw/Color.h"

namespace View {

class OpenGlCommonService {
public:

        static void clear (View::Color const &c);

};

} /* namespace View */

#endif /* OPENGLCOMMONSERVICE_H_ */
#endif
