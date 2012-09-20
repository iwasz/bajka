/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_IMODEL_H_
#define BAJKA_IMODEL_H_

#include <vector>
#include <map>
#include <core/Object.h>
#include "util/ReflectionMacros.h"
#include "view/IView.h"
#include "controller/IController.h"
#include "geometry/Box.h"
#include "geometry/AffineMatrix.h"
#include "layout/IGroupProperties.h"

namespace Event {
class UpdateEvent;
}

/**
 * Modele
 */
namespace Model {

/**
 * Interfejs modelu. Obiekty graficzne w bajce składają się z M-V-C. Model jest głównym
 * elementem tej trójki, gdyż spina widok i kontroler oraz inne modele ze sobą. Model
 * Zawiera
 * - funkcjonalność opisującą element graficzny (jego cechy),
 * - przekształcenia modelu (affine transformations),
 * - zawieranie jednych modeli przez inne (drzewo modeli)
 *
 */
struct IModel : public virtual Core::Object {

        virtual ~IModel () {}

        /**
         * Rysuje obiekt. Model jest centralnym z trzech obiektów w M-V-C, dlatego także
         * ma metodę update, ktora wywołuje metody widoku i kontrolera. Najważniejsza
         * implementacja tej metody znajduje się w Model::AbstractModel. Rysuje ona
         * obiekt graficzny (model) z uwzględnieniem zagnieżdżonej i drzewiastej struktury
         * modeli.
         */
        virtual void update (Event::UpdateEvent *e) = 0;

        /**
         * \name Transformacje.
         */
        ///@{
        /**
         * Przesunięcie. Większość kształtów sama w sobie jest jakoś
         * umiejscowiona w przestrzeni. Na prztykład Box jest zdefiniowany
         * za pomocą 2 wierzchołków, które mogą być w dowolnym miejscu.
         * Jednak translate jest dodatkowym przesunięciem, które nie
         * modyfikuje tych wierzchołków, a jedynie powoduje ich transformację
         * przez macierz przesunięcia.
         */
        virtual Geometry::Point getTranslate () const = 0;

        /**
         * Ustaw przesunięcie.
         */
        virtual void setTranslate (Geometry::Point const &translate) = 0;

        /**
         * Pobiera kąt obrotu.
         */
        virtual double getAngle () const = 0;

        /**
         * Ustawia kąt obrotu.
         */
        virtual void setAngle (double a) = 0;

        /**
         * Pobiera skalę.
         */
        virtual double getScale () const = 0;

        /**
         * Ustawia skalę.
         */
        virtual void setScale (double a) = 0;

        /**
         * Punkt względem którego wykonywane są obroty i skalowanie.
         */
        virtual Geometry::Point getCenter () const = 0;
        virtual void setCenter (Geometry::Point const &p) = 0;

        /**
         * Macierz przekształceń.
         */
        virtual Geometry::AffineMatrix getMatrix () const = 0;
        ///@}

/*------searching-----------------------------------------------------------*/

        /**
         * \name Kompozycja modeli.
         * Czyli to drzewo modeli.
         */
        ///@{
        /**
         * Znajduje model w zadanym punkcie. Zaczyna przeszukiwanie od dzieci,
         * i idzie w dół, jeśli nie znajdzie. W ten sposób możliwe, że zwróci
         * samego siebie, jeśli żadne jego dziecko nie znajduje się w podanym
         * punkcie, albo ten model nie ma żadnych dzieci. Współrzędne punktu p
         * podajemy oczywiście w układzie tego (this) modelu.
         */
        virtual IModel *findContains (Geometry::Point const &p) = 0;

        /**
         * Czy podany punkt jest wewnątrz kształtu.
         * @param p  W układzie rodzica.
         * @return
         */
        virtual bool contains (Geometry::Point const &p) const = 0;

        /**
         * Pobiera rodzica tego modelu. Zwraca NULL, jeśli nie ma rodzica (czyli jeśli root).
         */
        virtual IModel *getParent () = 0;

        /**
         * Także callback; TODO jedna metoda zamiast dwóch byłaby lepsza.
         * @param m
         */
        virtual void setParent (IModel *m) = 0;
        virtual void onParentSet (IModel *m) = 0;
        ///@}

/*------additional-functionalities------------------------------------------*/

        virtual View::IView *getView () = 0;
        virtual void setView (View::IView *v) = 0;

        virtual Controller::IController *getController () = 0;
        virtual void setController (Controller::IController *c) = 0;

/*------layout--------------------------------------------------------------*/

        virtual IGroupProperties const *getGroupProps () const = 0;
        virtual void setGroupProps (IGroupProperties *l) = 0;

/*------runtime type information--------------------------------------------*/

        virtual bool isBox () const = 0;
        virtual bool isGroup () const = 0;

        /**
         * Bounding box w układzie rodzica.
         * @return
         */
        virtual Geometry::Box getBoundingBox () const = 0;
        virtual Geometry::Box getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const = 0;
};

/**
 *
 */
typedef std::vector <IModel *> ModelVector;
g_ (ModelVector)

typedef std::map <std::string, IModel *> ModelMap;
g_ (ModelMap)

} /* namespace Geometry */

#	endif /* IMODEL_H_ */
