/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_MODEL_BOX_GROUP_H_
#define BAJKA_MODEL_BOX_GROUP_H_

#include "../geometry/Point.h"
#include "../util/ReflectionMacros.h"
#include "../model/static/Box.h"
#include "IGroup.h"

namespace Model {

/**
 * Grupa, która jednocześnie jest grupą i pudełkiem Box (ma wymiary w przeciwieństwie do zwykłej grupy).
 *
 * Jest to podstawa dla wszystkich klas layputowych takich jak tabelki, vboxy etc. Wyrozniamy 5 cech 
 * podstawowych jesli chocdzi o funkcjonalnosc layoutu:
 * 1. Rozmiar BG wzgledem rodzica (np. 50%).
 * 2. Rozmiar BG wzgledem dzieci (dopasowanie czyli scisniecie lub rozszerzenie sie BG do rozmiaru tego
 *    co jest w srodku.
 * 3. Pozycje BG wzgledem rodzica (w procentach).
 * 4. Pozycja dzieci wzgledem BG. (np. align-center lub align-lft+top)
 * 5. Rozmiar dzieci wzgledem BG.
 *
 * Z tych punktow można odrzucić 5. Bo rozciaganie dzieci nie ma większego sensu, bo one zazwyczaj same
 * ustalaja swój rozmiar.
 *
 */
class BoxGroup : public Box, public IGroup {
public:

	C__ (void)
	b_ ("Box")

	BoxGroup () : relW (-1), relH (-1), relX (-1), relY (-1) {}
	virtual ~BoxGroup() {}

/*--layout------------------------------------------------------------------*/

	m_ (setRelW) void setRelW (double w);
	m_ (setRelH) void setRelH (double w);
	m_ (setRelX) void setRelX (double x);
	m_ (setRelY) void setRelY (double y);

/*--------------------------------------------------------------------------*/

    virtual Geometry::Point computeCenter () const { return Box::computeCenter (); }
    virtual bool contains (Geometry::Point const &p) const { return true; }
    bool isGroup () const { return true; }
    virtual IModel *findContains (Geometry::Point const &p);

/*--------------------------------------------------------------------------*/

    void parentCallback (IModel *m);
    m_ (getChildren) ModelVector &getChildren () { return children; }
    m_ (setChildren) void setChildren (ModelVector const &c);
    void addChild (IModel *m);
    ModelVector::iterator begin () { return children.begin (); }
    ModelVector::iterator end () { return children.end (); }
    ModelVector::const_iterator begin () const { return children.begin (); }
    ModelVector::const_iterator end () const { return children.end (); }

private:

    BoxGroup const *getParGroup () const;
    BoxGroup *getParGroup ();

private:

    ModelVector children;
    // Cache uzywany do inicjowania. Po inicjacji już nie używany.
    double relW, relH, relX, relY;

    E_ (BoxGroup)
};

} /* namespace Model */

#endif /* GROUP_H_ */
