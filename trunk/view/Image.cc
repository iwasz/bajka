/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 15, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <Foreach.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "Image.h"
#include "Math.h"

namespace View {

//void Image::setModel (Ptr <Model::IModel> m)
void Image::init ()
{
//        AbstractWidget::setModel (m);
        model = dynamic_pointer_cast <Model::Image> (getModel ());
        assert (model);

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

        SDL_Surface *texSurface = NULL;
        SDL_Surface *image = IMG_Load (model->getPath ().c_str ());

        if (image == NULL) {
                throw ImageException ();
        }

        model->setCenter (Model::Point (image->w / 2.0, image->h / 2.0));
        model->setWidth (image->w);
        model->setHeight (image->h);

        // Podniesione do następnej potęgi
        unsigned int width = Util::Math::nextSqr (image->w);
        unsigned int height = Util::Math::nextSqr (image->h);

        if (height != image->h || width != image->w) {

                SDL_Surface *surface = SDL_CreateRGBSurface (SDL_SWSURFACE, width, height, 32,
                #if SDL_BYTEORDER == SDL_LIL_ENDIAN
                            0x000000FF,
                            0x0000FF00,
                            0x00FF0000,
                            0xFF000000
                #else
                            0xFF000000,
                            0x00FF0000,
                            0x0000FF00,
                            0x000000FF
                #endif
                );

                if(surface == NULL) {
                        throw ImageException ();
                }

                Uint32 saved_flags = image->flags & (SDL_SRCALPHA | SDL_RLEACCELOK);
                if ((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA) {
                        SDL_SetAlpha (image, 0, 0);
                }

                /* Copy the surface into the GL texture image */
                SDL_Rect area;

                area.x = 0;
                area.y = height - image->h;
                area.w = image->w;
                area.h = image->h;

                SDL_BlitSurface (image, NULL, surface, &area);
                SDL_FreeSurface (image);

                texSurface = surface;
        }
        else {
                texSurface = image;
        }

/*--------------------------------------------------------------------------*/

        // Najpierw użyję proxy i sprawdzę czy uda się stworzyć teksturę:
        glTexImage2D(GL_PROXY_TEXTURE_2D, 0, GL_RGBA, width,
                     height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     NULL);

        GLint tmpWidth;
        glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &tmpWidth);

        if (tmpWidth != width) {
                throw ImageException ();
        }

/*--------------------------------------------------------------------------*/

        glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, width,
                     height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     texSurface->pixels);

        texWidth = width;
        texHeight = height;

        std::cerr << "path:" << model->getPath () << " texW:"  << width << " texH:" << height << " imgW:" << model->getWidth () << " imgH:" << model->getHeight () << std::endl;

        SDL_FreeSurface (texSurface);
}

/****************************************************************************/

//void Image::preDraw ()
//{
//        if (needRefresh) {
//                refreshView();
//                needRefresh = false;
//        }
//
//        AbstractWidget::preDraw ();
//}

/****************************************************************************/

void Image::doDraw ()
{
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

} // nam
