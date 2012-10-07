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

namespace {
inline Model::IModel *castVoid (void *obj)
{
        return dynamic_cast <Model::IModel *> (static_cast <Core::Object *> (obj));
}
}

/**
 *
 */
struct TranslateXAccessor : public IAccessor {
        ~TranslateXAccessor () {}
        double getValue (void *obj) const { return castVoid (obj)->getTranslate ().x; }
        void setValue (void *obj, double value) const
        {
        	Model::IModel *m = castVoid (obj);
        	Geometry::Point p = m->getTranslate ();
        	p.x = value;
        	m->setTranslate (p);
        	std::cerr << typeid (m).name () << ", m : "<< m << ", translate : " << p << std::endl;
        }
};

unsigned int const X = 0;

/**
 *
 */
struct TranslateYAccessor : public IAccessor {
        ~TranslateYAccessor () {}
        double getValue (void *obj) const { return castVoid (obj)->getTranslate ().y; }
        void setValue (void *obj, double value) const
        {
        	Model::IModel *m = castVoid (obj);
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
        double getValue (void *obj) const { return castVoid (obj)->getScale (); }
        void setValue (void *obj, double value) const { castVoid (obj)->setScale (value); }
};

unsigned int const SCALE = 2;

/**
 *
 */
struct AngleAccessor : public IAccessor {
        ~AngleAccessor () {}
        double getValue (void *obj) const { return castVoid (obj)->getAngle (); }
        void setValue (void *obj, double value) const { castVoid (obj)->setAngle (value); }
};

unsigned int const ANGLE = 3;

} /* namespace Tween */

#	endif /* AFFINEACCESSOR_H_ */
