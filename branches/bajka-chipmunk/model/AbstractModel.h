/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_ABSTRACTMODEL_H_
#define BAJKA_ABSTRACTMODEL_H_

#include "IModel.h"
#include "../util/ReflectionMacros.h"

namespace Model {

class AbstractModel : public IModel {
public:

        d__

        AbstractModel () : parent (0), view (0), controller (0) {}
        virtual ~AbstractModel () {}

        // TODO wywalić.
        virtual double getScale () const { return 1; }
        virtual void setScale (double a) {}
        virtual Geometry::Point getCenter () const { return Geometry::Point (); }
        virtual void setCenter (Geometry::Point const &p) {}
        virtual void transform (Geometry::Point *p) {}

        Geometry::Box getBoundingBox () const {}
        bool inside (Geometry::Point const &p) const {}

/*--------------------------------------------------------------------------*/

        virtual IModel *findChild (Geometry::Point const &p) { return NULL; }


/*--------------------------------------------------------------------------*/

        virtual bool update ();

/*--------------------------------------------------------------------------*/

        IModel *getParent () { return parent; }
        void setParent (IModel *m) { parent = m; }
        void parentCallback (IModel *m) {}

        m_ (getChildren) ModelVector &getChildren () { return children; }
        m_ (setChildren) void setChildren (ModelVector const &c);
        void addChild (IModel *m);
        ModelVector::iterator begin () { return children.begin (); }
        ModelVector::iterator end () { return children.end (); }

/*--------------------------------------------------------------------------*/

        View::IView *getView () { return view; }
        s_ (setView) void setView (View::IView *v) { view = v; }

        Controller::IController *getController () { return controller; }
        s_ (setController) void setController (Controller::IController *c) { controller = c; }

private:

        IModel *parent;
        ModelVector children;
        View::IView *view;
        Controller::IController *controller;

        E_ (AbstractModel)
};

} /* namespace Model1 */

#	endif /* ABSTRACTMODEL_H_ */
