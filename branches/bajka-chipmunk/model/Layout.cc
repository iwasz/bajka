/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Layout.h"
#include "IModel.h"
#include "BoxGroup.h"
#include "../geometry/Box.h"
#include "../geometry/Point.h"

namespace Model {
namespace G = Geometry;

G::Point Layout::calculateTranslation (IModel const *m) const
{
        BoxGroup const *parGroup = BoxGroup::getParGroup (m);

        if (!parGroup) {
                return m->getTranslate ();
        }

        // Przypadek domyślny - nie pobieramy aabb
        if (align == (TOP | RIGHT)) {
                return G::Point (parGroup->getWidth() * translateRel.x / 100.0, parGroup->getHeight () * translateRel.y / 100.0);
        }
        else {
                G::Box aabb = m->getBoundingBox ();
                G::Point ct = G::Point (parGroup->getWidth() * translateRel.x / 100.0, parGroup->getHeight () * translateRel.y / 100.0);

                if (align & HCENTER) {
                        ct.x -= aabb.getWidth () / 2.0;
                }
                else if (align & LEFT) {
                        ct.x -= aabb.getWidth ();
                }

                if (align & VCENTER) {
                        ct.y -= aabb.getHeight () / 2.0;
                }
                else if (align & BOTTOM) {
                        ct.y -= aabb.getHeight ();
                }

                return ct;
        }
}

} /* namespace Model */
