/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 21, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ICONTROLLER_H_
#define ICONTROLLER_H_

#include <Pointer.h>
#include <List.h>
#include <Object.h>

#include "IWidget.h"
#include "mapping/IMapping.h"
#include "KeyboardEvent.h"
#include "MouseButtonEvent.h"
#include "MouseMotionEvent.h"
#include "TimerEvent.h"

namespace Controller {

class IController;
typedef Core::List <Ptr <IController> > ControllerList;

struct IController : public Events::IObserver <Events::KeyboardEvent>,
                        public Events::IObserver <Events::MouseButtonEvent>,
                        public Events::IObserver <Events::MouseMotionEvent>,
                        public Events::IObserver <Events::TimerEvent>,
                        public Core::Object {

        virtual ~IController () {}

        /// After properties are set. TODO to jest propozycja.
        virtual void init () = 0;
        /// Do the drawiang.
        virtual void draw () = 0;

/*------Properties----------------------------------------------------------*/

        virtual Ptr<View::IWidget> getWidget () const = 0;
        virtual void setWidget (Ptr<View::IWidget> widget) = 0;

        virtual Ptr <IMapping> getMapping () const = 0;

        virtual Ptr<Model::IModel> getModel () const = 0;
        virtual void setModel (Ptr<Model::IModel> model) = 0;

/*------Containing----------------------------------------------------------*/

        /**
         * Every widget except the root has a parent.
         * @return Parent.
         */
        virtual Ptr <IController> getParent () const = 0;

        virtual ControllerList &getChildren () = 0;
        virtual const ControllerList &getChildren () const = 0;
        virtual void setChildren (const ControllerList &list) = 0;
        virtual void addChildren (const ControllerList &list) = 0;
        virtual void addChild (Ptr <IController> widget) = 0;

};

}

#	endif /* ICONTROLLER_H_ */
