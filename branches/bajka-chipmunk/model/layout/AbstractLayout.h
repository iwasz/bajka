/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTLAYOUT_H_
#define ABSTRACTLAYOUT_H_

#include "../Box.h"

namespace Model {

/**
 * Metody wspólne dla wszystkich klas layoutowych.
 * \ingroup Layout
 */
class AbstractLayout : public Box {
public:
        __d
        _b ("Model::Box")

        AbstractLayout ();
        virtual ~AbstractLayout ();

        void setWidthPercent (double w) {}
        double getWidthPercent () const {}

        void setHeightPercent (double w) {}
        double getHeightPercent () const {}

        double getX1Percent () const {}
        void setX1Percent (double x) { }

        double getY1Percent () const {}
        void setY1Percent (double y) {}

        _e (AbstractLayout)
};

}

#	endif /* ABSTRACTLAYOUT_H_ */
