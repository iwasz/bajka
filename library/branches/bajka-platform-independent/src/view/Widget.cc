/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "view/openGl/OpenGl.h"
#include "view/Widget.h"
#include "model/IModel.h"
#include "Platform.h"
#include "util/Config.h"
#include "draw/Primitives.h"

namespace View {

void Widget::preUpdate (Model::IModel *model, Event::UpdateEvent *, View::GLContext *ctx)
{
        if (!visible) {
                return;
        }

        defaultPreUpdate (model, ctx);
}

/****************************************************************************/

void Widget::postUpdate (Model::IModel *model, Event::UpdateEvent *, View::GLContext *ctx)
{
        if (!visible) {
                return;
        }

        defaultPostUpdate (model, ctx);
}

/****************************************************************************/

void Widget::defaultPreUpdate (Model::IModel *model, View::GLContext *ctx)
{
        glUniformMatrix4fv (ctx->projectionLocation, 1, GL_FALSE, ctx->getProjectionMatrix ().data ().begin ());

        Geometry::AffineMatrix const &top = ctx->pushMatrix (model->getMatrix ());

#if 0
        std::cerr << model << ", " << top << " | " << model->getMatrix () << std::endl;
#endif

        glUniformMatrix4fv (ctx->modelViewLocation, 1, GL_FALSE, top.data ().begin ());
}

/****************************************************************************/

void Widget::defaultPostUpdate (Model::IModel *model, View::GLContext *ctx)
{
        ctx->popMatrix ();
}

} /* namespace View */
