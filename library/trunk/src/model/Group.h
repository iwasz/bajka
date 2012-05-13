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
 *
 * Bounding box takiej grupy jest zawsze rozciągnięty żeby miściły się w nim wszystkie
 * dzieci.
 *
 * Środek transformacji (obrotu i skali) domyślnie jest w punkcie 0,0 (nie jest
 * wyliczany na podstawie rozmieszczenia dzieci).
 */
class Group : public AbstractModel, public IGroup {
public:

	C__ (void)
	b_ ("AbstractModel")

	Group () : eventIndex (NULL), pointerInsideIndex (NULL) {}
	virtual ~Group() {}

        virtual Geometry::Point computeCenter () const { return Geometry::Point (); }
        virtual Geometry::Box getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const;
        virtual bool contains (Geometry::Point const &p) const { return true; }
        bool isGroup () const { return true; }
        virtual IModel *findContains (Geometry::Point const &p);

        void screenToGroup (Geometry::Point *p) const;
        void groupToScreen (Geometry::Point *p) const;

/*--------------------------------------------------------------------------*/

        void setIndices (Event::EventIndex *e1, Event::PointerInsideIndex *e2);

/*--------------------------------------------------------------------------*/

        m_ (getChildren) ModelVector &getChildren () { return children; }
        m_ (setChildren) void setChildren (ModelVector const &c);
        void addChild (IModel *m);
        void popChild ();
        IModel *getTop ();
        ModelVector::iterator begin () { return children.begin (); }
        ModelVector::iterator end () { return children.end (); }
        ModelVector::const_iterator begin () const { return children.begin (); }
        ModelVector::const_iterator end () const { return children.end (); }

protected:

        ModelVector children;

        /**
         * Ustawiane przez App (mogło by być prywatne + friend, ale mi się nie chce kombinować).
         * Jest to indeks modeli, w którym można szybko wyszukać Event::Type -> IModel. Dzieki temu
         * dispatchery wiedzą gdzie kierować eventy;
         */
        Event::EventIndex *eventIndex;

        /**
         * Ustawiane przez App. To jest indeks, który zawiera informację o modelach, nad którymi
         * aktualnie znajduje się kursor myszy. Ten indeks ułatwia generowanie eventów onMouseOut.
         * Grupy mają do niego wskaźnik, żeby mogły usuwać z niego na berząco modele, gdy user usunie
         * model z grupy.
         */
        Event::PointerInsideIndex *pointerInsideIndex;

        E_ (Group)
};

} /* namespace Model */

#endif /* GROUP_H_ */
