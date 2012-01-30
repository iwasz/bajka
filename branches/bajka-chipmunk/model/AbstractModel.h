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

        AbstractModel () : parent (0), angle (0), scale (1), view (0), controller (0) {}
        virtual ~AbstractModel () {}

/*--------------------------------------------------------------------------*/

        virtual Geometry::Point getPosition () const { return position; }
        m_ (setPosition) virtual void setPosition (Geometry::Point const &p) { position = p; }

        virtual Geometry::Point getCenter () const;
        m_ (setCenter) virtual void setCenter (Geometry::Point const &p);
        // TODO pure virtual
        virtual Geometry::Point computeCenter () const { return Geometry::Point(); }

        virtual double getAngle () const { return angle; }
        m_ (setAngle) virtual void setAngle (double a) { angle = a; }

        virtual double getScale () const { return scale; }
        m_ (setScale) virtual void setScale (double s) { scale = s; }

/*--------------------------------------------------------------------------*/

        virtual void transform (Geometry::Point *p) const;

        // TODO wywalić.
        virtual Geometry::Box getBoundingBox () const {}
        virtual bool contains (Geometry::Point const &p) const {}

/*--------------------------------------------------------------------------*/

        virtual IModel *findContains (Geometry::Point const &p) { return NULL; }

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
        ModelVector::const_iterator begin () const { return children.begin (); }
        ModelVector::const_iterator end () const { return children.end (); }

/*--------------------------------------------------------------------------*/

        View::IView *getView () { return view; }
        S_ (setView) void setView (View::IView *v) { view = v; }

        Controller::IController *getController () { return controller; }
        S_ (setController) void setController (Controller::IController *c) { controller = c; }


protected:

        IModel *parent;
        ModelVector children;

        Geometry::Point position;
        double angle;
        double scale;

private:

        std::auto_ptr <Geometry::Point> center;
        View::IView *view;
        Controller::IController *controller;

        E_ (AbstractModel)
};

} /* namespace Model1 */

#	endif /* ABSTRACTMODEL_H_ */
