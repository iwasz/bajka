/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_VIEW_IMAGE_H_
#define BAJKA_VIEW_IMAGE_H_

#include <SDL_opengl.h>
#include "Widget.h"

namespace View {

/**
 * Simple image ie.\ from file.
 * \ingroup View
 */
class Image : public Widget {
public:
        C__ (void)
        b_ ("Widget")

        Image () : texName (0), texWidth (0), texHeight (0), initialized (false) {}
        virtual ~Image () {}

        /// Do the drawing.
        virtual void update (Model::IModel *model);

        std::string const &getPath () const { return path; }
        m_ (setPath) void setPath (std::string const &p) { path = p; }

private:

        void init (Model::IModel *model);

private:

        GLuint texName;
        int texWidth, texHeight;
        std::string path;
        bool initialized;

        E_ (View::Image)
};

}

#	endif /* IMAGE_H_ */
