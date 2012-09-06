/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_CHIPMUNK
#ifndef BAJKA_SPACE_H_
#define BAJKA_SPACE_H_

#include "../util/Exceptions.h"
#include "../Group.h"

struct cpSpace;

namespace Model {

class Space : public Group {
public:

        C__ (void)
        b_ ("Group")

        Space ();
        virtual ~Space ();

        static cpSpace *getSpace ();

/*--------------------------------------------------------------------------*/

        // W środku rodzica.
        virtual Geometry::Point computeCenter () const { return Geometry::ZERO_POINT; }

/*--------------------------------------------------------------------------*/

        IModel *findContains (Geometry::Point const &p);

/*--------------------------------------------------------------------------*/

        Geometry::Point getGravity () const;
        m_ (setGravity) void setGravity (Geometry::Point const &g);

private:

        static cpSpace *space;

        E_ (Space)
};

} /* namespace Model */

#endif /* SPACE_H_ */
#endif
