/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IMODEL_H_
#define IMODEL_H_

#include <Object.h>

#include "geometry/Utils.h"
#include "geometry/Point.h"
#include "tree/TreeSlave.h"
#include "IController.h"
#include "geometry/Box.h"
#include "IModelAware.h"

/**
 * Klasy związane z modelem. Klasy z warstwy domenowej.
 */
namespace Model {

/**
 * Marker
 * TODO Zastanowić się jakie właściwie tu powinny być metody.
 *
 * Rodzaje układów współrzędznych w Bajce.
 * - Device coordinates : to są współrzędne ekranowe po naszemu i w ich przypadku
 * w górnym lewym rogu ekranu zawsze wypada 0,0. Oś Y rośnie do dołu, jednostki są
 * całkowite.
 * - Screen coordinates : to są współrzędne root-modelu. Jeśli rot-model nie ma ustawionej
 * żadnej transformacji, to jedyna różnica polega na tym, że oś Y rośnie do góry, a środek
 * ukłądu przebiega przez środek ekranu. Po nałożeniu transofmracji (czyli przemnożeniu
 * macierzy transofmracji root-modelu przez jakąś macierz przekształacającą) środek układu
 * może wylądować gdzieś indziej, układ może się też obrócić o jakiś kąt etc.
 * - Model coordinates / item coordinates : to są współrzędne układu odniesieina dla
 * konkretnego modelu. Zasada jest ta sama co w przypadku screen-coordinates, tylko, że
 * modele można zagnieżdżać i każdy ma macierz transformacji. Z tego wynika, że model na
 * samym dole tej chierarchii (ostatnie dziecko) ma transformację skłądającą się z
 * przemnożonych macierzy swoich rodziców i swojej.
 */
struct IModel :
        virtual public Core::Object,
        public Util::TreeSlave <IModel, IModelAware, &IModelAware::getModel> {

        virtual ~IModel () {}

/*------przekształcenia-----------------------------------------------------*/

        /**
         * Returns affine transformation matrix for this object.
         */
        virtual
        Geometry::AffineMatrix const &
        getMatrix () const = 0;

        virtual void setMove (const Geometry::Point &p) = 0;
        virtual void setRotate (double r) = 0;
        virtual void setResize (double w, double h) = 0;
        virtual void setResizeW (double w) = 0;
        virtual void setResizeH (double h) = 0;

        virtual Geometry::Point const &screenToModel (Geometry::Point const &) const = 0;
        virtual Geometry::Point const &modelToScreen (Geometry::Point const &) const = 0;

/*------kształt-------------------------------------------------------------*/

        /**
         * Sprawdza, czy punkt znajduje się w środku danego modelu.
         */
        virtual bool enclose (const Geometry::Point &p) const = 0;
        //virtual bool enclose (const Geometry::Box &p) const = 0;
        // ...

        virtual double getWidth () const = 0;
        virtual double getHeight () const = 0;

        /**
         * Zwraca boundingBox w układzie współrzędnych swojego rodzica.
         * @return
         */
        virtual Geometry::Box const &getBoundingBox () const = 0;


        virtual Geometry::AffineMatrix const &updateMatrixStack () const = 0;

};


}

#	endif /* IMODEL_H_ */
