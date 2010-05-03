///****************************************************************************
// *                                                                          *
// *  Author & Copyright (c) :  Lukasz Iwaszkiewicz                           *
// *  ~~~~~~~~~~~~~~~~~~~~~~~~  lukasz.iwaszkiewicz@gmail.com                 *
// *                                                                          *
// *  Date :                    Nov 4, 2009                                   *
// *  ~~~~~~                                                                  *
// *                                                                          *
// *      This program is free software;  you can redistribute it and / or    *
// *      modify it under the terms of the GNU General Public License. See    *
// *      COPYING file for details.                                           *
// *                                                                          *
// ****************************************************************************/
//
//#	ifndef OPENGLHELPER_H_
//#	define OPENGLHELPER_H_
//
//#include <vector>
//#include "geomx.h"
//
//struct IDisplay {
//
//        virtual ~IDisplay () {}
//
//        virtual void init (int argc, char **argv) = 0;
//
//        /**
//         * mBuf Nie zawiera informacji o ilości punktów, stąd dodatkowy parametr.
//         */
//        virtual void drawParticles (const std::vector<GeomBuf> &mBuf, int NumPoints) = 0;
//
//};
//
///**
// * To będzie głupawa klasa, która hermetyzuje operacje na openGLu
// */
//class OpenGLDisplay : public IDisplay {
//public:
//
//        OpenGLDisplay () : window_width (1024), window_height (768) {}
//        virtual ~OpenGLDisplay () {}
//
//        virtual void init (int argc, char **argv);
//        virtual void drawParticles (const std::vector<GeomBuf> &mBuf, int NumPoints);
//
//private:
//
//        float window_width;
//        float window_height;
//
//};
//
//#	endif /* OPENGLHELPER_H_ */
