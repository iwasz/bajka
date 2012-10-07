/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_MODEL_BOX_GROUP2_H_
#define BAJKA_MODEL_BOX_GROUP2_H_

#include <map>
#include "Layer.h"

namespace Model {
class RelativeGroupProperties;

/**
 * Grupa, która jednocześnie jest grupą i pudełkiem Box (ma wymiary w przeciwieństwie do zwykłej grupy).
 */
class RelativeGroup : public Layer  {
public:

	C__ (void)
	b_ ("Layer")

	virtual ~RelativeGroup() {}

/*--layout------------------------------------------------------------------*/

	void updateLayout ();
        virtual void update (Event::UpdateEvent *e);

/*--------------------------------------------------------------------------*/

        CoordinateSystemOrigin getCoordinateSystemOrigin () const { return BOTTOM_LEFT; }
        bool contains (Geometry::Point const &p) const;
        Geometry::Box getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const;

private:

        /*
         * @param w Aktualna wysokość boundingBoxa modelu dla którego
         * @param h Aktualna szerokość boundingBoxa modelu m
         */
        void calculateTranslation (IModel *child, RelativeGroupProperties const *props);

        /*
         * Ustawienia szerokość i wysokość obieku wewnątrz tego RelativeGroup na podstawie
         * width i height w skojarzonym z tym obiektem RelativeGroupProperties. Działa tylko
         * dla obiektów implementujących IBox i bez transformacji angle i scale.
         */
        void adjustChildrenDimensions (IModel *child, RelativeGroupProperties const *props);

        E_ (RelativeGroup)
};

} /* namespace Model */

#endif /* GROUP_H_ */
