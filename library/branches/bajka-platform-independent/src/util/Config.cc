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
                viewportWidth (640),
                viewportHeight (480),
                showAABB (false),
                showSystemCursor (true),
                loopDelayMs (17),
                model (NULL)
{
}


} /* namespace Util */
