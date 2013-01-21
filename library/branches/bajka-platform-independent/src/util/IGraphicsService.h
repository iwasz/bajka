/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_INTERFACE_GRAPHICSSERVICE_H_
#define BAJKA_INTERFACE_GRAPHICSSERVICE_H_

namespace Util {
class Config;

/**
 *
 */
class IGraphicsService {
public:

        virtual ~IGraphicsService () {}

        virtual bool initDisplay (Util::Config *config) = 0;
        virtual void termDisplay () = 0;
        virtual void unbindSurfaceAndContext () = 0;

        /**
         * Zwraca true gdy powodzenie.
         */
        virtual bool saveScreenDimensionsInConfig (Util::Config *config) = 0;
        virtual void swapBuffers () = 0;

};

}

#endif /* GRAPHICSSERVICE_H_ */
