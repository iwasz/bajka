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
#include "Commons.h"
#include "geometry/Point.h"
#include "AbstractModel.h"

namespace Model {

class ParalaxModel : public AbstractModel {
public:
        __c (void)
        _b ("AbstractModel")

        virtual ~ParalaxModel () {}
        virtual void setMove (const Geometry::Point &p);

        const Util::DoubleVector &getDepths () const { return depths; }
        _m (setDepths) void setDepths (const Util::DoubleVector &depths) { this->depths = depths; }

private:

        Util::DoubleVector depths;

        _e (ParalaxModel)
};

}

#	endif /* PARALAXMODEL_H_ */
