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

#include "IObserver.h"
#include "mapping/IMapping.h"
#include "../base/tree/ITreeController.h"

namespace Model {
class IModel;
}

namespace View {
class IView;
class IWidget;
}

/**
 * Sprawy związane z kontrolerami i klasami pomocniczymi.
 */
namespace Controller {

class IController;
typedef Reflection::List <Ptr <IController> > ControllerList;
_f (ControllerList)

/**
 * Interfejs kontrolerów. Ten interfejs dziedziczy z Base::ITreeController, czyli wszystkie
 * kontrolery w bajce mają możliwość zagnieżdżania jednego w drugim. Prócz tego w tym podstawowym
 * interfejsie są metody do pobierania modelu i widgetu.
 *
 * IController i Base::ITreeController są oddzielone od siebie, żeby zachować prostotę interfejsu
 * IController i nie zaciemniac jej metodami drzewiastymi.
 * \ingroup Kontroler
 */
struct IController :
        public virtual Core::Object,
        public Base::ITreeController {
        __d

        virtual ~IController () {}

        /// \todo After properties are set. To jest propozycja.
        _m (init) virtual void init () = 0;

        /// Do the drawiang.
        virtual void draw () = 0;

/*------Properties----------------------------------------------------------*/

        _m (getWidget) virtual Ptr <View::IWidget> const &getWidget () = 0;
        _m (setWidget) virtual void setWidget (Ptr <View::IWidget> w) = 0;

        _m (getMapping) virtual Ptr <IMapping> getMapping () = 0;

        _m (getModel)
        _m (setModel)
        _e (IController)
};

}

#	endif /* ICONTROLLER_H_ */
