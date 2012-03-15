/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 15, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL.h>
#include <SDL_image.h>
#include "Image.h"
#include "Math.h"
#include "Model.h"
#include "../dependencies/sdl/Util.h"
#include "../util/Exceptions.h"

namespace View {

Image::~Image ()
{
        glDeleteTextures (1, &texName);
}

/****************************************************************************/

void Image::init (Model::IModel *model, bool updateModelDimension)
{
        initialized = true;

/*--------------------------------------------------------------------------*/

        SDL_Surface *image = static_cast <SDL_Surface *> (bitmap->getData ());

        if (updateModelDimension && model->isBox ()) {
                Model::IBox *b = dynamic_cast <Model::IBox *> (model);

                if (region.get ()) {
                        b->setWidth (region->getWidth ());
                        b->setHeight (region->getHeight ());
                }
                else {
                        b->setWidth (image->w);
                        b->setHeight (image->h);
                }
        }

/*--------------------------------------------------------------------------*/

        if (region.get ()) {
                imgWidth = region->getWidth ();
                imgHeight = region->getHeight ();
        }
        else {
                imgWidth = image->w;
                imgHeight = image->h;
        }

        SDL_Surface *texSurface = Sdl::expandSurfacePowerOf2 (image, region.get ());

        int width = texSurface->w;
        int height = texSurface->h;

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

        // Najpierw użyję proxy i sprawdzę czy uda się stworzyć teksturę:
        glTexImage2D(GL_PROXY_TEXTURE_2D, 0, GL_RGBA, width,
                     height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     NULL);

        GLint tmpWidth;
        glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &tmpWidth);

        assertThrow (tmpWidth == width, "Image::init : tmpWidth != width");

/*--------------------------------------------------------------------------*/

        glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, width,
                     height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     texSurface->pixels);

        texWidth = width;
        texHeight = height;

        SDL_FreeSurface (texSurface);
}

/****************************************************************************/

void Image::update (Model::IModel *model)
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
