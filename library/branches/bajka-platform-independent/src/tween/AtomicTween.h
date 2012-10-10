/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ATOMICTWEEN_H_
#define ATOMICTWEEN_H_

#include <cstddef>
#include <memory>
#include <iostream>
#include "ease/IEquation.h"
#include "accessor/IAccessor.h"
#include "AbstractTween.h"
#include "TweeningProperty.h"
#include "ITargetable.h"

namespace Tween {

/**
 * Tween dla pojedynczej wartości (na przykład współrzędnej X w punkcie).
 */
class AtomicTween : public AbstractTween, public ITargetable {
public:

        enum Type { TO, FROM };

        AtomicTween () : AbstractTween (), equation (NULL), durationMs (0), object (NULL), type (TO), overwrite (NONE) {}
        virtual ~AtomicTween () {}

        void *getTarget () { return object; }
        void setTarget (void *o) { object = o; }

        AtomicTween *abs (unsigned int property, double value);
        AtomicTween *abs (std::string const &property, double value);
        AtomicTween *rel (unsigned int property, double value);
        AtomicTween *rel (std::string const &property, double value);

        Overwrite getOverwrite () const { return overwrite; }
        void setOverwrite (Overwrite o) { overwrite = o; }

        void addProperty (TweeningProperty *p) { properties.push_back (p); }

        friend AtomicTween *to (void *targetObject, unsigned int durationMs, Ease ease);
        friend AtomicTween *from (void *targetObject, unsigned int durationMs, Ease ease);
        friend class ParserImpl;

        int getDurationMs () const { return durationMs; }
        void setDurationMs (int ms) { durationMs = ms; }

protected:

        AtomicTween *property (IAccessor const *accessor, double value, bool abs);

        // Uruchamia się jeden raz na poczatku działania tweena (lub po repeat).
        void initEntry (bool reverse);
        void initExit (bool reverse);
        void delayEntry (bool reverse);
        void delayExit (bool reverse);
        void runEntry (bool reverse);
        void runExit (bool reverse);
        void finishedEntry (bool reverse);
        void finishedExit (bool reverse);

        void updateRun (int deltaMs, bool direction);
        bool checkEnd (bool direction);

public:

        IEquation const *equation;
        int durationMs;
        void *object;
        TweeningPropertyList properties;
        Type type;
        Overwrite overwrite;
};

/**
 *
 * @param targetObject
 * @param durationMs
 * @param ease
 * @return
 */
extern AtomicTween *to (void *targetObject, unsigned int durationMs, Ease ease = LINEAR_INOUT);

extern AtomicTween *from (void *targetObject, unsigned int durationMs, Ease ease = LINEAR_INOUT);

}

#	endif /* ATOMICTWEEN_H_ */
