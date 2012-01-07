/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTMODEL_H_
#define ABSTRACTMODEL_H_

#include "geometry/Point.h"
#include "geometry/Box.h"
#include "TreeModel.h"

namespace Model {

/**
 * Implementacja typowych operacji na modelu. Implemenacja IModel, która zbiera
 * najczęściej używane operacje do kupy.
 * \ingroup Model
 */
class AbstractModel : public TreeModel {
public:
        __d

        virtual ~AbstractModel () {}

/*--------------------------------------------------------------------------*/

        /// \name Przekształcenia / układy współrzędznych
        //\{

        _m (setMove)    void setMove (const Geometry::Point &p);
                        Geometry::Point getMove () const;
                        void setPosition (const Geometry::Point &p);
        _M (void, setRotate, double)
                        void setRotate (double deg);
                        double getRotate () const;
                        void setRotate (double deg, const Geometry::Point &p);
                        void setRotateRad (double rad);
                        void setRotateRad (double rad, const Geometry::Point &p);
                        void setResize (double w, double h);
                        void setResize (double w, double h, Geometry::Point const &p);
        _m (setResizeW) void setResizeW (double w) { setResize (w, 1); }
        _m (setResizeH) void setResizeH (double h) { setResize (1, h); }

        double getRotateRad () const;
        double getResizeW () const;
        double getResizeH () const;

        virtual Geometry::AffineMatrix const &
        getMatrix () const { return matrix; }

        virtual Geometry::Point screenToModel (Geometry::Point const &) const;
        virtual Geometry::Point modelToScreen (Geometry::Point const &) const;

        // TODO To do zastanowienia.
        Geometry::AffineMatrix const &updateMatrixStack () const;

        //\}

/*--------------------------------------------------------------------------*/

        /// \name Kształt / pozycja
        //\{

        /**
         * Domyślna implementacja sprawdza, czy któreś z dzieci zawiera punkt p. Nie jest to
         * najszybsze rozwiązanie, dlatego należy albo nie dodawać żadnych dzieci (w kodzie
         * krytycznym), albo przedefiniować tą metodę.
         */
        virtual bool enclose (const Geometry::Point &p) const;

        /**
         * Domyślna implementacja zwraca bounding box obejmujący wszystkie swoje dzieci.
         * Oczywiście ta implementacja nie jest zbyt szybka, dlatego w klasach konkretnych
         * można ją przedefiniowac, tak, żeby tego nie robiła, albo wystarczy po prostu
         * nie dodawać żadnych dzieci do widgeta, i wtedy ta metoda nie spowolni działania
         * programu.
         */
        virtual Geometry::Box getBoundingBox () const;

        /**
         * Domyslna implementacja : zwraca punkt 0,0, czyli ten model ma środek tam gdzie rodzic.
         */
        virtual Geometry::Point const &getOrigin () const { static Geometry::Point p; return p; }

        //\}

/*--------------------------------------------------------------------------*/

        /// \name Update i przyległości
        //\{

        /**
         * Implementacja metody IModel::update. Ponieważ update jest wykonywana przez <b>każdym</b> uruchomieniem
         * IController::draw, ta implementacja deleguje zadanie do metody AbstractModel::doUpdate i uruchamia
         * ją za każdym razem lub tylko przy pierwszym wywołaniu. Zachowanie zależy od znaczników ustawianych za
         * pomocą metod AbstractModel::getUpToDate i AbstractModel::getAlwaysUpdate.
         */
        void update ();

        /**
         * AbstractModel::update dleguje swoje zadanie wlaśnie do tej metody, przy czym uruchamia ją jeden raz
         * lub za każdym razem, zależnie od konfiguracji.
         */
        virtual void doUpdate () {}

        /// Czy update zostało wykonane przynajmniej 1 raz?
        bool getUpToDate () const { return upToDate; }
        /// Czy AbstractModel::doUpdate wykonywać za każdym razemkiedy uruchomione jest AbstractModel::update?
        bool getAlwaysUpdate () const { return upToDate; }
        /// Czy AbstractModel::doUpdate wykonywać za każdym razemkiedy uruchomione jest AbstractModel::update?
        _m (setAlwaysUpdate) void setAlwaysUpdate (bool b) { alwaysUpdate = b; }

        //\}

protected:

        AbstractModel ();

protected:

        // Relative to root-element
        Geometry::AffineMatrix matrix;

private:

        mutable Geometry::AffineMatrix matrixStack;
//        mutable Geometry::Point tmpPoint;
        bool upToDate;
        bool alwaysUpdate;

        _e (AbstractModel)
};

/**
 * To jest propozycja - chodzi o to, że to jest model, który nie ma kształtu, ani nawet
 * pozycji w przesytrzeni - on tylko umożliwia transformacje swoich dzieci, czyli obrót
 * całości, przesunięcie o jakiś czas w lewo/prawo.
 *
 * Nie ma kształtu, ale ma środek układu współrzędnych. To jest potrzebne do obracania
 * i rozmieszczania dzieci.
 */
struct Shapeless : public AbstractModel {
        __c (void)
        _b ("AbstractModel")

        virtual ~Shapeless () {}

//        /// Zwraca 0. AbstractModel sam w sobie ma wielkość punktu.
//        virtual double getWidth () const { return 0.0; }
//        /// Zwraca 0. AbstractModel sam w sobie ma wielkość punktu.
//        virtual double getHeight () const { return 0.0; }
//        /// Pusta operacja
//        virtual void setWidth (double d) {}
//        /// Pusta operacja
//        virtual void setHeight (double d) {}

        virtual bool enclose (const Geometry::Point &p) const { return false; }

        /// Pudełko o zerowym rozmiarze.
        virtual Geometry::Box getBoundingBox () const { return Geometry::Box (); }

        /// Zawsze zwraca punkt (0, 0).
        Geometry::Point const &getOrigin () const { static Geometry::Point origin; return origin; }

private:

        _e (Shapeless)
};

} // namespace

#	endif /* ABSTRACTMODEL_H_ */
