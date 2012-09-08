/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_FRAMESET_H_
#define BAJKA_FRAMESET_H_

#include <map>
#include "util/ReflectionMacros.h"
#include "util/Commons.h"

namespace View {

/**
 * Sekwencja animacji. Klasa Animation może zawierać kolekcję obiektów typu FrameSet.
 * Każdy taki obiekt odpowiada jednej sekwencji.
 */
class FrameSet {
public:

        C__ (void)
        FrameSet () : fps (0), loop (true) { reset (); }

        int getCurrentFrame () const { return *current; }

        /**
         * Następna klatka. Zwraca true gdy jesteśmy na ostatniej klatce i kolejne wywołanie
         * spowoduje przejście do początku.
         */
        bool inc ();

        /**
         * Poprzednia klatka.
         */
        bool dec ();
        void reset ();

        int getFps () const { return fps; }
        m_ (setFps)
        void setFps (int i) { fps = i; }

        bool getLoop () const { return loop; }
        m_ (setLoop)
        void setLoop (bool b) { loop = b; }

        m_ (getFrames)
        Util::IntVector const &getFrames () const { return frames; }
        m_ (setFrames)
        void setFrames (Util::IntVector const &f);

private:

        int fps;
        bool loop;
        // FIXME To by było fajnie, jakby była tablica, czy wskaźnik do 1 elem tablicy. Tylko kontener nie umie tworzyć tablic.
        Util::IntVector frames;
        Util::IntVector::const_iterator current;

        E_ (FrameSet)
};

typedef std::map <std::string, FrameSet *> FrameSetMap;
g_ (FrameSetMap);

} /* namespace View */

#endif /* FRAMESET_H_ */
