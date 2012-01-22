/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL.h>
#include <SDL_image.h>
#include "Math.h"
#include "Model.h"
#include "Text.h"
#include "../util/Exceptions.h"
#include <boost/functional/hash.hpp>
#include "../dependencies/sdl/Util.h"

using Sdl::expandSurfacePowerOf2;

namespace View {

void Text::init (Model::IModel *model)
{
        SDL_Surface *image = static_cast <SDL_Surface *> (font->render (text, getForeground (), getBackground ()));
        SDL_Surface *texSurface = expandSurfacePowerOf2 (image);
        SDL_FreeSurface (image);

        unsigned int width = texSurface->w;
        unsigned int height = texSurface->h;

/*--------------------------------------------------------------------------*/

        // TODO może nie trzeba za każdym razem tworzyć nowej tekstury, poza tym nie wiem, czy nie wycieka pamięć w karcie tu.
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

        if (tmpWidth != width) {
                throw Util::RuntimeException ("Text::update : tmpWidth != width");
        }

/*--------------------------------------------------------------------------*/

        glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, width,
                     height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     texSurface->pixels);

        texWidth = width;
        texHeight = height;

        SDL_FreeSurface (texSurface);
}

/****************************************************************************/

void Text::update (Model::IModel *model)
{
        static boost::hash <std::string> hf = boost::hash <std::string> ();
        std::size_t h = hf (text);

        if (h != hash) {
                init (model);
                hash = h;
        }

        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture(GL_TEXTURE_2D, texName);

        glBegin (GL_QUADS);
                glTexCoord2i (0, 1); glVertex2i (0, 0);
                glTexCoord2i (0, 0); glVertex2i (0, texHeight);
                glTexCoord2i (1, 0); glVertex2i (texWidth, texHeight);
                glTexCoord2i (1, 1); glVertex2i (texWidth, 0);
        glEnd();

        glDisable (GL_TEXTURE_2D);
}


} /* namespace View */
