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
#include "IMultiTween.h"

namespace Tween {
class Pool;
class Timeline;
class MultiTween;
class SetTween;
class TweeningProperty;
class ITargetable;

/**
 *
 */
class Manager : public virtual IMultiTween {
public:

        Manager ();
        virtual ~Manager ();

        void update (int deltaMs);

        IMultiTween *add (ITween *tween);
        void remove (ITween *tween);
        void remove (void const *target, bool onlyActive);
        void remove (void const *target, TweeningProperty *property, bool onlyActive = false);
        void killAll () { remove (NULL, false); }

        void overwrite (ITargetable const *tween);

        IEquation const *getEase (Ease e) const;
        IEquation const *getEase (std::string const &s) const;

        void registerAccessor (unsigned int id, std::string const &s, IAccessor *a);
        IAccessor const *getAccessor (unsigned int id) const;
        IAccessor const *getAccessor (std::string const &s) const;

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

        void free (ITween *t);

/*--------------------------------------------------------------------------*/

        static void init ();
        static void destroy ();
        static Manager *getMain ()
        {
                assertThrow (main, "Main tween manager is not created. Use Tween::init () first.");
                return main;
        }

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
        TweenList tweens;
        std::auto_ptr <Pool> pool;
};

/**
 *
 */
extern void init ();

/**
 *
 */
extern void destroy ();

} /* namespace Tween */

#	endif /* MANAGER_H_ */
