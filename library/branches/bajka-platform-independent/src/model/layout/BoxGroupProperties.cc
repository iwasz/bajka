/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BoxGroupProperties.h"
#include "model/IModel.h"
#include "BoxGroup.h"
#include "geometry/Box.h"
#include "geometry/Point.h"

namespace Model {
namespace G = Geometry;

G::Point BoxGroupProperties::calculateTranslation (IModel const *m, Geometry::Point const &currentTranslate, double aabbW, double aabbH) const
{
        BoxGroup const *parGroup = BoxGroup::getParGroup (m);

        if (!parGroup) {
                return currentTranslate;
        }

        // Przypadek domyślny - nie pobieramy aabb
        if (align == (TOP | RIGHT)) {
                return G::makePoint (parGroup->getWidth() * translate.x / 100.0, parGroup->getHeight () * translate.y / 100.0);
        }
        else {
                G::Point ct = G::makePoint (parGroup->getWidth() * translate.x / 100.0, parGroup->getHeight () * translate.y / 100.0);

                if (align & HCENTER) {
                        ct.x -= aabbW / 2.0;
                }
                else if (align & LEFT) {
                        ct.x -= aabbW;
                }

                if (align & VCENTER) {
                        ct.y -= aabbH / 2.0;
                }
                else if (align & BOTTOM) {
                        ct.y -= aabbH;
                }

                return ct;
        }
}

} /* namespace Model */
