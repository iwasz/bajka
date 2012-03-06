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
#include "IBox.h"
#include "IGroup.h"

namespace Model {
class BoxGroup;

class AbstractModel : public IModel {
public:

        d__

        AbstractModel () : parent (0), angle (0), scale (1), view (0), controller (0), layout (NULL) {}
        virtual ~AbstractModel () {}

/*--------------------------------------------------------------------------*/

        virtual Geometry::Point getTranslate () const;
        m_ (setTranslate) virtual void setTranslate (Geometry::Point const &p);

        virtual Geometry::Point getCenter () const;
        m_ (setCenter) virtual void setCenter (Geometry::Point const &p);
        virtual Geometry::Point computeCenter () const = 0;

        virtual double getAngle () const { return angle; }
        m_ (setAngle) virtual void setAngle (double a) { angle = a; }

        virtual double getScale () const { return scale; }
        m_ (setScale) virtual void setScale (double s) { scale = s; }

        virtual Geometry::AffineMatrix getMatrix () const;

/*--------------------------------------------------------------------------*/

        m_ (getLayout) Layout *getLayout () { return layout; }
        m_ (setLayout) void setLayout (Layout *l) { layout = l; }

/*--------------------------------------------------------------------------*/

        virtual bool isBox () const { return false; }
        virtual bool isGroup () const { return false; }

/*--------------------------------------------------------------------------*/

        virtual IModel *findContains (Geometry::Point const &p);
        virtual Geometry::Box getBoundingBox () const { return getBoundingBoxImpl (getMatrix ()); }

/*--------------------------------------------------------------------------*/

        virtual void update (Event::UpdateEvent *e);

/*--------------------------------------------------------------------------*/

        IModel *getParent () { return parent; }
        void setParent (IModel *m) { parent = m; }
        void onParentSet (IModel *m) {}

/*--------------------------------------------------------------------------*/

        m_ (getView) virtual View::IView *getView () { return view; }
        S_ (setView) void setView (View::IView *v) { view = v; }

        m_ (getController) Controller::IController *getController () { return controller; }
        S_ (setController) void setController (Controller::IController *c) { controller = c; }

protected:

        IModel *parent;
        Geometry::Point translate;
        double angle;
        double scale;

private:

        std::auto_ptr <Geometry::Point> center;
        View::IView *view;
        Controller::IController *controller;
        Layout *layout;

        E_ (AbstractModel)
};

} /* namespace Model1 */

#	endif /* ABSTRACTMODEL_H_ */
