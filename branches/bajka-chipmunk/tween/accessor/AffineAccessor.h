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
#include "../../model/IModel.h"

namespace Tween {

/**
 *
 */
struct TranslateXAccessor : public IAccessor {
        ~TranslateXAccessor () {}
        double getValue (void *obj) const { return static_cast <Model::IModel *> (obj)->getTranslate ().x; }
        void setValue (void *obj, double value)
        {
        	Model::IModel *m = static_cast <Model::IModel *> (obj);
        	Geometry::Point p = m->getTranslate ();
        	p.x = value;
        	m->setTranslate (p);
        }
};

/**
 *
 */
struct TranslateYAccessor : public IAccessor {
        ~TranslateYAccessor () {}
        double getValue (void *obj) const { return static_cast <Model::IModel *> (obj)->getTranslate ().y; }
        void setValue (void *obj, double value)
        {
        	Model::IModel *m = static_cast <Model::IModel *> (obj);
        	Geometry::Point p = m->getTranslate ();
        	p.y = value;
        	m->setTranslate (p);
        }};

/**
 *
 */
struct ScaleAccessor : public IAccessor {
        ~ScaleAccessor () {}
        double getValue (void *obj) const { return static_cast <Model::IModel *> (obj)->getScale (); }
        void setValue (void *obj, double value) { static_cast <Model::IModel *> (obj)->setScale (value); }
};

/**
 *
 */
struct AngleAccessor : public IAccessor {
        ~AngleAccessor () {}
        double getValue (void *obj) const { return static_cast <Model::IModel *> (obj)->getAngle (); }
        void setValue (void *obj, double value) { static_cast <Model::IModel *> (obj)->setAngle (value); }
};

} /* namespace Tween */

#	endif /* AFFINEACCESSOR_H_ */
