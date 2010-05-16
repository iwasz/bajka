/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IMAGE_H_
#define IMAGE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <String.h>

#include "AbstractWidget.h"

// TODO Przenieść do pliku z View::Rectangle
#include "AbstractModel.h"

namespace View {

/**
 * Simple image ie. from file. Caution! After seting a new model
 * with setModel method, you should call init to reload image, and
 * update model.width/height.
 */
class Image : public AbstractWidget {
public:
        __c (void)
        _b ("AbstractWidget")

        Image () : texName (0), texWidth (0), texHeight (0) {}
        virtual ~Image () {}

        virtual void init ();

        /// Do the drawing.
        virtual void doDraw ();

private:

        GLuint texName;
        int texWidth, texHeight;
        Ptr <Model::Image> model;

        _e (View::Image)
};

/**
 *
 */
struct Exception {

};

/**
 *
 */
struct ImageException : public Exception {

};

/*##########################################################################*/

class Rectangle : public AbstractWidget {
public:
        __c (void)
        _b ("AbstractWidget")

        virtual ~Rectangle () {}

        virtual void setModel2 (Ptr <Model2::IModel> model);
        virtual void doDraw ();

private:

        Model2::Box2 *box;
        _e (Rectangle)
};



///**
// *
// */
//class Layer : public Primitive {
//public:
//
//};

}

#	endif /* IMAGE_H_ */
