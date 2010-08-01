/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SIMPLECONTROLLER_H_
#define SIMPLECONTROLLER_H_

#include "IController.h"
#include "AbstractObserver.h"

namespace Controller {

/**
 *
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
 */
class SimpleController : public IController, public Event::AbstractObserver {
public:

        __c (void)
        _b ("IController")
        _m (setBitMask)

        SimpleController (Ptr <View::IWidget> widget = Ptr <View::IWidget> (),
                          Ptr <IMapping> mapping = Ptr <IMapping> ()) :
                                  myHelper (this),
                                  widget (widget),
                                  mapping (mapping),
                                  render (true) {}

        virtual ~SimpleController () {}

/*------Drawing-------------------------------------------------------------*/

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

/*------Containing----------------------------------------------------------*/

        virtual Ptr <IController> getParent () const { return parent; }

        virtual ControllerList &getChildren () { return children; }
        virtual const ControllerList &getChildren () const { return children; }
        virtual void setChildren (const ControllerList &list) { children = list; }
        virtual void addChildren (const ControllerList &list) { children.addAll (list); }
        virtual void addChild (Ptr <IController> widget) { children.add (widget); }

/*------Events--------------------------------------------------------------*/

        /**
         * Tu zaimplementowane jest przekazywanie eventu wgłąb struktury
         * drzewiastej. Najpierw przetwarza go rodzic, potem jego potomkowie,
         * potem potomkowie potomków etc. Jeśli któraś metoda obsługi zwróci
         * false, to łańcuch jest perywany.
         * @param event
         * @return
         */
        bool onEvent (Event::IEvent *event);

        bool onMouseMotion (Event::MouseMotionEvent *e);
        bool onMouseOver (Event::MouseMotionEvent *e);
        bool onMouseOut (Event::MouseMotionEvent *e);

        bool onTimer (Event::TimerEvent *e);

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
        Ptr <IController> parent;

        bool render;

        ControllerList children;

        _e (SimpleController)
};

}

#	endif /* SIMPLECONTROLLER_H_ */
