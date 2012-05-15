/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#if USE_OPENGL
#ifndef OPENGLSERVICE_H_
#define OPENGLSERVICE_H_

namespace View {

class OpenGlService {
public:

        static void init (int resX, int resY);
        static void free ();
        static void mouseToDisplay (int x, int y, int windowWidth, int windowHeight, float *nx, float *ny);

};

} /* namespace View */

#endif /* OPENGLSERVICE_H_ */
#endif
