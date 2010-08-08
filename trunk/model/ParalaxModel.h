/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef PARALAXMODEL_H_
#define PARALAXMODEL_H_

#include <Reflection.h>
#include "ShapelessModel.h"
#include "Commons.h"
#include "geometry/Point.h"

namespace Model {

class ParalaxModel : public ShapelessModel {
public:
        __c (void)
        _b ("AbstracModel")

        virtual ~ParalaxModel () {}
        virtual void setMove (const Geometry::Point &p);

        const Util::DoubleVector &getDepths () const { return depths; }
        void setDepths (const Util::DoubleVector &depths) { this->depths = depths; }

private:

        Util::DoubleVector depths;

        _e (ParalaxModel)
};

}

#	endif /* PARALAXMODEL_H_ */
