/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ParalaxModel.h"

namespace Model {

void ParalaxModel::setMove (const Geometry::Point &p)
{
        // TODO
        ShapelessModel::setMove (p);
        // A tu wpęti trzeba będzie zrobić jakąś korekcję.
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << p << std::endl;
}

}
