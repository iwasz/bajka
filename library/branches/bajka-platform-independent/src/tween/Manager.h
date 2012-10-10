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
class TweeningProperty;

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

        void registerAccessor (unsigned int id, std::string const &s, IAccessor *a);

        IEquation const *getEase (Ease e) const;
        IEquation const *getEase (std::string const &s) const;

        IAccessor const *getAccessor (unsigned int id) const;
        IAccessor const *getAccessor (std::string const &s) const;

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

        TweeningProperty *newProperty ();
        void freeProperty (TweeningProperty *);

        Timeline *newTimeline ();
        void freeTimeline (Timeline *);

        MultiTween *newMultiTween ();
        void freeMultiTween (MultiTween *);

        SetTween *newSetTween ();
        void freeSetTween (SetTween *);

private:

        typedef std::map <Ease, IEquation *> EquationMap;
        typedef std::map <std::string, IEquation *> EquationMapStr;

        typedef std::map <unsigned int, IAccessor *> AccessorMap;
        typedef std::map <std::string, IAccessor *> AccessorMapStr;

        static Manager *main;
        EquationMap equations;
        EquationMapStr equationsStr;
        AccessorMap accessors;
        AccessorMapStr accessorsStr;
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
