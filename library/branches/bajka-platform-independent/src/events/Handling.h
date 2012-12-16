/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKAHANDLING_H_
#define BAJKAHANDLING_H_

namespace Event {

        /**
         * Informacja w jaki sposób metody kontrolerów obsłużyły event.
         */
        enum Handling {
                IGNORE = 0x00, /** < Ta metoda nie obsłużyła eventu. Zignorowała go, lub intencją programisty było, żeby system tak myślał. */
                PASS = 0x01,   /** < Ta metoda obsłużyła event. Puść ten event dalej w stosie wywołań */
                BREAK = 0x02   /** < Ta metoda obsłużyła event. Zatrzymaj wykonywanie tego eventu. Inne handlery już go nie dostaną. */
        };

}

#endif /* HANDLING_H_ */
