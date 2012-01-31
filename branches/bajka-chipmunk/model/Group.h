/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_MODEL_GROUP_H_
#define BAJKA_MODEL_GROUP_H_

#include "AbstractModel.h"
#include "IGroup.h"
#include "../geometry/Point.h"
#include "../util/ReflectionMacros.h"

namespace Model {

/**
 * Podstawowa grupa modeli, czyli coś, co się rozciąga w nieskończoność (nie ma
 * swojego rozmiaru).
 */
class Group : public AbstractModel, public IGroup {
public:

	C__ (void)
	b_ ("AbstractModel")

	virtual ~Group() {}

    virtual Geometry::Point computeCenter () const { return Geometry::Point (); }
    virtual Geometry::Box getBoundingBox () const;
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

    E_ (Group)
};

} /* namespace Model */

#endif /* GROUP_H_ */
