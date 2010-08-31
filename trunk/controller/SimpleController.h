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
#include "tree/TreeMaster.h"
#include "geometry/Utils.h"

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
        public IController,
        public Event::AbstractObserver, // Eventy
        public Util::TreeMaster <IController> { // Zawieranie

public:

        __c (void)
        _b ("IController", "AbstractObserver")

        SimpleController (Ptr <View::IWidget> widget = Ptr <View::IWidget> (),
                          Ptr <IMapping> mapping = Ptr <IMapping> ()) :
                                  myHelper (this),
                                  widget (widget),
                                  mapping (mapping),
                                  render (true) {}

        virtual ~SimpleController () {}

/*------Drawing-------------------------------------------------------------*/

        /// \name Rysowanie
        //\{
        virtual void init ();
        virtual void draw ();
        virtual void doChildren ();

        bool getRender () const { return render; }
        void setRender (bool r) { render = r; }

        // Zmienić na View
        Ptr<View::IWidget> getWidget () const { return widget; }
        void setWidget (Ptr<View::IWidget> widget) { this->widget = widget; }

        Ptr<Model::IModel> getModel () const { return model; }
        void setModel (Ptr<Model::IModel> model);

        Ptr<IMapping> getMapping () const { return mapping; }
        _m (setMapping) void setMapping (Ptr<IMapping> mapping) { this->mapping = mapping; }
        //\}

/*------Containing----------------------------------------------------------*/

        /*
         * Implementacja, która działa z kontenerem (szablonowe nie działają z kontenerem).
         * TODO Kiedy kontener będzie obsługiwał zwykłe kolekcje STL (taki amm zamiar), to
         * w ogole będzie można wywalić tą metodę i zostawić tą z TreeMaster, która przyjmuje
         * zwykły wektor.
         */
        _m (setChildren)
        void setChildren (const ControllerList &list);

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

//        bool onTimer (Event::TimerEvent *e);

        //\}

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

        Ptr <View::IWidget> widget;
        Ptr <Model::IModel> model;
        Ptr <IMapping> mapping;
//        Ptr <IController> parent;

        bool render;

//        ControllerList children;

        _e (SimpleController)
};

}

#	endif /* SIMPLECONTROLLER_H_ */
