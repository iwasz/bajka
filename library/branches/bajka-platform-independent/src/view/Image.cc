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
#include "util/IShell.h"

namespace View {

Image::Image () : texName (0), texWidth (0), texHeight (0), imgWidth (0), imgHeight (0), initialized (false), bitmap (NULL)
{
        glGenBuffers (1, &vertexBuffer);
        glBindBuffer (GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData (GL_ARRAY_BUFFER, 16 * sizeof (GLfloat), NULL, GL_DYNAMIC_DRAW); // Alokuje pamięć

        glGenBuffers (1, &texCoordBuffer);
        glBindBuffer (GL_ARRAY_BUFFER, texCoordBuffer);
        glBufferData (GL_ARRAY_BUFFER, 8 * sizeof (GLfloat), NULL, GL_DYNAMIC_DRAW);

        glGenTextures(1, &texName);
}

/****************************************************************************/

Image::~Image ()
{
        glDeleteTextures (1, &texName);
        glDeleteBuffers (1, &vertexBuffer);
        glDeleteBuffers (1, &texCoordBuffer);
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

void Image::update (Model::IModel *model, Event::UpdateEvent *, View::GLContext *ctx)
{
        if (!initialized) {
                init (model);
        }

        GLfloat verts[] = {
                0.0,      0.0,       0.0, 1.0,
                imgWidth, 0.0,       0.0, 1.0,
                0,        imgHeight, 0.0, 1.0,
                imgWidth, imgHeight, 0.0, 1.0
        };

        // Stworzenie bufora i zainicjowanie go danymi z vertex array.
        glBindBuffer (GL_ARRAY_BUFFER, vertexBuffer);
        glBufferSubData (GL_ARRAY_BUFFER, 0, 16 * sizeof (GLfloat), verts);
        glVertexAttribPointer (ctx->positionAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer (GL_ARRAY_BUFFER, 0);

        float texCoordW = double (imgWidth) / texWidth;
        float texCoordH = double (imgHeight) / texHeight;

        GLfloat texCoords[] = {
                0.0,       1.0 - texCoordH,
                texCoordW, 1.0 - texCoordH,
                0.0,       1.0,
                texCoordW, 1.0
        };

        glBindBuffer (GL_ARRAY_BUFFER, texCoordBuffer);
        glBufferSubData (GL_ARRAY_BUFFER, 0, 8 * sizeof (GLfloat), texCoords);
        glVertexAttribPointer (ctx->texCoordInAttribLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer (GL_ARRAY_BUFFER, 0);

        // Tekstura
        glActiveTexture(GL_TEXTURE0);
        glBindTexture (GL_TEXTURE_2D, texName);
        // A w taki dziwny sposób się przekazuje teksturę do shadera. Zamiast nazwy uniforma podajemy uchwyt do tekstury.
        glUniform1i (texName, 0);

        glEnableVertexAttribArray (ctx->positionAttribLocation);
        glEnableVertexAttribArray (ctx->texCoordInAttribLocation);

        glDrawArrays (GL_TRIANGLE_STRIP, 0, 4);

        glDisableVertexAttribArray (ctx->positionAttribLocation);
        glDisableVertexAttribArray (ctx->texCoordInAttribLocation);
}

} // nam
#endif
