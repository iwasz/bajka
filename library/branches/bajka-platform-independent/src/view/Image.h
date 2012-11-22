/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_VIEW_IMAGE_H_
#define BAJKA_VIEW_IMAGE_H_

#include "openGl/OpenGl.h"
#include "view/Widget.h"
#include "resource/IBitmap.h"
#include "geometry/Box.h"

namespace View {

/**
 * Simple image ie.\ from file.
 * \ingroup View
 */
class Image : public Widget {
public:
        C__ (void)
        b_ ("Widget")

        Image ();
        virtual ~Image ();

        /// Do the drawing.
        virtual void update (Model::IModel *model, Event::UpdateEvent *e, View::GLContext *ctx);

        m_ (getBitmap) IBitmap *getBitmap () { return bitmap; }
        S_ (setBitmap) void setBitmap (IBitmap *b) { bitmap = b; }

        virtual double getWidthHint () const;
        virtual double getHeightHint () const;

protected:

        virtual void check ();
        void drawTile (float textureOffsetX, float textureOffsetY, View::GLContext *ctx);

protected:

        GLuint texName;
        // Rozmiary textury (potęga 2jki)
        int texWidth, texHeight;
        // Faktyczne rozmiary bitmapy (równe rozmiarom regionu, lub rozmiarom obrazka, jeśli region pusty).
        int imgWidth, imgHeight;
        bool initialized;
        IBitmap *bitmap;
        GLuint vertexBuffer;
        GLuint texCoordBuffer;

        E_ (Image)
};

}

#endif /* IMAGE_H_ */
