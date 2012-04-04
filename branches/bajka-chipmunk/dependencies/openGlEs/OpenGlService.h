/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#if USE_OPENGLES
#ifndef ES_OPENGLSERVICE_H_
#define ES_OPENGLSERVICE_H_

namespace View {

class OpenGlService {
public:

        static void init (int, int);
        static void free ();

};

} /* namespace View */

#endif /* OPENGLSERVICE_H_ */
#endif

