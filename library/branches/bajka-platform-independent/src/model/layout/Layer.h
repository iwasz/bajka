/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef LAYER_BAJKA_MODEL_BOX_GROUP2_H_
#define LAYER_BAJKA_MODEL_BOX_GROUP2_H_

#include "util/ReflectionMacros.h"
#include "model/IBox.h"
#include "model/Group.h"
#include <map>
#include "LayerProperties.h"

namespace Model {
class RelativeGroupProperties;

/**
 * Grupa, która jednocześnie jest grupą i pudełkiem Box (ma wymiary w przeciwieństwie do zwykłej grupy).
 */
class Layer : public IBox, public Group  {
public:

	C__ (void)
	b_ ("Group")

	Layer () : w (0), h (0) {}
	virtual ~Layer() {}

/*--layout------------------------------------------------------------------*/

	void updateLayout ();
        virtual void update (Event::UpdateEvent *e);

/*--IBox--------------------------------------------------------------------*/

        double getWidth () const { return w; }
        m_ (setWidth) void setWidth (double w) { this->w = w; }
        double getHeight () const { return h; }
        m_ (setHeight) void setHeight (double h) { this->h = h; }

        Geometry::Box getBox () const { return Geometry::Box (0, 0, w - 1, h - 1); }
        virtual CoordinateSystemOrigin getCoordinateSystemOrigin () const { return CENTER; }

/*--------------------------------------------------------------------------*/

        bool isBox () const { return true; }

        virtual Geometry::Box getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const;
        virtual bool contains (Geometry::Point const &p) const;
        virtual IModel *findContains (Geometry::Point const &p);

private:

        /*
         * Ustawienia szerokość i wysokość obieku wewnątrz tego Layer na podstawie
         * width i height w skojarzonym z tym obiektem RelativeGroupProperties. Działa tylko
         * dla obiektów implementujących IBox i bez transformacji angle i scale.
         */
        void adjustChildrenDimensions (IModel *child, IBox *childBox, LayerProperties const *props);

protected:

        float w, h;

        E_ (Layer)
};

} /* namespace Model */

#endif /* GROUP_H_ */
