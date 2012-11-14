/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 15, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ANDROID
#include "Image.h"
#include "util/Math.h"
#include "model/Model.h"
#include "util/Exceptions.h"
#include "view/openGl/OpenGl.h"

namespace View {

Image::~Image ()
{
        glDeleteTextures (1, &texName);
}

/****************************************************************************/

double Image::getWidthHint () const
{
        if (!bitmap) {
                return 0;
        }

        if (region.get ()) {
                return region->getWidth ();
        }

        return bitmap->getVisibleWidth ();
}

/****************************************************************************/

double Image::getHeightHint () const
{
        if (!bitmap) {
                return 0;
        }

        if (region.get ()) {
                return region->getHeight ();
        }

        return bitmap->getVisibleHeight ();
}

/****************************************************************************/

void Image::init (Model::IModel *model)
{
        initialized = true;

/*--------------------------------------------------------------------------*/

        glGenTextures(1, &texName);
        glBindTexture(GL_TEXTURE_2D, texName);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        /*
         * Te dwie poniższe komendy ustawiają filtrowanie dla przybliżania i
         * oddalania. GL_NEAREST - kolor z 1 teksela najbliższego pixelowi.
         */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

/*--------------------------------------------------------------------------*/

        texWidth = bitmap->getWidth ();
        texHeight = bitmap->getHeight ();
        imgWidth = bitmap->getVisibleWidth ();
        imgHeight = bitmap->getVisibleHeight ();

        int format = -1;

        if (bitmap->getColorSpace () == RGBA) {
                format = GL_RGBA;
        }
        else if (bitmap->getColorSpace () == RGB) {
                format = GL_RGB;
        }

        glTexImage2D (GL_TEXTURE_2D, 0, format, texWidth,
                     texHeight, 0, format, GL_UNSIGNED_BYTE,
                     bitmap->getData ());
}

/****************************************************************************/

void Image::update (Model::IModel *model, Event::UpdateEvent *, Util::IShell *)
{
        if (!initialized) {
                init (model);
        }

        glEnable (GL_TEXTURE_2D);
        glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture (GL_TEXTURE_2D, texName);

        glBegin (GL_QUADS);
                glTexCoord2i (0, 1); glVertex2i (0, 0);
                glTexCoord2i (0, 0); glVertex2i (0, texHeight);
                glTexCoord2i (1, 0); glVertex2i (texWidth, texHeight);
                glTexCoord2i (1, 1); glVertex2i (texWidth, 0);
        glEnd();

        glDisable (GL_TEXTURE_2D);
}

} // nam
#endif
