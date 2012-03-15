/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_VIEW_IMAGE_H_
#define BAJKA_VIEW_IMAGE_H_

#include <SDL_opengl.h>
#include "Widget.h"
#include "resource/IBitmap.h"
#include "../geometry/Box.h"

namespace View {

/**
 * Simple image ie.\ from file.
 * \ingroup View
 */
class Image : public Widget {
public:
        C__ (void)
        b_ ("Widget")

        Image () : texName (0), texWidth (0), texHeight (0), imgWidth (0), imgHeight (0), initialized (false) {}
        virtual ~Image ();

        /// Do the drawing.
        virtual void update (Model::IModel *model);

        m_ (getBitmap) Ptr <IBitmap> getBitmap () { return bitmap; }
        S_ (setBitmap) void setBitmap (Ptr <IBitmap> b) { bitmap = b; }

        Geometry::Box const &getRegion () const { return (region.get ()) ? (*region) : (Geometry::Box::ZERO_BOX); }
        m_ (setRegion) void setRegion (Geometry::Box const &r) { region = std::auto_ptr <Geometry::Box> (new Geometry::Box (r)); }

protected:

        void init (Model::IModel *model, bool updateModelDimension = true);

protected:

        GLuint texName;
        // Rozmiary textury (potęga 2jki)
        int texWidth, texHeight;
        // Faktyczne rozmiary bitmapy (równe rozmiarom regionu, lub rozmiarom obrazka, jeśli region pusty).
        int imgWidth, imgHeight;
        bool initialized;
        Ptr <IBitmap> bitmap;
        std::auto_ptr <Geometry::Box> region;

        E_ (Image)
};

}

#	endif /* IMAGE_H_ */
