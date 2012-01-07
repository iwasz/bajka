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

#include "IObserver.h"
#include "mapping/IMapping.h"
#include "../base/tree/ITreeController.h"
#include "../events2/IObserver.h"

using Event::IObserver;

/**
 * Sprawy związane z kontrolerami i klasami pomocniczymi.
 */
namespace Controller {

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
        public virtual IObserver,
        public ITreeController {

        virtual ~IController () {}

        /// \todo After properties are set. To jest propozycja.
        virtual void init () = 0;

        /// Do the drawiang.
        virtual void draw () = 0;

/*------Properties----------------------------------------------------------*/

        virtual Ptr <View::IWidget> const &getWidget () = 0;
        virtual void setWidget (Ptr <View::IWidget> w) = 0;

        virtual Ptr <IMapping> getMapping () = 0;
};

_f (ControllerCollection)

}

#	endif /* ICONTROLLER_H_ */
