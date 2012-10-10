/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_TWEEN_ITARGETABLE_H_
#define BAJKA_TWEEN_ITARGETABLE_H_

namespace Tween {

/**
 *
 */
class ITargetable {
public:
        virtual ~ITargetable () {}

        virtual void *getTarget () = 0;
        virtual void setTarget (void *) = 0;

        virtual ITween *abs (unsigned int property, double value) = 0;
        virtual ITween *abs (std::string const &property, double value) = 0;
        virtual ITween *rel (unsigned int property, double value) = 0;
        virtual ITween *rel (std::string const &property, double value) = 0;

        enum Overwrite { NONE, ALL_IMMEDIATE, AUTO, CONCURRENT, ALL_ONSTART };

        virtual Overwrite getOverwrite () const = 0;
        virtual void setOverwrite (Overwrite o) = 0;

        virtual void addProperty (TweeningProperty *p) = 0;
};

} /* namespace Tween */
#endif /* ITARGETABLE_H_ */
