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
#include "ITween.h"

namespace Tween {

/**
 * - Overwrite : co ma się dzieć, kiedy dodamy 2 tweeny do tego samego obiektu na ten
 * sam czas.
 * a) Drugi tween ma być ingnorowany.
 * b) Pierwszy jest anulowany a wykonumemy drugi natychmiast.
 * c) Drugi ustawia się w kolejce i czeka aż tenpierwszy skończy. (?) to dubluje funkcjonalność timeline.
 * http://www.greensock.com/overwritemanager/ - ten ma mnóstwo opcji i nie wiem które są przydatne.
 */
class Manager {
public:

        Manager () : tween (NULL) {}
        virtual ~Manager () {}

        void update (int deltaMs);

        // TODO tymczasowe
        void setTween (ITween *t) { tween = t; }

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

        ITween *tween;

};

} /* namespace Tween */

#	endif /* MANAGER_H_ */
