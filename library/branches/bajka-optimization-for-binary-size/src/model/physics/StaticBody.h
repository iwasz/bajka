/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_CHIPMUNK
#ifndef BAJKA_STATICBODY_H_
#define BAJKA_STATICBODY_H_

#include "Body.h"

namespace Model {

class StaticBody : public Body {
public:

        C__ (bool)
        b_ ("Body")

        StaticBody (bool spcBdy = false);
        virtual ~StaticBody ();

        // To główne ze space.
        bool getSpaceBody () const { return spaceBody; }

private:

        bool spaceBody;

        E_ (StaticBody)
};

}

#endif /* STATICBODY_H_ */
#endif
