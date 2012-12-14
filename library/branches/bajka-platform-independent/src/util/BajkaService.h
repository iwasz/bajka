/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKASERVICE_H_
#define BAJKASERVICE_H_

#include <string>

namespace Util {
class ShellConfig;
class Config;
class Scene;

/**
 * Do inicjowania i konfigurowania biblioteki bajka z zewnątrz, czyli z shella.
 */
class BajkaService {
public:

        BajkaService ();
        ~BajkaService ();

        /**
         * Nie kasować, kontener skasuje.
         */
        Util::Config *loadAndOverrideConfig (Util::ShellConfig const &cfg);

        /**
         * Skasować za pomocą delete.
         */
        Util::Scene *loadScene (std::string const &sceneFile);
        void init (Util::Config *config);
        void initProjectionMatrix (Util::Config *config);

private:

        Util::Config *loadConfig (std::string const &configFile);
        Util::Config *overrideConfig (Util::ShellConfig const &shellConfig, Util::Config *config);

private:

        struct Impl;
        Impl *impl;

};

} /* namespace Util */
#endif /* BAJKASERVICE_H_ */
