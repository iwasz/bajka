/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKASERVICE_H_
#define BAJKASERVICE_H_

namespace Common {
class DataSource;
}

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
        Util::Config *loadAndOverrideConfig (Common::DataSource *dataDource, Util::ShellConfig const &cfg);

        /**
         * Skasować za pomocą delete.
         */
        Util::Scene *loadScene (Common::DataSource *ds, Util::ShellConfig const &cfg);
        void init (Util::Config *config);
        void initProjectionMatrix (Util::Config *config);

private:

        Util::Config *loadConfig (Common::DataSource *dataDource, Util::ShellConfig const &cfg);
        Util::Config *overrideConfig (Util::ShellConfig const &cfg, Util::Config *cfg2);

private:

        struct Impl;
        Impl *impl;

};

} /* namespace Util */
#endif /* BAJKASERVICE_H_ */
