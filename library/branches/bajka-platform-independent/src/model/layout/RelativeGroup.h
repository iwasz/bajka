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
#include "model/IBox.h"
#include "model/Group.h"
#include <map>

namespace Model {
class RelativeGroupProperties;

/**
 * Grupa, która jednocześnie jest grupą i pudełkiem Box (ma wymiary w przeciwieństwie do zwykłej grupy).
 */
class RelativeGroup : public IBox, public Group  {
public:

	C__ (void)
	b_ ("Group")

	RelativeGroup () : w (0), h(0) {}
	virtual ~RelativeGroup() {}

/*--layout------------------------------------------------------------------*/

	void updateLayout ();
        virtual void update (Event::UpdateEvent *e);

/*--IBox--------------------------------------------------------------------*/

        double getWidth () const { return w; }
        m_ (setWidth) void setWidth (double w) { this->w = w; }
        double getHeight () const { return h; }
        m_ (setHeight) void setHeight (double h) { this->h = h; }

        Geometry::Box getBox () const { return Geometry::Box (0, 0, w - 1, h - 1); }

/*--------------------------------------------------------------------------*/

        bool isBox () const { return true; }

        virtual Geometry::Point computeCenter () const { return Geometry::makePoint (w / 2, h / 2); }
        virtual Geometry::Box getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const;
        virtual bool contains (Geometry::Point const &p) const;
        virtual IModel *findContains (Geometry::Point const &p);

private:

        /*
         * @param w Aktualna wysokość boundingBoxa modelu dla którego
         * @param h Aktualna szerokość boundingBoxa modelu m
         */
        Geometry::Point calculateTranslation (IModel *child, RelativeGroupProperties const *props) const;

        /*
         * Ustawienia szerokość i wysokość obieku wewnątrz tego RelativeGroup na podstawie
         * width i height w skojarzonym z tym obiektem RelativeGroupProperties. Działa tylko
         * dla obiektów implementujących IBox i bez transformacji angle i scale.
         */
        void adjustChildrenDimensions (IBox *child, RelativeGroupProperties const *props, float *w, float *h);

        /*
         * Ustala rozmiar tej grupy. Działa tylko gdy ustawione wrapContents. Ustala rozmiar tej
         * grupy na rozmiar największego z dzieci.
         */
        void adjustMyDimensions ();

private:

        float w, h;

        E_ (RelativeGroup)
};

} /* namespace Model */

#endif /* GROUP_H_ */
