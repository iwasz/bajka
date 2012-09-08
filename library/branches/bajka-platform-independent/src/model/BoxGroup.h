/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_MODEL_BOX_GROUP2_H_
#define BAJKA_MODEL_BOX_GROUP2_H_

#include "util/ReflectionMacros.h"
#include "IBox.h"
#include "model/Group.h"

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
class BoxGroup : public IBox, public Group  {
public:

	C__ (void)
	b_ ("Group")

	BoxGroup () : w (0), h(0), relW (-1), relH (-1), relX (-1), relY (-1), expand (false) {}
	virtual ~BoxGroup() {}

/*--IBox--------------------------------------------------------------------*/

        double getWidth () const;
        m_ (setWidth) void setWidth (double w) { this->w = w; }
        double getHeight () const;
        m_ (setHeight) void setHeight (double h) { this->h = h; }

        Geometry::Box getBox () const;

/*--layout------------------------------------------------------------------*/

	m_ (setRelW) void setRelW (double w);
	m_ (setRelH) void setRelH (double w);
//	m_ (setRelX) void setRelX (double x);
//	m_ (setRelY) void setRelY (double y);

	/**
	 * Czy grupa rozciąga się pod wpływem zawieranych modli, czy nie.
	 */
	               bool getExpand () const { return expand; }
	m_ (setExpand) void setExpand (bool e) { expand = e; }

/*--------------------------------------------------------------------------*/

        bool isBox () const { return true; }

        virtual Geometry::Point computeCenter () const { return Geometry::makePoint (w / 2, h / 2); }
        virtual Geometry::Box getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const;
        virtual bool contains (Geometry::Point const &p) const;
        virtual IModel *findContains (Geometry::Point const &p);

/*--------------------------------------------------------------------------*/

        /**
         * Zwraca rodzica jako BoxGroup. Zrzuca wyjątek, jeśli rodzic nie jest tego typu.
         * @return
         */
        static BoxGroup const *getParGroup (IModel const *m);
        static BoxGroup *getParGroup (IModel *m);

private:

        double w, h;
        // Cache uzywany do inicjowania. Po inicjacji już nie używany.
        double relW, relH, relX, relY;
        bool expand;

        E_ (BoxGroup)
};

} /* namespace Model */

#endif /* GROUP_H_ */
