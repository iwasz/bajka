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
        virtual ~StaticBody ();
};

}

#	endif /* STATICBODY_H_ */
