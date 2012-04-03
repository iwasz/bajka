/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ANDROID
#include <SDL.h>
#include <SDL_image.h>
#include "Animation.h"
#include "../../model/IModel.h"
#include "../../model/IBox.h"
#include "../../dependencies/GraphicsInterface.h"
#include "../../util/Exceptions.h"
#include "../../events/types/UpdateEvent.h"

namespace View {

Animation::~Animation ()
{
        glDeleteTextures (count, texName);
        delete [] texName;
}

/****************************************************************************/

double Animation::getWidthHint () const
{
        return region.getWidth ();
}

/****************************************************************************/

double Animation::getHeightHint () const
{
        return region.getHeight ();
}

/****************************************************************************/

void Animation::play ()
{
        FrameSetMap::iterator i = frames.begin ();

        if (i == frames.end ()) {
                throw Util::InitException ("Animation::play : no frameSets in Animation (empty).");
        }

        current = i->second;
        paused = false;
}

/****************************************************************************/

void Animation::play (std::string const &name)
{
        FrameSetMap::iterator i = frames.find (name);

        if (i == frames.end ()) {
                throw Util::InitException ("Animation::play : no such frameSet in animation. Name : [" + name + "]");
        }

        current = i->second;
        paused = false;
}

/****************************************************************************/

void Animation::stop ()
{
        paused = true;
}

/****************************************************************************/

void Animation::init (Model::IModel *model)
{
        initialized = true;

/*--------------------------------------------------------------------------*/

        // W image jest cały grid obrazków.
        SDL_Surface *image = static_cast <SDL_Surface *> (bitmap->getData ());

        // Rozmiary jednej klatki - takie jakie wyświetlimy na ekranie.
        imgWidth = region.getWidth ();
        imgHeight = region.getHeight ();

/*--------------------------------------------------------------------------*/

        texName = new GLuint[count];
        glGenTextures(count, texName);

        for (int i = 0; i < count; ++i) {

                glBindTexture (GL_TEXTURE_2D, texName[i]);

                glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
                glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
                glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

                Geometry::Box srcRegion = region;
                srcRegion.ll.x += imgWidth * i;
                srcRegion.ur.x += imgWidth * i;

                SDL_Surface *texSurface = GraphicsInterface::expandSurfacePowerOf2 (image, &srcRegion);

                // Rozmiary tekstury - potęga dwójki. Zawsze równe lub większe imgWidth i imgHeight
                texWidth = texSurface->w;
                texHeight = texSurface->h;

                glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, texWidth,
                              texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                              texSurface->pixels);

                SDL_FreeSurface (texSurface);
        }
}

/****************************************************************************/

void Animation::update (Model::IModel *model, Event::UpdateEvent *e)
{
        if (!initialized) {
                init (model);
        }

        glEnable (GL_TEXTURE_2D);
        glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture (GL_TEXTURE_2D, texName[currentFrame]);

        glBegin (GL_QUADS);
                glTexCoord2i (0, 1); glVertex2i (0, 0);
                glTexCoord2i (0, 0); glVertex2i (0, texHeight);
                glTexCoord2i (1, 0); glVertex2i (texWidth, texHeight);
                glTexCoord2i (1, 1); glVertex2i (texWidth, 0);
        glEnd();

        glDisable (GL_TEXTURE_2D);

        if (!paused) {
                currentMs += e->getDeltaMs ();

                if (currentMs >= 1000.0 / current->getFps ()) {
                        current->inc ();
                        currentFrame = current->getCurrentFrame ();
                        currentMs = 0;
                }
        }
}

} /* namespace View */
#endif
