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
#include <Reflection.h>
#include <collection/List.h>

#include "IWidget.h"
#include "mapping/IMapping.h"
#include "KeyboardEvent.h"
#include "MouseButtonEvent.h"
#include "MouseMotionEvent.h"
#include "TimerEvent.h"
#include "IObserver.h"

namespace Controller {

class IController;
typedef Reflection::List <Ptr <IController> > ControllerList;
_f (ControllerList)

/**
 *
 */
struct IController : public virtual Core::Object {
        __d

        virtual ~IController () {}

        /// After properties are set. TODO to jest propozycja.
        _m (init) virtual void init () = 0;
        /// Do the drawiang.
        virtual void draw () = 0;

/*------Properties----------------------------------------------------------*/

        _m (getWidget) virtual Ptr<View::IWidget> getWidget () const = 0;
        _m (setWidget) virtual void setWidget (Ptr<View::IWidget> widget) = 0;

        _m (getMapping) virtual Ptr <IMapping> getMapping () const = 0;

        _m (getModel) virtual Ptr<Model::IModel> getModel () const = 0;
        _m (setModel) virtual void setModel (Ptr<Model::IModel> model) = 0;

/*------Containing----------------------------------------------------------*/

        /**
         * Every widget except the root has a parent.
         * @return Parent.
         */
        virtual Ptr <IController> getParent () const = 0;

        virtual ControllerList &getChildren () = 0;
        virtual const ControllerList &getChildren () const = 0;
        _m (setChildren) virtual void setChildren (const ControllerList &list) = 0;
        virtual void addChildren (const ControllerList &list) = 0;
        virtual void addChild (Ptr <IController> widget) = 0;

        _e (IController)
};

}

#	endif /* ICONTROLLER_H_ */
