/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_CHIPMUNK
#include <chipmunk.h>
#include "StaticBody.h"
#include "Space.h"

namespace Model {

StaticBody::StaticBody (bool spcBdy) : Body (0), spaceBody (spcBdy)
{
        if (spcBdy) {
                body = cpSpaceGetStaticBody (Space::getSpace ());
        }
        else {
                body = cpBodyNewStatic ();
                cpBodySetUserData (body, this);
        }
}

StaticBody::~StaticBody ()
{
        // skasuje się w Body::~Body
}

} /* namespace Model */

#endif
