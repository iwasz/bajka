/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 15, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IVIEW_H_
#define IVIEW_H_

#include <List.h>
#include <Object.h>

/**
 * Klasy generujące widoki.
 */
namespace View {

/**
 * Interfejs dowlonej rzeczy, którą da się narysować. Mogą to być przeróżne elementy graficzne, sekwencje
 * animacji, przejścia i inne.
 * \ingroup View
 */
struct IView : public virtual Core::Object {

        virtual ~IView () {}

        /*
         * TODO to jest propozycja wprowadzona w celu rozwiązania konkretnych
         * problemów (nie odświeżanie się w kontenerze, problem z kolejnością
         * ustawianai i inicjowania property).
         */
        virtual void init () = 0;
        virtual void draw () = 0;
        virtual void doDraw () = 0;// Zamiast draw

        virtual void preDraw () = 0;
        virtual void postDraw () = 0;
};

} // nam

#	endif /* IVIEW_H_ */
