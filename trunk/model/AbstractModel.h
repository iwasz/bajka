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

/*------affine-transformations----------------------------------------------*/

        _m (setMove)    virtual void setMove (const Geometry::Point &p);
        _m (setRotate)  virtual void setRotate (double r);
                        virtual void setResize (double w, double h);
        _m (setResizeW) virtual void setResizeW (double w) { setResize (w, 1); }
        _m (setResizeH) virtual void setResizeH (double h) { setResize (1, h); }

        virtual Geometry::AffineMatrix const &
        getMatrix () const { return matrix; }

        virtual Geometry::Point const &screenToModel (Geometry::Point const &) const;
        virtual Geometry::Point const &modelToScreen (Geometry::Point const &) const;

        // TODO To do zastanowienia.
        Geometry::AffineMatrix const &updateMatrixStack () const;

        /// Zwraca 0. AbstractModel sam w sobie ma wielkość punktu.
        virtual double getWidth () const { return 0.0; }

        /// Zwraca 0. AbstractModel sam w sobie ma wielkość punktu.
        virtual double getHeight () const { return 0.0; }
        virtual void setWidth (double d) {}
        virtual void setHeight (double d) {}

        /**
         * AbstractModel sam w sobie ma wielkość punktu, więc nigdy nic nie jest w jego środku, ale
         * deleguje jeszcze sprawdzenie do swoich dzieci. Jeżeli ktorekolwiek z nich zwróci prawdę,
         * to ta metoda także zwrac prawdę.
         */
        virtual bool enclose (const Geometry::Point &) const;

        /// Pudełko o zerowym rozmiarze.
        virtual Geometry::Box const &getBoundingBox () const { static Geometry::Box b; return b; }

/*--------------------------------------------------------------------------*/

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

protected:

        AbstractModel ();

protected:

        // Relative to root-element
        Geometry::AffineMatrix matrix;

private:

        mutable Geometry::AffineMatrix matrixStack;
        mutable Geometry::Point tmpPoint;
        bool upToDate;
        bool alwaysUpdate;

        _e (AbstractModel)
};

/**
 * To jest propozycja - chodzi o to, że to jest model, który nie ma kształtu, ani nawet
 * pozycji w przesytrzeni - on tylko umożliwia transformacje swoich dzieci, czyli obrót
 * całości, przesunięcie o jakiś czas w lewo/prawo.
 *
 * PS, to czy nie ma pozycji, czy ma być, to jest do ustalenia - bo ja cały czas nie wiem!
 */
struct Shapeless : public AbstractModel {
        __c (void)
        _e (Shapeless)
};

} // namespace

#	endif /* ABSTRACTMODEL_H_ */
