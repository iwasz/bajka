/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "RelativeGroup.h"
#include "util/Exceptions.h"
#include "geometry/Ring.h"
#include "geometry/AffineMatrix.h"
#include "model/static/Box.h"
#include "model/static/Circle.h"
#include "RelativeGroupProperties.h"
#include "Align.h"

namespace Model {
using namespace boost::geometry;
namespace G = Geometry;
namespace trans = boost::geometry::strategy::transform;

/****************************************************************************/

void RelativeGroup::update (Event::UpdateEvent *e, Util::UpdateContext *uCtx)
{
        // TODO to nie powino się updejtować przy każdym odświerzeniu. Do wywalenia jest ta metoda.
        // Może używac jakiegoś cache child-objectów i sprawdzać czy coś im się zmieniło (na przykład za pomocą jakiegoś HASHa wyliczanego na podstawie translate, angle i size).
        updateLayout ();
        Group::update (e, uCtx);
}

/****************************************************************************/

void RelativeGroup::updateLayout ()
{
        // Rozmieść i rozszerz dzieci.
        for (ModelVector::iterator i = children.begin (); i != children.end (); ++i) {
                IModel *child = *i;
                RelativeGroupProperties const *props = ((child->getGroupProps ()) ? (dynamic_cast <RelativeGroupProperties const *> (child->getGroupProps ())) : (NULL));

                if (!props) {
                        continue;
                }

                adjustChildrenDimensions (child, props);

                // Pozycja dzieci :
                calculateTranslation (child, props);
        }
}

/****************************************************************************/

void RelativeGroup::adjustChildrenDimensions (IModel *child, RelativeGroupProperties const *props)
{
        // Rozmiar dziecu AABB - tak zmienia rozmiar obiektu, żeby jego AABB stanowiło dany procent wysokości / szerokości tego RelativeGroup:
        IBox *box = NULL;
        if ((props->width > 0 || props->height > 0) && (box = dynamic_cast <IBox *> (child))) {
                if (child->getAngle () || child->getScale () != 1) {
                        throw Util::RuntimeException ("RelativeGroup::updateLayout : width or height of an object was requested, but angle or scale is set. I don't know how to adjust AABB of objects with transformations applied.");
                }

                float reqW = props->width;
                float reqH = props->height;

                if (reqW >= 0) {
                        box->setWidth (getWidth () * reqW / 100.0);
                }

                if (reqH >= 0) {
                        box->setHeight (getHeight () * reqH / 100.0);
                }
        }
}

/****************************************************************************/

void RelativeGroup::calculateTranslation (IModel *child, RelativeGroupProperties const *props)
{
        G::Box aabb = child->getBoundingBox ();
        float aabbW = aabb.getWidth ();
        float aabbH = aabb.getHeight ();

        G::Point tReq = props->translate;
        G::Point ct;

        ct.x = getWidth() * tReq.x / 100.0;
        ct.y = getHeight () * tReq.y / 100.0;

        if (props->hAlign == HA_RIGHT && props->vAlign == VA_TOP) {
                // zwróć ct, ct jest gotowe.
        }
        else {
                if (tReq.x >= 0) {
                        if (props->hAlign == HA_CENTER) {
                                ct.x -= aabbW / 2.0;
                        }
                        else if (props->hAlign == HA_LEFT) {
                                ct.x -= aabbW;
                        }
                }

                if (tReq.y >= 0) {
                        if (props->vAlign == VA_CENTER) {
                                ct.y -= aabbH / 2.0;
                        }
                        else if (props->vAlign == VA_BOTTOM) {
                                ct.y -= aabbH;
                        }
                }

        }

        child->setTranslate (ct);
}

/****************************************************************************/

bool RelativeGroup::contains (G::Point const &p) const
{
        G::Ring ring;
        G::Ring output;
        convert (getBox (), ring);
        G::AffineMatrixTransformer matrix (getMatrix ());
        transform (ring, output, matrix);
        return within (p, output);
}

/****************************************************************************/

G::Box RelativeGroup::getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const
{
        G::Ring ring;
        G::Ring output;
        G::Box box;
        convert (getBox (), ring);
        G::AffineMatrixTransformer matrix (transformation);
        transform (ring, output, matrix);
        envelope (output, box);
        return box;
}

} /* namespace Model */
