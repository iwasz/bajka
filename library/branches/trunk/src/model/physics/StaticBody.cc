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
                cpSpace *space = Space::getSpace ();
                assertThrow (space, "StaticBody::StaticBody : !space");
                body = cpSpaceGetStaticBody (space);
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
