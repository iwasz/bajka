/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_IGROUP_H_
#define BAJKA_IGROUP_H_

#include <Object.h>
#include "IModel.h"

namespace Model {

/**
 *
 */
struct IGroup : public virtual Core::Object {

        virtual ~IGroup () {}

        virtual void screenToGroup (Geometry::Point *p) const = 0;
        virtual void groupToScreen (Geometry::Point *p) const = 0;

        virtual ModelVector &getChildren () = 0;
        virtual void setChildren (ModelVector const &) = 0;
        virtual void addChild (IModel *m) = 0;
        virtual ModelVector::iterator begin () = 0;
        virtual ModelVector::iterator end () = 0;

};

}

#	endif /* IMODEL_H_ */
