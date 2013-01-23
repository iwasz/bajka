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
#include "view/openGl/OpenGl.h"

namespace View {

Text::Text () : font (NULL),
        hash (0),
        multiline (false),
        align (IFont::LEFT)
{
}

/****************************************************************************/

Text::~Text ()
{
}

/****************************************************************************/

double Text::getWidthHint () const
{
        const_cast <Text *> (this)->check ();
        return imgWidth;
}

/****************************************************************************/

double Text::getHeightHint () const
{
        const_cast <Text *> (this)->check ();
        return imgHeight;
}

/****************************************************************************/

void Text::check ()
{
        static boost::hash <std::string> hf = boost::hash <std::string> ();
        std::size_t h = hf (text);

        if (h != hash) {
                hash = h;
        }
        else {
                return;
        }

        Ptr <IBitmap> bitmap;
        assert (font);

        if (multiline) {
                bitmap = font->renderMulti (text, getForeground (), align);
        }
        else {
                bitmap = font->render (text, getForeground ());
        }

        imgWidth = bitmap->getVisibleWidth ();
        imgHeight = bitmap->getVisibleHeight ();

        // Rozmiar bitmapy na texturę podniesiony do następnej potęgi
        texWidth = bitmap->getWidth ();
        texHeight = bitmap->getHeight ();

/*--------------------------------------------------------------------------*/

        glBindTexture(GL_TEXTURE_2D, texName);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        /*
         * Te dwie poniższe komendy ustawiają filtrowanie dla przybliżania i
         * oddalania. GL_NEAREST - kolor z 1 teksela najbliższego pixelowi.
         */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//        TODO zrobićlinear (treaz jest zamrożony kod, nie mogę).
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

/*--------------------------------------------------------------------------*/

        glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, texWidth,
                     texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     bitmap->getData ());
}

} /* namespace View */
