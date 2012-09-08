/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef AFFINEACCESSOR_H_
#define AFFINEACCESSOR_H_

#include "IAccessor.h"
#include "model/IModel.h"

namespace Tween {

/**
 *
 */
struct TranslateXAccessor : public IAccessor {
        ~TranslateXAccessor () {}
        double getValue (void *obj) const { return static_cast <Model::IModel *> (obj)->getTranslate ().x; }
        void setValue (void *obj, double value) const
        {
        	Model::IModel *m = static_cast <Model::IModel *> (obj);
        	Geometry::Point p = m->getTranslate ();
        	p.x = value;
        	m->setTranslate (p);
        }
};

unsigned int const X = 0;

/**
 *
 */
struct TranslateYAccessor : public IAccessor {
        ~TranslateYAccessor () {}
        double getValue (void *obj) const { return static_cast <Model::IModel *> (obj)->getTranslate ().y; }
        void setValue (void *obj, double value) const
        {
        	Model::IModel *m = static_cast <Model::IModel *> (obj);
        	Geometry::Point p = m->getTranslate ();
        	p.y = value;
        	m->setTranslate (p);
        }
};

unsigned int const Y = 1;

/**
 *
 */
struct ScaleAccessor : public IAccessor {
        ~ScaleAccessor () {}
        double getValue (void *obj) const { return static_cast <Model::IModel *> (obj)->getScale (); }
        void setValue (void *obj, double value) const { static_cast <Model::IModel *> (obj)->setScale (value); }
};

unsigned int const SCALE = 2;

/**
 *
 */
struct AngleAccessor : public IAccessor {
        ~AngleAccessor () {}
        double getValue (void *obj) const { return static_cast <Model::IModel *> (obj)->getAngle (); }
        void setValue (void *obj, double value) const { static_cast <Model::IModel *> (obj)->setAngle (value); }
};

unsigned int const ANGLE = 3;

} /* namespace Tween */

#	endif /* AFFINEACCESSOR_H_ */
