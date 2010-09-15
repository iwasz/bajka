/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

// TODO usunąć jakoś
#include  "IWidget.h"
// TODO usunąć jakoś
#include  "IController.h"
#include "ParalaxModel.h"

namespace Model {

void ParalaxModel::setMove (const Geometry::Point &p)
{
        // Siebie w ogóle nie przesuwa.
        //AbstractModel::setMove (p);

        Util::DoubleVector::const_iterator j = depths.begin ();

        for (iterator i = begin (); i != end (); ++i, ++j) {
//                double factor = 1
                (*i)->setMove (p * *j);
        }

}

}
