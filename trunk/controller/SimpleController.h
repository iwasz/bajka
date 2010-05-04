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

#include "IController.h"

namespace Controller {

class SimpleController : public IController {
public:

        __c (void)
        _b ("IController")

        SimpleController (Ptr <View::IWidget> widget = Ptr <View::IWidget> (),
                          Ptr <IMapping> mapping = Ptr <IMapping> ()) : widget (widget), mapping (mapping), render (true) {}
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
        void setModel (Ptr<Model::IModel> model) { this->model = model; }

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

}

#	endif /* SIMPLECONTROLLER_H_ */
