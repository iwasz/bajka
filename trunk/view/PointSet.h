/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 26, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef POINTSET_H_
#define POINTSET_H_

#include "AbstractWidget.h"

namespace Model {
class IModel;
class PointSet;
}

namespace View {

/**
 * Set of points on the screen.
 */
class PointSet : public AbstractWidget {
public:

        virtual ~PointSet () {}
        virtual void init (Ptr <Model::IModel> model);
        virtual void doDraw ();

private:

        Ptr <Model::PointSet> model;

};

}

#	endif /* POINTSET_H_ */
