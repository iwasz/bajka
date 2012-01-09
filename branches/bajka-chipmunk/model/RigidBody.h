/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_RIGIDBODY_H_
#define BAJKA_RIGIDBODY_H_

#include "Body.h"

namespace Model {

class RigidBody : public Body {
public:
        virtual ~RigidBody () {}
};

}

#	endif /* RIGIDBODY_H_ */
