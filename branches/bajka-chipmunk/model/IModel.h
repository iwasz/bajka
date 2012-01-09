/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_IMODEL_H_
#define BAJKA_IMODEL_H_

#include <vector>
#include <Object.h>
#include <chipmunk.h>
#include "../view/IView.h"
#include "../controller/IController.h"
#include "../geometry/Point.h"

namespace Model {

struct IModel;

/**
 *
 */
typedef std::vector <IModel *> ModelVector;

/**
 *
 */
struct IModel : public Core::Object {

        virtual ~IModel () {}

        /**
         * Pozycja tego modelu we współrzędnych rodzica. Jest to pozycja
         * pewnego punktu w tym modelu (na przykład środek okręgu).
         */
        virtual Geometry::Point getPosition () const = 0;
        virtual void setPosition (Geometry::Point const &position) = 0;

        virtual double getAngle () const = 0;
        virtual void setAngle (double a) = 0;

        virtual double const *getMatrix () const = 0;

/*--------------------------------------------------------------------------*/

        virtual bool update () = 0;

/*--------------------------------------------------------------------------*/

        virtual IModel *getParent () = 0;

        /**
         * Także callback;
         * @param m
         */
        virtual void setParent (IModel *m) = 0;
        virtual void parentCallback (IModel *m) = 0;

        virtual ModelVector &getChildren () = 0;
        virtual void setChildren (ModelVector const &) = 0;
        virtual void addChild (IModel *m) = 0;
        virtual ModelVector::iterator begin () = 0;
        virtual ModelVector::iterator end () = 0;

/*--------------------------------------------------------------------------*/

        virtual View::IView *getView () = 0;
        virtual void setView (View::IView *v) = 0;

        virtual Controller::IController *getController () = 0;
        virtual void setController (Controller::IController *c) = 0;

};

} /* namespace Geometry */

#	endif /* IMODEL_H_ */
