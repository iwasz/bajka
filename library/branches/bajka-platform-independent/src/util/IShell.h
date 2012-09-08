/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_ISHELL_H_
#define BAJKA_ISHELL_H_

#include <string>

namespace Model {
class IModel;
}

namespace Util {
class Config;

struct ShellConfig {

        ShellConfig () :
                fullScreen (false),
                resX (-1),
                resY (-1),
                showAABB (false),
                loopDelayMs (-1) {}

        bool             fullScreen;
        int             resX;
        int             resY;
        bool             showAABB;
        int             loopDelayMs;
        std::string     definitionFile;
};

class IShell {
public:
        virtual ~IShell() {}

        virtual int run (Util::ShellConfig const &cfg) = 0;
        virtual void quit () = 0;

        /**
         * Powoduje zawieszenie wykonywania aktualnej iteracji i rozpoczęcie następnej.
         * Wszystkie czekające eventy zostają odrzucone etc.
         */
        virtual void dropIteration () = 0;
        virtual bool getDropIteration () const = 0;

        virtual void setModel (Model::IModel *model) = 0;
        virtual Util::Config *getConfig () = 0;
};

} /* namespace Util */
#endif /* ISHELL_H_ */
