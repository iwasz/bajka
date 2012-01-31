/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_MODEL_BOX_GROUP_H_
#define BAJKA_MODEL_BOX_GROUP_H_

#include "../geometry/Point.h"
#include "../util/ReflectionMacros.h"
#include "../model/static/Box.h"
#include "IGroup.h"

namespace Model {

/**
 * Grupa, która jednocześnie jest grupą i pudełkiem Box (ma wymiary w przeciwieństwie do zwykłej grupy).
 */
class BoxGroup : public Box, public IGroup {
public:

	C__ (void)
	b_ ("Box")

	virtual ~BoxGroup() {}

    virtual Geometry::Point computeCenter () const { return Box::computeCenter (); }
    virtual bool contains (Geometry::Point const &p) const { return true; }
    bool isGroup () const { return true; }
    virtual IModel *findContains (Geometry::Point const &p);

/*--------------------------------------------------------------------------*/

    m_ (getChildren) ModelVector &getChildren () { return children; }
    m_ (setChildren) void setChildren (ModelVector const &c);
    void addChild (IModel *m);
    ModelVector::iterator begin () { return children.begin (); }
    ModelVector::iterator end () { return children.end (); }
    ModelVector::const_iterator begin () const { return children.begin (); }
    ModelVector::const_iterator end () const { return children.end (); }

private:

    ModelVector children;

    E_ (BoxGroup)
};

} /* namespace Model */

#endif /* GROUP_H_ */
