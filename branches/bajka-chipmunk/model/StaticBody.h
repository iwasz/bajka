/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_STATICBODY_H_
#define BAJKA_STATICBODY_H_

#include "Body.h"

namespace Model {

class StaticBody : public Body {
public:

        StaticBody (bool spcBdy = false);
        virtual ~StaticBody ();

        // To główne ze space.
        bool getSpaceBody () const { return spaceBody; }

private:

        bool spaceBody;

};

}

#	endif /* STATICBODY_H_ */
