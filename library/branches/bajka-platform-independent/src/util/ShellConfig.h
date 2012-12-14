/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SHELLCONFIG_H_
#define BAJKA_SHELLCONFIG_H_

#include <string>

namespace Util {

/**
 * Config, raczej to co przyjdzie z linii polceceń.
 */
struct ShellConfig {

        ShellConfig () :
                fullScreen (false),
                viewportWidth (-1),
                viewportHeight (-1),
                showAABB (false),
                loopDelayMs (-1),
                definitionFile ("main.xml"),
                configFile ("config.xml") {}

        bool            fullScreen;
        int             viewportWidth;
        int             viewportHeight;
        bool            showAABB;
        int             loopDelayMs;
        std::string     definitionFile;
        std::string     configFile;
};

} /* namespace Util */

#endif /* SHELLCONFIG_H_ */
