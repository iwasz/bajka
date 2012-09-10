/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "util/Math.h"
#include "model/Model.h"
#include "Text.h"
#include "util/Exceptions.h"
#include <boost/functional/hash.hpp>

namespace View {

/****************************************************************************/

double Text::getWidthHint () const
{
        const_cast <Text *> (this)->initIf ();
        return imgWidth;
}

/****************************************************************************/

double Text::getHeightHint () const
{
        const_cast <Text *> (this)->initIf ();
        return imgHeight;
}

/****************************************************************************/

void Text::init ()
{
        Ptr <IBitmap> bitmap;
        assert (font);

        if (multiline) {
                bitmap = font->renderMulti (text, getForeground (), getBackground (), align);
        }
        else {
                bitmap = font->render (text, getForeground (), getBackground ());
        }

        imgWidth = bitmap->getWidth ();
        imgHeight = bitmap->getHeight ();

        // Rozmiar bitmapy na texturę podniesiony do następnej potęgi
        texWidth = Util::Math::nextSqr (imgWidth);
        texHeight = Util::Math::nextSqr (imgHeight);

        // Kopia o rozmiarach własciwych dla textury. TODO może da się wyelminować ten krok, tak, żeby font sam tworzył bitmapę o odpowiednim rozmiarze?
        Ptr <IBitmap> texBitmap = bitmap->blit (NULL, texWidth, texHeight);

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

        glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, texWidth,
                     texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     texBitmap->getData ());
}

/****************************************************************************/

void Text::initIf ()
{
        static boost::hash <std::string> hf = boost::hash <std::string> ();
        std::size_t h = hf (text);

        if (h != hash) {
                init ();
                hash = h;
        }
}

/****************************************************************************/

void Text::update (Model::IModel *model, Event::UpdateEvent *)
{
        initIf ();

        glEnable (GL_TEXTURE_2D);
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
