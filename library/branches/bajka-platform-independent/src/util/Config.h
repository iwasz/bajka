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

        bool            p_ (fullScreen);
        int             p_ (resX);
        int             p_ (resY);
        std::string     p_ (windowCaption);
        bool            p_ (showAABB);
        bool            p_ (showSystemCursor);
        View::Color     P_ (clearColor);
        int             p_ (loopDelayMs);
        Model::IModel * p_ (model);

        E_ (Config)
};

} /* namespace Util */

#	endif /* CONFIG_H_ */
