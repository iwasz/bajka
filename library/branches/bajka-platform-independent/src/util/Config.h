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

/**
 * Konfiguracja gry.
 */
struct Config {

        C__ (void)

        Config ();

        /**
         * Pełny ekran. Gra wyświetli się nie w okienku z belką, ale na pełnym ekranie o rozdzielczości
         * viewportWidth / viewportHeight lub o rozdzielczości ekranu jaką miał system przed uruchomieniem
         * gry jeśli autoViewport == true;
         */
        bool            p_ (fullScreen);

        /**
         * Auto-rozdzielczość. Jeśli ustawione na true to wartości viewportWidth i viewportHeight
         * są zamazywane szerokością i wysokością ekranu w pikselach. Ich ustawianie nie ma wówczas
         * rezultatu.
         */
        bool            p_ (autoViewport);

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
         * Wysokość układu współrzędnych (w punktach) widocznego w oknie gry. Jeśli nie ustawisz tego pola, a ustawisz
         * projectionWidth, to to pole zostanie wyliczone na podstawie rozdzielczości viewportu (czyli zostanie
         * zachowane aspect-ratio).
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
