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
#include "Math.h"
#include "Model.h"
#include "GraphicsService.h"
#include "../util/Exceptions.h"

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

        return bitmap->getWidth ();
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

        return bitmap->getHeight ();
}

/****************************************************************************/

void Image::init (Model::IModel *model)
{
        initialized = true;

/*--------------------------------------------------------------------------*/

        if (region.get ()) {
                // Image będzie wycinkiem bitmapy
                imgWidth = region->getWidth ();
                imgHeight = region->getHeight ();
        }
        else {
                // Image będzie zawierało całą bitmapę.
                imgWidth = bitmap->getWidth ();
                imgHeight = bitmap->getHeight ();
        }

        // Rozmiar bitmapy na texturę podniesiony do następnej potęgi
        texWidth = Util::Math::nextSqr (imgWidth);
        texHeight = Util::Math::nextSqr (imgHeight);

        // Kopia o rozmiarach własciwych dla textury.
        Ptr <IBitmap> texBitmap = bitmap->blit (region.get (), texWidth, texHeight);

/*--------------------------------------------------------------------------*/

        glGenTextures(1, &texName);
        glBindTexture(GL_TEXTURE_2D, texName);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        /*
         * Te dwie poniższe komendy ustawiają filtrowanie dla przybliżania i
         * oddalania. GL_NEAREST - kolor z 1 teksela najbliższego pixelowi.
         */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

/*--------------------------------------------------------------------------*/
#if 0
        // Najpierw użyję proxy i sprawdzę czy uda się stworzyć teksturę:
        glTexImage2D(GL_PROXY_TEXTURE_2D, 0, GL_RGBA, width,
                     height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     NULL);

        GLint tmpWidth;
        glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &tmpWidth);

        assertThrow (tmpWidth == width, "Image::init : tmpWidth != width");
#endif
/*--------------------------------------------------------------------------*/

        glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, texWidth,
                     texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     texBitmap->getData ());
}

/****************************************************************************/

void Image::update (Model::IModel *model, Event::UpdateEvent *)
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
