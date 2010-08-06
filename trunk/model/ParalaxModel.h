/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef PARALAXMODEL_H_
#define PARALAXMODEL_H_

#include "AbstracModel.h"

namespace Model {

class ParalaxModel : public AbstracModel {
public:
        __c (void)
        _b ("AbstracModel")

        virtual ~ParalaxModel () {}
        virtual void setMove (const Geometry::Point &p);

private:

        // Tu lista doubli.
        _e (ParalaxModel)
};

}

#	endif /* PARALAXMODEL_H_ */
