/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SIMPLECONTROLLER_H_
#define SIMPLECONTROLLER_H_

#include <stack>
#include "IController.h"
#include "AbstractObserver.h"
#include "geometry/Utils.h"
#include "KeyboardEvent.h"
#include "MouseButtonEvent.h"
#include "MouseMotionEvent.h"
#include "TimerEvent.h"
#include "AbstractController.h"

// Kiedy nie ma tych nagłówków, kontener nie chce ładować klas.
#include "IWidget.h"
#include "IModel.h"

//namespace Geometry {
//class AffineMatrix;
//typedef std::stack <AffineMatrix> AffineMatrixStack;
//}

namespace Controller {

/**
 * Kontekst typu Event::IEventContext, który zawiera stos macierzy
 * przekszatłceń dla eventów. Możliwe, że to będzie zastąpione przez
 * stos macierzy bezpośrednio w modelu.
 * \ingroup Kontroler
 */
class SimpleControllerContext : public Event::IEventContext {
public:

        virtual ~SimpleControllerContext () {}

        /**
         * Odkłada na stosie macierz mnożąc ją przez poprzednią. Czyli
         * Odkładając kolejno macierze m1, m2, m3 stos będzie wyglądał :
         * m1 x m2 x m3
         * m1 x m2
         * m1
         * @param m
         */
        void pushMatrix (const Geometry::AffineMatrix &m);
        void popMatrix ();
        const Geometry::AffineMatrix &topMaptrix () const;

private:

        Geometry::AffineMatrixStack stack;
};


/**
 * Implementuje:
 * - zawieranie
 * - obsługę eventów w drzewie
 * - odfiltrowywanie eventów, które nie są w obszarze.
 * \ingroup Kontroler
 */
class SimpleController :
        public Event::AbstractObserver, // Eventy
        public AbstractController { // Zawieranie
public:

        __c (void)
        _b ("TreeController", "AbstractObserver")

        SimpleController (Ptr <View::IWidget> w = Ptr <View::IWidget> (),
                          Ptr <IMapping> mapping = Ptr <IMapping> ()) :
                                  AbstractController (w),
                                  myHelper (this),
                                  mapping (mapping),
                                  render (true) {}

        virtual ~SimpleController () {}

/*------Drawing-------------------------------------------------------------*/

        /// \name Rysowanie
        //\{

        virtual void init ();

        /**
         * Zwyczajnie deleguje rysowanie do widgetu. Implementacja tej metody wygląda
         * poprostu jak widget->draw (); Rysowaniem swoich dzieci zajmuje się już sam
         * widget
         */
        virtual void draw ();

        bool getRender () const { return render; }
        void setRender (bool r) { render = r; }

        Ptr<IMapping> getMapping () { return mapping; }
        _m (setMapping) void setMapping (Ptr<IMapping> mapping) { this->mapping = mapping; }

        //\}

/*------Containing----------------------------------------------------------*/

        /// \name Zawieranie
        //\{

        /*
         * Implementacja, która działa z kontenerem (szablonowe nie działają z kontenerem).
         * TODO Kiedy kontener będzie obsługiwał zwykłe kolekcje STL (taki mam zamiar), to
         * w ogole będzie można wywalić tą metodę i zostawić tą z TreeMaster, która przyjmuje
         * zwykły wektor.
         */
        _m (setChildren)

/*------Events--------------------------------------------------------------*/


        /// \name Eventy
        //\{

        /**
         * Tu zaimplementowane jest przekazywanie eventu wgłąb struktury
         * drzewiastej. Najpierw przetwarza go rodzic, potem jego potomkowie,
         * potem potomkowie potomków etc. Jeśli któraś metoda obsługi zwróci
         * false, to łańcuch jest perywany.
         * @param event
         * @return
         */
        virtual bool onEvent (Event::IEvent *event);

        virtual bool onMouseMotion (Event::MouseMotionEvent *e);
        virtual bool onMouseOver (Event::MouseMotionEvent *e);
        virtual bool onMouseOut (Event::MouseMotionEvent *e);

        //\}
/*--------------------------------------------------------------------------*/

        virtual void setModel (Ptr <Model::IModel> m);

private:

        /**
         * Zadaniem tego obserwatora jest odrzucenie eventów, kiedy kursor
         * myszy nie znajduje się w obszarze tengo widgetu. Możliwe, że
         * będzie też spradzać fokus przy eventach związanych z klawiaturą.
         */
        class ObserverHelper : public Event::IObserver {
        public:

                friend class SimpleController;

                ObserverHelper (SimpleController *c) : myController (c), myModel (NULL), pointerInside (false) {}

                bool onEvent (Event::IEvent *event) { return true; }
                bool acceptEvent (Event::IEvent *event) const { return true; }
                bool getActive () const { return true; }

                bool onButtonPress (Event::ButtonPressEvent *e);
                bool onButtonRelease (Event::ButtonReleaseEvent *e);
                bool onMouseMotion (Event::MouseMotionEvent *e);
                bool onKeyDown (Event::KeyDownEvent *e);
                bool onKeyUp (Event::KeyUpEvent *e);
                bool onTimer (Event::TimerEvent *e);
                bool onQuit (Event::QuitEvent *e);

        private:

                bool checkArea (Event::MouseEvent *e);

        private:

                SimpleController *myController;
                Model::IModel *myModel;
                bool pointerInside;
        };

        ObserverHelper myHelper;

private:

        Ptr <IMapping> mapping;
        bool render;

        _e (SimpleController)
};

}

#	endif /* SIMPLECONTROLLER_H_ */
