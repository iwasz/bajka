/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_CONFIG_H_
#define BAJKA_CONFIG_H_

#include "ReflectionMacros.h"

namespace Util {

/*
 * Ta klasa jest tylko po to, żeby ułatwoć stosowanie bajki z kontenerem.
 * Otóż kolejność pracy programu musi być następująca:
 * - Utworzenie BajkaConfig.
 * - Ustawienie jej pól.
 * - Uruchomienie init ().
 * Treaz OpenGL i SDL są zainicjowane, można dodawać obiekty. I dopero teraz
 * można uruchomić pętlę programu:
 * - BajkaApp run.
 * INICJUJE OpenGL!
 */
class BajkaConfig {
public:
        C__ (void)

        BajkaConfig ();

/*------access methods------------------------------------------------------*/

        bool getFullScreen () const { return fullScreen; }
        m_ (setFullScreen) void setFullScreen (bool fullScreen) { this->fullScreen = fullScreen; }

        int getResX () const { return resX; }
        m_ (setResX) void setResX (int resX) { this->resX = resX; }

        int getResY () const { return resY; }
        m_ (setResY)  void setResY (int resY) { this->resY = resY; }

        const std::string &getWindowCaption () const { return windowCaption; }
        m_ (setWindowCaption) void setWindowCaption (const std::string &windowCaption) { this->windowCaption = windowCaption; }

private:

        bool fullScreen;
        int resX;
        int resY;
        std::string windowCaption;

        E_ (BajkaConfig)
};

} /* namespace Util */

#	endif /* CONFIG_H_ */