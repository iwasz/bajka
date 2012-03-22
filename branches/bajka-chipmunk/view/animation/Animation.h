/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_ANIMATION_H_
#define BAJKA_ANIMATION_H_

#include <SDL_opengl.h>
#include "FrameSet.h"
#include "../Widget.h"
#include "../resource/IBitmap.h"
#include "../../util/ReflectionMacros.h"
#include "../../geometry/Box.h"

namespace View {

/**
 * Animacja. Animacja może zawerać w sobie kilka sekwencji (musi przynajmniej jedną,
 * żeby coś się animowało). Sekwencje są nazwane, a wyboru sekwencji dokonujemy za
 * pomocą metody play (name).
 */
class Animation : public Widget {
public:

        C__ (void)
        b_ ("Widget")

        Animation () :
                texName (NULL),
                texWidth (0),
                texHeight (0),
                imgWidth (0),
                imgHeight (0),
                current (NULL),
                count (0),
                currentFrame (0),
                currentMs (0),
                paused (true),
                initialized (false) {}

        virtual ~Animation();

        /**
         * Uruchom sekwencję. Ma sens tylko gdy jest jedna sekwencja w mapie.
         * Gdy sekwencji jest więcej, należy użyć metody play (name).
         */
        virtual void play ();

        /**
         * Uruchom sekwencję o zadanej nazwie.
         */
        virtual void play (std::string const &name);

        /**
         * Zatrzymaj animację.
         */
        virtual void stop ();

        /// Do the drawing.
        virtual void update (Model::IModel *model, Event::UpdateEvent *e);

        m_ (getBitmap) Ptr <IBitmap> getBitmap () { return bitmap; }
        S_ (setBitmap) void setBitmap (Ptr <IBitmap> b) { bitmap = b; }

        Geometry::Box const &getRegion () const { return region; }
        m_ (setRegion) void setRegion (Geometry::Box const &r) { region = r; }

        int getCount () const { return count; }
        m_ (setCount)
        void setCount (int i) { count = i; }

        m_ (getFrames)
        FrameSetMap *getFrames () { return &frames; }
        m_ (setFrames)
        void setFrames (FrameSetMap const &f) { frames = f; }

        m_ (setDefault)
        void setDefault (std::string const &s) { play (s); }

        double getWidthHint () const;
        double getHeightHint () const;

protected:

        void init (Model::IModel *model);

private:

        // Tablica na tekstury.
        GLuint *texName;
        // Rozmiary textury (potęga 2jki)
        int texWidth, texHeight;
        // Faktyczne rozmiary bitmapy (równe rozmiarom regionu, lub rozmiarom obrazka, jeśli region pusty).
        int imgWidth, imgHeight;
        Ptr <IBitmap> bitmap;
        Geometry::Box region;
        FrameSetMap frames;
        FrameSet *current;
        int count;
        int currentFrame;
        int currentMs;
        bool paused;
        bool initialized;

        E_ (Animation)
};

} /* namespace View */

#endif /* ANIMATION_H_ */
