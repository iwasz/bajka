/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_IGROUP_H_
#define BAJKA_IGROUP_H_

#include <core/Object.h>
#include "model/IModel.h"

namespace Event {
class EventIndex;
class PointerInsideIndex;
}

namespace Model {

/**
 * Interfejs grup, czyli kontenerów innych modeli. Grupuje modele logicznie i graficznie.
 * Dzieci sa wyświetlane od pierwszego do ostatniego, przy czym kazde następne zasłania
 * poprzednie.
 */
struct IGroup : public virtual Core::Object {

        virtual ~IGroup () {}

        /**
         * Konwersja współrzędnych.
         */
        virtual void screenToGroup (Geometry::Point *p) const = 0;

        /**
         * Konwersja współrzędnych.
         */
        virtual void groupToScreen (Geometry::Point *p) const = 0;

        /**
         * Kolekcja modeli. Zwraca kolekcję modeli, którą zawiera ta grupa. Ta kolekcja to
         * takzwane dzieci grupy. Grupa może zawierać inne grupy.
         */
        virtual ModelVector &getChildren () = 0;

        /**
         * Ustawia kolekcję dzieci. Stara kolekcja zostaje wymazana.
         */
        virtual void setChildren (ModelVector const &) = 0;

        /**
         * Dodaje model. Dodaje model na koniec kolekcji. Aktualnie dodany model bedzie ostatni
         * w kolekcji modeli i przez to wyświetli się jako ostatni, zasłaniając (to zalezy oczywiście
         * też od jego rozmiarów) poprzednie modele.
         */
        virtual void addChild (IModel *m) = 0;

        /**
         * Usuwa model. Usuwa ostatnio dodany model (czyli ostatni z kolekcji).
         */
        virtual void popChild () = 0;

        /**
         * Pobiera ostatnio dodany model.
         */
        virtual IModel *getTop () = 0;

        /**
         * Iterator.
         */
        virtual ModelVector::iterator begin () = 0;

        /**
         * Iterator.
         */
        virtual ModelVector::iterator end () = 0;

        /**
         * Iterator.
         */
        virtual ModelVector::const_iterator begin () const = 0;

        /**
         * Iterator.
         */
        virtual ModelVector::const_iterator end () const = 0;

        /**
         * Ustawiane przez bajkaApp. Bardziej szczegółowa dokumentacja w klasie Group.
         */
        virtual void setIndices (Event::EventIndex *e1, Event::PointerInsideIndex *e2) = 0;

        enum CoordinateSystemOrigin { CENTER, BOTTOM_LEFT };

        /**
         * Zwraca jedną z 2 wartości opisujących gdzie znajduje się środek układu współrzędnych
         * tej grupy. Ta wartość ma znaczenie tylko dla grup, ktgóre mają szerokość i wysokość.
         * Wartość CENTER oznacza, że środek układu współrzędncyh tej gurpy znajduje się pośrodku
         * prostokąta wyznaczonego przez wysokość i szerokośc tej grupy, BOTTOM_LEFT oznacza, ze
         * srodek jest w dolnym lewym rogu.
         */
        virtual CoordinateSystemOrigin getCoordinateSystemOrigin () const = 0;
};

}

#	endif /* IMODEL_H_ */
