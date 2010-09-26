/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IMODEL_T_H_
#define IMODEL_T_H_

#include <Object.h>

#include "geometry/Utils.h"
#include "geometry/Point.h"
#include "geometry/Box.h"
#include "../base/tree/ITreeModel.h"

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
 *
 * Zawiera grupy metod :
 * - Przekształcenia / układ współrzędnych.
 * - Kształt.
 * - update
 *
 * TODO Układy współrzędnych, oraz środek ukłądu współrzędnych dla widgeta - to jest skoplikowane,
 * więc trzeba się upewnić, że to jest OK i jest logiczne, a potem to ładnie udokumentować i narysować.
 * TODO Metody procentowe dałbym do IModel - takzeby każdy widget mógł być resolution independent.
 * \ingroup Model
 */
struct IModel :
        public virtual Core::Object,
        public ITreeModel {

        virtual ~IModel () {}

/*------przekształcenia-----------------------------------------------------*/

        /// \name Przekształcenia / układy współrzędznych
        //\{

        /**
         * Returns affine transformation matrix for this object.
         */
        virtual
        Geometry::AffineMatrix const &
        getMatrix () const = 0;

        virtual Geometry::AffineMatrix const &updateMatrixStack () const = 0;

        virtual void setMove (const Geometry::Point &p) = 0;
        virtual void setRotate (double r) = 0;
        virtual void setResize (double w, double h) = 0;
        virtual void setResizeW (double w) = 0;
        virtual void setResizeH (double h) = 0;

        virtual Geometry::Point const &screenToModel (Geometry::Point const &) const = 0;
        virtual Geometry::Point const &modelToScreen (Geometry::Point const &) const = 0;

        //\}

/*------kształt-------------------------------------------------------------*/

        /// \name Kształt / pozycja
        //\{

        /**
         * Sprawdza, czy punkt znajduje się w środku danego modelu.
         */
        virtual bool enclose (const Geometry::Point &p) const = 0;
        //virtual bool enclose (const Geometry::Box &p) const = 0;
        // ...

        /**
         * Zwraca boundingBox w układzie współrzędnych swojego rodzica (?).
         */
        virtual Geometry::Box const &getBoundingBox () const = 0;

        virtual double getWidth () const = 0;
        virtual void setWidth (double) = 0;
        virtual double getHeight () const = 0;
        virtual void setHeight (double) = 0;

        /**
         * Każdy model ma swój środek. Stanowi on :
         * - Środek układu współrzędnych dla ewentualnych dzieci tego modelu.
         * - Środek obrotu (za pomocą setRotate).
         * - Środek skalowania (za pomocą setResize).
         * Punkt ten jest zwracany bez transformowania go za pomocą macierzy.
         * Ustawianie tego punktu jest sposobem na bezwzględne przesunięcie.
         */
        virtual Geometry::Point const &getOrigin () const = 0;
        virtual void setOrigin (Geometry::Point const &) = 0;

        //\}

/*--------------------------------------------------------------------------*/

        /**
         * Metod uruchamiana przez kontrolery (i ewentualnie przez widoki) przed
         * każdym odmalowaniem danego kontrolera.
         */
        virtual void update () = 0;

};


}

#	endif /* IMODEL_H_ */
