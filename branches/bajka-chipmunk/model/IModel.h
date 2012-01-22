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
#include "../geometry/AffineMatrix.h"
#include "../util/ReflectionMacros.h"

namespace Model {

struct IModel;

/**
 *
 */
typedef std::vector <IModel *> ModelVector;
g_ (ModelVector)

/**
 * Mam zamysł, żeby to było głownie nastawione na geometrię. Czyli kształty, pozycje
 * kąty etc. Jeśli mam obrazek, to ścieżka do obrazka będzie polem widoku, a nie modelu
 * natomiast model to będzie box, circle etc. czyli definicja kształtu tego obrazka
 * (jego konturów).
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

        virtual double getSacle () const = 0;
        virtual void setScale (double a) = 0;

/*------searching-----------------------------------------------------------*/

        /**
         * Znajduje model w zadanym punkcie. Zaczyna przeszukiwanie od dzieci,
         * i idzie w dół, jeśli nie znajdzie. W ten sposób możliwe, że zwróci
         * samego siebie, jeśli żadne jego dziecko nie znajduje się w podanym
         * punkcie, albo ten model nie ma żadnych dzieci. Współrzędne punktu p
         * podajemy oczywiście w układzie tego (this) modelu.
         */
        virtual IModel *findChild (Geometry::Point const &p) = 0;

        /**
         * Bounding box w układzie rodzica.
         * @return
         */
        virtual Geometry::Box getBoundingBox () const = 0;

        /**
         * Czy podany punkt jest wewnątrz kształtu.
         * @param p  W układzie rodzica.
         * @return
         */
        virtual bool inside (Geometry::Point const &p) const = 0;

/*--------------------------------------------------------------------------*/

        virtual bool update () = 0;

/*------parent-child--------------------------------------------------------*/

        virtual IModel *getParent () = 0;

        /**
         * Także callback; TODO jedna metoda zamiast dwóch byłaby lepsza.
         * @param m
         */
        virtual void setParent (IModel *m) = 0;
        virtual void parentCallback (IModel *m) = 0;

        virtual ModelVector &getChildren () = 0;
        virtual void setChildren (ModelVector const &) = 0;
        virtual void addChild (IModel *m) = 0;
        virtual ModelVector::iterator begin () = 0;
        virtual ModelVector::iterator end () = 0;

/*------additional-functionalities------------------------------------------*/

        virtual View::IView *getView () = 0;
        virtual void setView (View::IView *v) = 0;

        virtual Controller::IController *getController () = 0;
        virtual void setController (Controller::IController *c) = 0;

};

} /* namespace Geometry */

#	endif /* IMODEL_H_ */
