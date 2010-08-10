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

#include <Reflection.h>
#include <Pointer.h>
#include <List.h>
#include <collection/List.h>

#include "IWidget.h"
#include "mapping/IMapping.h"
#include "KeyboardEvent.h"
#include "MouseButtonEvent.h"
#include "MouseMotionEvent.h"
#include "TimerEvent.h"
#include "IObserver.h"
#include "tree/TreeMaster.h"

namespace Model {
class IModel;
}

//namespace View {
//class IView;
//class IWidget;
//}

/**
 * Sprawy związane z kontrolerami i klasami pomocniczymi.
 */
namespace Controller {

class IController;
typedef Reflection::List <Ptr <IController> > ControllerList;
_f (ControllerList)

/**
 * Base class of all controllers. Controllers are the "C" in MVC. There
 * are some OO rules broken here becuse Icontroller isnt really a pure interface.
 * It has non pure-virtual methods inherited from TreeMaster.
 * \ingroup Kontroler
 */
struct IController :
        public virtual Core::Object,
        public Util::TreeMaster <IController> {
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

        _e (IController)
};

}

#	endif /* ICONTROLLER_H_ */
