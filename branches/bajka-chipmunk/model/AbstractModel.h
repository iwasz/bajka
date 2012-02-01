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

/*--------------------------------------------------------------------------*/

        virtual Geometry::Point getTranslate () const;
        m_ (setTranslate) virtual void setTranslate (Geometry::Point const &p);

        virtual Geometry::Point getCenter () const;
        m_ (setCenter) virtual void setCenter (Geometry::Point const &p);
        virtual Geometry::Point computeCenter () const = 0;

        virtual double getAngle () const;
        m_ (setAngle) virtual void setAngle (double a);

        virtual double getScale () const;
        m_ (setScale) virtual void setScale (double s);

        virtual Geometry::AffineMatrix const &getMatrix () const;

/*--------------------------------------------------------------------------*/

        virtual bool isBox () const { return false; }
        virtual bool isGroup () const { return false; }

/*--------------------------------------------------------------------------*/

        virtual void transform (Geometry::Point *p) const;

/*--------------------------------------------------------------------------*/

        virtual IModel *findContains (Geometry::Point const &p) { return NULL; }

/*--------------------------------------------------------------------------*/

        virtual void update ();

/*--------------------------------------------------------------------------*/

        IModel *getParent () { return parent; }
        void setParent (IModel *m) { parent = m; }
        void parentCallback (IModel *m) {}

/*--------------------------------------------------------------------------*/

        View::IView *getView () { return view; }
        S_ (setView) void setView (View::IView *v) { view = v; }

        Controller::IController *getController () { return controller; }
        S_ (setController) void setController (Controller::IController *c) { controller = c; }

protected:

        IModel *parent;
        std::auto_ptr <Geometry::AffineMatrix> matrix;

private:

        void initMatrix ();

private:

        std::auto_ptr <Geometry::Point> center;
        View::IView *view;
        Controller::IController *controller;

        E_ (AbstractModel)
};

} /* namespace Model1 */

#	endif /* ABSTRACTMODEL_H_ */
