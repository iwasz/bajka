/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Config.h"

namespace Util {

/****************************************************************************/

Config::Config () :
                fullScreen (false),
                autoViewport (false),
                viewportWidth (640),
                viewportHeight (480),
                autoProjection (false),
                projectionWidth (0),
                projectionHeight (0),
                showAABB (false),
                showSystemCursor (true),
                loopDelayMs (17)
{
}


} /* namespace Util */
