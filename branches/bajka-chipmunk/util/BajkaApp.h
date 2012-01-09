/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKAAPP_H_
#define BAJKAAPP_H_

#include "../model/geometry/Geometry.h"
#include <Reflection.h>
#include "../model/geometry/Point.h"
#include <chipmunk.h>

//using Geometry::AffineMatrix;
//#include "IDispatcher.h"

//namespace Controller {
//class IController;
//}

namespace Util {

struct OperationNotSupportedException : public std::exception {

        virtual ~OperationNotSupportedException () throw () {}
        virtual const char* what() const throw () { return "Bajka not nupported operation"; }

};

}

namespace Model {
class IModel;
}

namespace View {

/**
 * Widok.
 */
struct IView : public Core::Object {

        virtual ~IView () {}

        virtual void preUpdate (Model::IModel *) = 0;
        virtual void update (Model::IModel *) = 0;
        virtual void postUpdate (Model::IModel *) = 0;

};

class Widget : public IView {
public:

        Widget () : visible (true) {}
        virtual ~Widget () {}

        virtual void preUpdate (Model::IModel *);
        virtual void postUpdate (Model::IModel *);

        bool getVisible () const { return visible; }
        /*_m (setVisible) */void setVisible (bool v) { visible = v; }

private:

        bool visible;

};


/**
 * Rysuje prostokąt.
 * \ingroup View
 */
class Rectangle : public Widget {
public:
//        __c (void)
//        _b ("AbstractWidget")

        virtual ~Rectangle () {}

        virtual void update (Model::IModel *model);

//// Żeby nie trzeba było kastowac modelu na box w pochodnych.
//protected:
//
//        Model::Box *box;
//        _e (Rectangle)
};

/**
 * Rysuje prostokąt.
 * \ingroup View
 */
class Circle : public Widget {
public:

        virtual ~Circle () {}
        virtual void update (Model::IModel *model);
};

}


namespace Controller {

/**
 *
 */
struct IController : public Core::Object {

        virtual ~IController () {}

        virtual bool preUpdate (Model::IModel *m, View::IView *v) = 0;
        virtual bool update (Model::IModel *m, View::IView *v) = 0;
        virtual bool postUpdate (Model::IModel *m, View::IView *v) = 0;

};

struct EmptyController : public IController {

        virtual ~EmptyController () {}

        virtual bool preUpdate (Model::IModel *m, View::IView *v) {}
        virtual bool update (Model::IModel *m, View::IView *v) {}
        virtual bool postUpdate (Model::IModel *m, View::IView *v) {}

};

}

namespace Model {

typedef std::vector <IModel *> ModelVector;

struct IModel : public Core::Object {

        virtual ~IModel () {}

        /**
         * Pozycja tego modelu we współrzędnych rodzica. Jest to pozycja
         * pewnego punktu w tym modelu (na przykład środek okręgu).
         */
        virtual Geometry::Point getPosition () const = 0;
        virtual void setPosition (Geometry::Point const &position) = 0;

        virtual double getAngle () const = 0;
        virtual void setAngle (double a) = 0;

        virtual double const *getMatrix () const = 0;

/*--------------------------------------------------------------------------*/

        virtual bool update () = 0;

/*--------------------------------------------------------------------------*/

        virtual IModel *getParent () = 0;

        /**
         * Także callback;
         * @param m
         */
        virtual void setParent (IModel *m) = 0;
        virtual void parentCallback (IModel *m) = 0;

        virtual ModelVector &getChildren () = 0;
        virtual void setChildren (ModelVector const &) = 0;
        virtual void addChild (IModel *m) = 0;
        virtual ModelVector::iterator begin () = 0;
        virtual ModelVector::iterator end () = 0;

/*--------------------------------------------------------------------------*/

        virtual View::IView *getView () = 0;
        virtual void setView (View::IView *v) = 0;

        virtual Controller::IController *getController () = 0;
        virtual void setController (Controller::IController *c) = 0;

};

class AbstractModel : public IModel {
public:

        AbstractModel () : parent (0), view (0), controller (0) {}
        virtual ~AbstractModel () {}

        virtual bool update ();

/*--------------------------------------------------------------------------*/

        IModel *getParent () { return parent; }
        void setParent (IModel *m) { parent = m; }
        void parentCallback (IModel *m) {}

        ModelVector &getChildren () { return children; }
        // Todo pętla setParent
        void setChildren (ModelVector const &c) { children = c; }
        void addChild (IModel *m) { children.push_back (m); m->setParent (this); m->parentCallback (this); }
        ModelVector::iterator begin () { return children.begin (); }
        ModelVector::iterator end () { return children.end (); }

/*--------------------------------------------------------------------------*/

        View::IView *getView () { return view; }
        void setView (View::IView *v) { view = v; }

        Controller::IController *getController () { return controller; }
        void setController (Controller::IController *c) { controller = c; }

private:

        IModel *parent;
        ModelVector children;
        View::IView *view;
        Controller::IController *controller;

};


class CPModel : public AbstractModel {

};

class CPSpace : public CPModel {
public:

        CPSpace ();
        virtual ~CPSpace ();

        static cpSpace *getSpace () { return space; }

/*--------------------------------------------------------------------------*/

        Geometry::Point getPosition () const { return Geometry::Point (); }
        void setPosition (Geometry::Point const &position) { throw Util::OperationNotSupportedException ();  }

        double getAngle () const { return 0; }
        void setAngle (double a) { throw Util::OperationNotSupportedException ();  }

        double const *getMatrix () const;

/*--------------------------------------------------------------------------*/

        Geometry::Vector getGravity () const;
        void setGravity (Geometry::Vector const &g);

private:

        static cpSpace *space;

};

class CPBody : public CPModel {
public:

        CPBody ();
        virtual ~CPBody ();

        Geometry::Point getPosition () const;
        void setPosition (Geometry::Point const &position);

        double getAngle () const;
        void setAngle (double a);

        double const *getMatrix () const;

/*--------------------------------------------------------------------------*/

        double getMass () const;
        void setMass (double m);

        double getInertia () const;
        void setInertia (double i);
        void addInertia (double i);

        cpBody *getBody () { return body; }
        cpBody const *getBody () const { return body; }

private:

        cpBody *body;


};

class CPRigidBody : public CPBody {

};

class CPStaticBody : public CPRigidBody {

};

class CPShape : public CPModel {
public:

        CPShape () : shape (0) {}
        virtual ~CPShape ();

        virtual double calculateInertia (double mass) const = 0;
        virtual void parentCallback (IModel *m);

        double const *getMatrix () const;

protected:

        cpShape *shape;

};

class CPCircle : public CPShape {
public:

        CPCircle ();
        virtual ~CPCircle () {}

        double getRadius () const;
        void setRadius (double r);

        Geometry::Point getPosition () const;
        void setPosition (Geometry::Point const &p);

        double getAngle () const { return 0; }
        void setAngle (double) {}

        /*--------------------------------------------------------------------------*/

        double calculateInertia (double mass) const;
        virtual void parentCallback (IModel *m);

private:

        double radius;
        Geometry::Point position;

};

class CPSegment : public CPShape {

};

class CPPolygon : public CPShape {

};

class CPBox : public CPPolygon {
public:

//        CPBox () : width (0), height (0) {}
//
//        double getWidth () const { return width; }
//        void setWidth (double w) { width = w; }
//
//        double getHeight () const { return height; }
//        void setHeight (double h) { height = h; }
//
//private:
//
//        double width;
//        double height;

};

class Box : public AbstractModel {
public:

        Box (double x, double y, double w, double h) : position (x, y), width (w), height (h) {}
        Box () : width (0), height (0) {}
        virtual ~Box () {}

        Geometry::Point getPosition () const { return position; }
        void setPosition (Geometry::Point const &p) { position = p; }

        // TODO
        double getAngle () const { throw 1; }
        void setAngle (double a) { matrix.rotate (a); }

        double const *getMatrix () const { return matrix.data ().begin (); }

        double getWidth () const { return width; }
        void setWidth (double w) { width = w; }

        double getHeight () const { return height; }
        void setHeight (double h) { height = h; }

private:

        Geometry::Point position;
        double width;
        double height;
        Geometry::AffineMatrix matrix;

};

}

namespace Util {

/*
 * Ta klasa jest tylko po to, żeby ułatwoć stosowanie bajki z kontenerem.
 * Otóż kolejność pracy programu musi być następująca:
 * - Utworzenie BajkaConfig.
 * - Ustawienie jej pól.
 * - Uruchomienie init ().
 * Treaz OpenGL i SDL są zainicjowane, można dodawać obiekty. I dopero teraz
 * można uruchomić pętlę programu:
 * - BajkaApp run.
 * INICJUJE OpenGL!
 */
class BajkaConfig {
public:
        __c (void)

        BajkaConfig ();

/*--------------------------------------------------------------------------*/

        _m (init) void init ();

/*------access methods------------------------------------------------------*/

        bool getFullScreen () const { return fullScreen; }
        _m (setFullScreen) void setFullScreen (bool fullScreen) { this->fullScreen = fullScreen; }

        int getResX () const { return resX; }
        _m (setResX) void setResX (int resX) { this->resX = resX; }

        int getResY () const { return resY; }
        _m (setResY)  void setResY (int resY) { this->resY = resY; }

        const std::string &getWindowCaption () const { return windowCaption; }
        _m (setWindowCaption) void setWindowCaption (const std::string &windowCaption) { this->windowCaption = windowCaption; }

private:

        bool fullScreen;
        int resX;
        int resY;
        std::string windowCaption;

        _e (BajkaConfig)
};

/**
 * Bajka application. It is bound to OpenGL and is not meant to
 * be used with any other technologies (i.e. DirectX). Implements
 * the main loop.
 *
 * CR : Kiedyś kiedyś : umożliwić stosowanie czegoś innego niż SDL.
 * Można z tego dziedziczyć i dodawać swoje metody game-specific.
 */
class BajkaApp : public Core::Object {
public:

       __c (void)

       BajkaApp () /*: dispatchers (new Event::DispatcherList)*/ {}
       virtual ~BajkaApp () {}

       _m (loop) void loop ();
       _m (debug) void debug (Core::String const &);
       _m (debug) void destroy ();

/*--------------------------------------------------------------------------*/

       /**
        * Wykonywane w głównej pętli PO wykonaniu wszystkich procedur obsługi eventow.
        * Domyślnie ta metoda jest pusta, ale można ją oczywiście przedefiniować.
        */
       virtual void afterEvents () {}

       Ptr <BajkaConfig> getConfig () const { return config; }
       _m (setConfig) void setConfig (Ptr <BajkaConfig> b) { config = b; }

       /// Głowny model.
       Ptr <Model::IModel> getModel () const { return model; }

       /**
        * 1. Odłącza poprzedni rootControloer od dispatcherów.
        * 2. Ustawia główny kontroler.
        * 3. Podłącza ten nowy do wszystkich dispatcherów.
        */
       _m (setModel) void setModel (Ptr <Model::IModel> model);
//
//       Ptr <Event::DispatcherList> getDispatchers () const { return dispatchers; }
//       _m (setDispatchers) void setDispatchers (Ptr <Event::DispatcherList> d) { dispatchers = d; }

/*--------------------------------------------------------------------------*/

//       /// Podłącza o do wszystkich dispatcherów.
//       void connect (Ptr <Event::IObserver> o);
//       /// Odłącza o od wszystkich dispatcherów.
//       void disconnect (Ptr <Event::IObserver> o);

private:

       Ptr <BajkaConfig> config;
       Ptr <Model::IModel> model;
//       Ptr <Event::DispatcherList> dispatchers;

       _e (BajkaApp)
};

} // nam

#	endif /* BAJKAAPP_H_ */
