/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_LAYOUTS_TABLEGROUP_H_
#define BAJKA_LAYOUTS_TABLEGROUP_H_

#include "util/ReflectionMacros.h"
#include "model/IBox.h"
#include "model/Group.h"

namespace Model {

class TableGroup : public IBox, public Group {
public:

        C__ (void)
        b_ ("Group")

        TableGroup () :
                cols (0),
                spacing (0),
                margin (0),
                wrapContentsW (false),
                wrapContentsH (false) {}

        virtual ~TableGroup () {}

//        TODO większość metod wspólna z LinearGroup - zrobić nadklasę
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

        void adjustMyDimensions (float w, float h);
        void getChildrenDimensions (float *w, float *h);

private:

        float w, h;
        int             p_ (cols);
        float           p_ (spacing);
        float           p_ (margin);
        bool            p_ (wrapContentsW);
        bool            p_ (wrapContentsH);

        E_ (TableGroup)
};

} /* namespace Model */
#endif /* TABLEGROUP_H_ */
