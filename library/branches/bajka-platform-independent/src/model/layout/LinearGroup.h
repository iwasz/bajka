/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_MODEL_LINEAR_GROUP_H_
#define BAJKA_MODEL_LINEAR_GROUP_H_

#include "util/ReflectionMacros.h"
#include "model/IBox.h"
#include "model/Group.h"
#include <map>
#include "Align.h"

namespace Model {
class RelativeGroupProperties;

/**
 * Grupa.
 */
class LinearGroup : public IBox, public Group  {
public:

        enum Type { HORIZONTAL, VERTICAL };

	C__ (void)
	b_ ("Group")

	LinearGroup () : w (0),
	        h(0),
	        type (HORIZONTAL),
                spacing (0),
                margin (0),
	        wrapContentsW (false),
	        wrapContentsH (false),
	        hGravity (HG_LEFT),
                vGravity (VG_BOTTOM) {}

	virtual ~LinearGroup() {}

        bool getWrapContentsW () const { return wrapContentsW; }
        void setWrapContentsW (bool b) { wrapContentsW = b; }

        bool getWrapContentsH () const { return wrapContentsH; }
        void setWrapContentsH (bool b) { wrapContentsH = b; }

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
         * Ustawienia szerokość i wysokość obieku wewnątrz tego LinearGroup na podstawie
         * width i height w skojarzonym z tym obiektem RelativeGroupProperties. Działa tylko
         * dla obiektów implementujących IBox i bez transformacji angle i scale.
         */
        void adjustChildrenDimensions (IBox *child, RelativeGroupProperties const *props, float *w, float *h);

        /*
         * Ustala rozmiar tej grupy. Działa tylko gdy ustawione wrapContents. Ustala rozmiar tej
         * grupy na rozmiar największego z dzieci.
         */
        void adjustMyDimensions (float w, float h);

        /*
         *
         */
        void getChildrenDimensions (float *w, float *h);

private:

        float w, h;
//        TODO
//        Type            p_ (type);
        int             p_ (type);
        float           p_ (spacing);
        float           p_ (margin);
        bool            p_ (wrapContentsW);
        bool            p_ (wrapContentsH);

//        TODO Zamienic na własciwy typ kiedy IoC będzie umiał
//        HGravity        p_ (hGravity);
//        VGravity        p_ (vGravity);
        int        p_ (hGravity);
        int        p_ (vGravity);
        E_ (LinearGroup)
};

} /* namespace Model */

#endif /* GROUP_H_ */
