/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_CONFIG_H_
#define BAJKA_CONFIG_H_

#include "util/ReflectionMacros.h"
#include "view/draw/Color.h"
#include "model/IModel.h"

namespace Util {

/*
 * Ta klasa jest tylko po to, żeby ułatwoć stosowanie bajki z kontenerem.
 * Otóż kolejność pracy programu musi być następująca:
 * - Utworzenie Config.
 * - Ustawienie jej pól.
 * - Uruchomienie init ().
 * Treaz OpenGL i SDL są zainicjowane, można dodawać obiekty. I dopero teraz
 * można uruchomić pętlę programu:
 * - App run.
 * INICJUJE OpenGL!
 */
struct Config {

        C__ (void)

        Config ();

        /**
         * Pełny ekran. Jeśli ustawione na truem to wartości viewportWidth i viewportHeight
         * są zamazywane szerokością i wysokością pełnego ekranu. Ich ustawianie nie ma wówczas
         * rezultatu.
         */
        bool            p_ (fullScreen);

        /**
         * Szerokość okna w pikselach. Jeśli fullScreen jest na false, to tu podajemy szerokość
         * ekranu (fizycznego okna) w pikselach.
         */
        int             p_ (viewportWidth);

        /**
         * Wysokość okna w pikselach. Jeśli fullScreen jest na false, to tu podajemy wysokość
         * ekranu (fizycznego okna) w pikselach.
         */
        int             p_ (viewportHeight);

        /**
         * Auto projekcja. To jest konfiguracja układu współrzędnych w przestrzeni gry. Jeśli autoProjection
         * kest na true, to projectionWidth i projectionHeight zostaną ustawione tak, żeby jeden punkt w układzie
         * współrzędnych gry odpowiadał dokładnie jednemu pikselowi na ekranie. Jest to przydatne do robienia
         * grafiki pixel-perfect, czyli na przykład pixelart. Jeśli autoProjection jest true, to ustawianie
         * projectionWidth i projectionHeight nie ma rezultatu.
         */
        bool            p_ (autoProjection);

        /**
         * Szerokość układu współrzędnych (w punktach) widocznego w oknie gry. Czyli na przykład ustawiamy viewportWidth
         * na 640, a projectionWidth na 160 - wówczas jedne punkt w układzie współrzędnych gry będzie miał 4 pixele.
         */
        float           p_ (projectionWidth);

        /**
         * Szerokość układu współrzędnych (w punktach) widocznego w oknie gry.
         * \see projectionWidth
         */
        float           p_ (projectionHeight);

        /**
         * Napis na belce okna (jeśli jest belka).
         */
        std::string     p_ (windowCaption);

        /**
         * Pokazuj bounding boxy.
         */
        bool            p_ (showAABB);

        /**
         * Ukryj / pokaż kursor systemowy.
         */
        bool            p_ (showSystemCursor);
        int             p_ (loopDelayMs);
        Model::IModel * p_ (model);

        E_ (Config)
};

} /* namespace Util */

#	endif /* CONFIG_H_ */
