/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IVIEW_H_
#define IVIEW_H_

#include <core/Object.h>

namespace Event {
class UpdateEvent;
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

        virtual void preUpdate (Model::IModel *, Event::UpdateEvent *e) = 0;
        virtual void update (Model::IModel *, Event::UpdateEvent *e) = 0;
        virtual void postUpdate (Model::IModel *, Event::UpdateEvent *e) = 0;

        /**
         * Stany widoku - jeśli brak, to olać.
         */
        virtual void setState (int) = 0;
        virtual int getState () const = 0;

        /**
         * Nieobowiązkowa metoda, która określa rozmiar danego widgeta. Taki rozmiar
         * moze być wykorzystany w modelu do automatycznego określenia rozmiaru modelu
         * na podstawie jego widoku. Tylko niektóre widoki implementują te metody, bo
         * tylko niektóre ustalają swój rozmiar same (obrazek Image i tekst Text).
         * Większość widoków czerpie informację o swoim rozmiarze z modelu, a nie na
         * odwrót.
         */
        virtual double getWidthHint () const = 0;
        virtual double getHeightHint () const = 0;

};

} /* namespace View */

#	endif /* IVIEW_H_ */
