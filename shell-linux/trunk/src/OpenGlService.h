/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef OPENGLSERVICE_H_
#define OPENGLSERVICE_H_

namespace Util {
class Config;
}

void initOpenGl (Util::Config *config);
void freeOpenGl ();
void mouseToDisplay (int x, int y, int windowWidth, int windowHeight, float *nx, float *ny);

#endif /* OPENGLSERVICE_H_ */
