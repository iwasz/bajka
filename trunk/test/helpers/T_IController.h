/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ICONTROLLER_H_
#define ICONTROLLER_H_

#include "Pointer.h"
#include "IModelAware.h"
#include "ITreeController.h"

class IWidget;

/**
 * Interfejs kontrolerów. Ten interfejs dziedziczy z Base::ITreeController, czyli wszystkie
 * kontrolery w bajce mają możliwość zagnieżdżania jednego w drugim. Prócz tego w tym podstawowym
 * interfejsie są metody do pobierania modelu i widgetu.
 *
 * IController i Base::ITreeController są oddzielone od siebie, żeby zachować prostotę interfejsu
 * IController i nie zaciemniac jej metodami drzewiastymi. 
 * \inplace Kontroler
 */
struct T_IController : public Controller::ITreeController {

        virtual ~T_IController () {}

        virtual Ptr <View::IWidget> const &getWidget () = 0;
        virtual void setWidget (Ptr <View::IWidget> w) = 0;

/*--------------------------------------------------------------------------*/

        // Testowa
        virtual std::string const &getName () const = 0;
};

#	endif /* ICONTROLLER_H_ */
