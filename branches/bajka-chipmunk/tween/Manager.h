/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_TWEEN_MANAGER_H_
#define BAJKA_TWEEN_MANAGER_H_

#include "../util/Exceptions.h"

namespace Tween {

class Manager {
public:
        virtual ~Manager () {}

        void update (int )

/*--------------------------------------------------------------------------*/

        static void init () { main = new Manager; }
        static void free () { delete main; }
        static Manager *getMain ()
        {
                assertThrow (main, "Main tween manager is not created. Use Tween::init () first.");
                return main;
        }

private:

        static Manager *main;

};

} /* namespace Tween */

#	endif /* MANAGER_H_ */
