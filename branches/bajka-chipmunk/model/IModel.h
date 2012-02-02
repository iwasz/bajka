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
#include "../util/ReflectionMacros.h"
#include "../view/IView.h"
#include "../controller/IController.h"
#include "../geometry/Box.h"
#include "../geometry/AffineMatrix.h"

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
 * (jego konturów). Aczkolwiek nie przywiązywał bym się do tego pomysłu.
 */
struct IModel : public virtual Core::Object {

        virtual ~IModel () {}

        /**
         * Przesunięcie. Większość kształtów sama w sobie jest jakoś
         * umiejscowiona w przestrzeni. Na prztykład Box jest zdefiniowany
         * za pomocą 2 wierzchołków, które mogą być w dowolnym miejscu.
         * Jednak translate jest dodatkowym przesunięciem, które nie
         * modyfikuje tych wierzchołków, a jedynie powoduje ich transformację
         * przez macierz przesunięcia.
         */
        virtual Geometry::Point getTranslate () const = 0;
        virtual void setTranslate (Geometry::Point const &translate) = 0;

        virtual double getAngle () const = 0;
        virtual void setAngle (double a) = 0;

        virtual double getScale () const = 0;
        virtual void setScale (double a) = 0;

        /**
         * Punkt względem którego wykonywane są obroty i skalowanie.
         */
        virtual Geometry::Point getCenter () const = 0;
        virtual void setCenter (Geometry::Point const &p) = 0;

        /**
         * Macierz przekształceń.
         */
        virtual Geometry::AffineMatrix getMatrix () const = 0;

/*------runtime type information--------------------------------------------*/

        virtual bool isBox () const = 0;
        virtual bool isGroup () const = 0;

/*------searching-----------------------------------------------------------*/

        /**
         * Znajduje model w zadanym punkcie. Zaczyna przeszukiwanie od dzieci,
         * i idzie w dół, jeśli nie znajdzie. W ten sposób możliwe, że zwróci
         * samego siebie, jeśli żadne jego dziecko nie znajduje się w podanym
         * punkcie, albo ten model nie ma żadnych dzieci. Współrzędne punktu p
         * podajemy oczywiście w układzie tego (this) modelu.
         */
        virtual IModel *findContains (Geometry::Point const &p) = 0;

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
        virtual bool contains (Geometry::Point const &p) const = 0;

/*--------------------------------------------------------------------------*/

        virtual void update () = 0;

/*------parent-child--------------------------------------------------------*/

        virtual IModel *getParent () = 0;

        /**
         * Także callback; TODO jedna metoda zamiast dwóch byłaby lepsza.
         * @param m
         */
        virtual void setParent (IModel *m) = 0;
        virtual void parentCallback (IModel *m) = 0;

/*------additional-functionalities------------------------------------------*/

        virtual View::IView *getView () = 0;
        virtual void setView (View::IView *v) = 0;

        virtual Controller::IController *getController () = 0;
        virtual void setController (Controller::IController *c) = 0;

};

} /* namespace Geometry */

#	endif /* IMODEL_H_ */
