/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_ABSTRACTMODEL_H_
#define BAJKA_ABSTRACTMODEL_H_

#include "model/IModel.h"
#include "util/ReflectionMacros.h"
#include "IBox.h"
#include "IGroup.h"

namespace Model {
class BoxGroup;

/**
 * Wspólna implemntacja modeli. To jest klasa zbierająca do kupy wspólny kod, który powtarzał by się
 * we wszystkich modelach. Czyli tu dziedziczenie zostało użyte nie do grupowania pojęć, a do reużywalności
 * kodu.
 */
class AbstractModel : public IModel {
public:

        d__

        AbstractModel () : parent (0),
                translate (Geometry::ZERO_POINT),
                angle (0),
                scale (1),
                view (0),
                controller (0),
                groupProps (NULL) {}

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

        IGroupProperties *getGroupProps () { return groupProps; }
        void setGroupProps (IGroupProperties *l) { groupProps = l; }

/*--------------------------------------------------------------------------*/

        virtual bool isBox () const { return false; }
        virtual bool isGroup () const { return false; }

/*--------------------------------------------------------------------------*/

        virtual IModel *findContains (Geometry::Point const &p);
        virtual Geometry::Box getBoundingBox () const { return getBoundingBoxImpl (getMatrix ()); }

/*--------------------------------------------------------------------------*/

        virtual void update (Event::UpdateEvent *e);

/*--------------------------------------------------------------------------*/

        /*
         * TODO Może wszędzie gdzie tu jest IModel dać IGroup?
         */
        IModel *getParent () { return parent; }
        void setParent (IModel *m) { parent = m; }
        void onParentSet (IModel *m) {}

/*--------------------------------------------------------------------------*/

        virtual View::IView *getView () { return view; }
        void setView (View::IView *v) { view = v; }

        Controller::IController *getController () { return controller; }
        void setController (Controller::IController *c) { controller = c; }

protected:

        IModel *parent;
        Geometry::Point translate;
        double angle;
        double scale;

private:

        std::auto_ptr <Geometry::Point> center;
        View::IView *                   p_ (view);
        Controller::IController *       p_ (controller);
        IGroupProperties *              p_ (groupProps);

        E_ (AbstractModel)
};

} /* namespace Model1 */

#	endif /* ABSTRACTMODEL_H_ */
