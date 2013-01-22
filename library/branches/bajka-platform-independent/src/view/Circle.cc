/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "draw/Primitives.h"
#include "model/static/Circle.h"
#include "Circle.h"

namespace View {

Circle::Circle ()
{
        glGenBuffers (1, &buffer);
}

/****************************************************************************/

Circle::~Circle ()
{
        glDeleteBuffers (1, &buffer);
}

/****************************************************************************/

static const GLfloat circleVAR[] = {
         0.0f,     0.0f,    0.0f, 1.0f,
         0.0000f,  1.0000f, 0.0f, 1.0f,
         0.2588f,  0.9659f, 0.0f, 1.0f,
         0.5000f,  0.8660f, 0.0f, 1.0f,
         0.7071f,  0.7071f, 0.0f, 1.0f,
         0.8660f,  0.5000f, 0.0f, 1.0f,
         0.9659f,  0.2588f, 0.0f, 1.0f,
         1.0000f,  0.0000f, 0.0f, 1.0f,
         0.9659f, -0.2588f, 0.0f, 1.0f,
         0.8660f, -0.5000f, 0.0f, 1.0f,
         0.7071f, -0.7071f, 0.0f, 1.0f,
         0.5000f, -0.8660f, 0.0f, 1.0f,
         0.2588f, -0.9659f, 0.0f, 1.0f,
         0.0000f, -1.0000f, 0.0f, 1.0f,
        -0.2588f, -0.9659f, 0.0f, 1.0f,
        -0.5000f, -0.8660f, 0.0f, 1.0f,
        -0.7071f, -0.7071f, 0.0f, 1.0f,
        -0.8660f, -0.5000f, 0.0f, 1.0f,
        -0.9659f, -0.2588f, 0.0f, 1.0f,
        -1.0000f, -0.0000f, 0.0f, 1.0f,
        -0.9659f,  0.2588f, 0.0f, 1.0f,
        -0.8660f,  0.5000f, 0.0f, 1.0f,
        -0.7071f,  0.7071f, 0.0f, 1.0f,
        -0.5000f,  0.8660f, 0.0f, 1.0f,
        -0.2588f,  0.9659f, 0.0f, 1.0f,
         0.0000f,  1.0000f, 0.0f, 1.0f
};

static const int circleVAR_indices = sizeof (circleVAR) / (sizeof (GLfloat) * 4);

/****************************************************************************/

void Circle::update (Model::IModel *model, Event::UpdateEvent *, View::GLContext *ctx)
{
        glLineWidth (getThickness ());
        glBindBuffer (GL_ARRAY_BUFFER, buffer);
        glBufferData (GL_ARRAY_BUFFER, sizeof (circleVAR), circleVAR, GL_STATIC_DRAW);

        glEnableVertexAttribArray (ctx->positionAttribLocation);

        glVertexAttribPointer (ctx->positionAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, 0);

        Color const &bg = getBackground ();
        if (bg.a > 0) {
                glUniform4f (ctx->colorUniformLocation, bg.r, bg.g, bg.b, bg.a);
                glDrawArrays (GL_TRIANGLE_FAN, 0, circleVAR_indices);
        }

        Color const &fg = getForeground ();
        if (fg.a > 0) {
                glUniform4f (ctx->colorUniformLocation, fg.r, fg.g, fg.b, fg.a);
                glDrawArrays (GL_LINE_STRIP, 0, circleVAR_indices);
        }

        glBindBuffer (GL_ARRAY_BUFFER, 0);
}

} /* namespace View */
