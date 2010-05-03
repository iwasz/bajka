/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 21, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SIMPLECONTROLLER_H_
#define SIMPLECONTROLLER_H_

#include <Reflection.h>
#include "IController.h"

namespace Controller {

class SimpleController : public IController {
public:

        __c (void)

        SimpleController (Ptr <View::IWidget> widget = Ptr <View::IWidget> (),
                          Ptr <IMapping> mapping = Ptr <IMapping> ()) : widget (widget), mapping (mapping), render (true) {}
        virtual ~SimpleController () {}

/*------Drawing-------------------------------------------------------------*/

        _m (init) virtual void init ();
        virtual void draw ();
        virtual void doChildren ();

        bool getRender () const { return render; }
        void setRender (bool r) { render = r; }

        // Zmienić na View
        _m (getWidget) Ptr<View::IWidget> getWidget () const { return widget; }
        _m (setWidget) void setWidget (Ptr<View::IWidget> widget) { this->widget = widget; }

        _m (getModel) Ptr<Model::IModel> getModel () const { return model; }
        _m (setModel) void setModel (Ptr<Model::IModel> model) { this->model = model; }

        _m (getMapping) Ptr<IMapping> getMapping () const { return mapping; }
        _m (setMapping) void setMapping (Ptr<IMapping> mapping) { this->mapping = mapping; }

/*------Containing----------------------------------------------------------*/

        virtual Ptr <IController> getParent () const { return parent; }

        virtual ControllerList &getChildren () { return children; }
        virtual const ControllerList &getChildren () const { return children; }
        _m (setChildren) virtual void setChildren (const ControllerList &list) { children = list; }
        virtual void addChildren (const ControllerList &list) { children.addAll (list); }
        virtual void addChild (Ptr <IController> widget) { children.add (widget); }

/*------Events--------------------------------------------------------------*/

        virtual void update (const Events::IObservable <Events::KeyboardEvent> &observable, const Events::KeyboardEvent &event) {}
        virtual void update (const Events::IObservable <Events::MouseButtonEvent> &observable, const Events::MouseButtonEvent &event) {}
        virtual void update (const Events::IObservable <Events::MouseMotionEvent> &observable, const Events::MouseMotionEvent &event) {}
        virtual void update (const Events::IObservable <Events::TimerEvent> &observable, const Events::TimerEvent &event) {}

private:

        Ptr <View::IWidget> widget;
        Ptr <Model::IModel> model;

        Ptr <IMapping> mapping;

        bool render;
        Ptr <IController> parent;
        ControllerList children;

        _e (SimpleController)
};

// TODO Do usunięcia, kiedy variant będzie zwracał dobre type_info
class TmpController : public SimpleController {
public:
        __c (void)
        _b ("SimpleController")

        virtual ~TmpController () {}

        _m (setModel2) void setModel2 (Ptr <Model::Image> m) { model = m; setModel (m); }
        _m (getModel2) Ptr <Model::Image> getModel2 () const { return model; }

private:

        Ptr <Model::Image> model;

        _e (TmpController)
};

}

#	endif /* SIMPLECONTROLLER_H_ */
