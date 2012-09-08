/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_TWEEN_MANAGER_H_
#define BAJKA_TWEEN_MANAGER_H_

#include <map>
#include "util/Exceptions.h"
#include "ITween.h"
#include "ease/IEquation.h"
#include "accessor/IAccessor.h"
#include <memory>
#include "AtomicTween.h"

namespace Tween {
class Pool;
class Timeline;
class MultiTween;
class SetTween;

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

        Manager ();
        virtual ~Manager ();

        void update (int deltaMs);

        // TODO tymczasowe
        void setTween (ITween *t) { tween = t; }

        void registerAccessor (unsigned int id, IAccessor *a);

        IEquation const *getEase (Ease e) const;
        IAccessor const *getAccessor (unsigned int id) const;

/*--------------------------------------------------------------------------*/

        static void init ();
        static void free ();
        static Manager *getMain ()
        {
                assertThrow (main, "Main tween manager is not created. Use Tween::init () first.");
                return main;
        }

/*--------------------------------------------------------------------------*/

        AtomicTween *newAtomicTween ();
        void freeAtomicTween (AtomicTween *);

        AtomicTween::Target *newTarget ();
        void freeTarget (AtomicTween::Target *);

        Timeline *newTimeline ();
        void freeTimeline (Timeline *);

        MultiTween *newMultiTween ();
        void freeMultiTween (MultiTween *);

        SetTween *newSetTween ();
        void freeSetTween (SetTween *);

private:

        typedef std::map <Ease, IEquation *> EquationMap;
        typedef std::map <unsigned int, IAccessor *> AccessorMap;

        static Manager *main;
        EquationMap equations;
        AccessorMap accessors;
        ITween *tween;
        std::auto_ptr <Pool> pool;
};

/**
 *
 */
extern void init ();

/**
 *
 */
extern void free ();

} /* namespace Tween */

#	endif /* MANAGER_H_ */
