/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef GRAPHICSSERVICE_H_
#define GRAPHICSSERVICE_H_

class ShellFactory;

namespace Util {
class Config;
}

/**
 *
 */
class GraphicsService {
public:

        /**
         * Metoda inicjująca, którą można wywoływac wiele razy na róznych etapach
         * i ona zawsze sprawdza co jest do zainichowania. Czyli śmiało można wywoływać
         * wiele razy.
         * Zwraca true, gdy operacja się powiedzie i ekran jest zainicjowany. False, gdy
         * się nie powiodła, ale jest szansa, że nastęþnym razem będzie OK. Zrzuca wyjątki
         * gdy sytuacja jest krytyczna.
         */
        bool initDisplay (Util::Config *config);
        void termDisplay ();
        void unbindSurfaceAndContext ();

        /**
         * Zwraca true gdy powodzenie.
         */
        bool saveScreenDimensionsInConfig (Util::Config *config);
        void swapBuffers ();

private:

        GraphicsService ();
        friend class ShellFactory;

private:

};

#endif /* GRAPHICSSERVICE_H_ */
