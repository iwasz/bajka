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
#include "util/IShell.h"

namespace View {

void Widget::preUpdate (Model::IModel *model, Event::UpdateEvent *, Util::IShell *shell)
{
        if (!visible) {
                return;
        }

        defaultPreUpdate (model, shell);
}

/****************************************************************************/

void Widget::postUpdate (Model::IModel *model, Event::UpdateEvent *, Util::IShell *shell)
{
        if (!visible) {
                return;
        }

        defaultPostUpdate (model, shell);
}

/****************************************************************************/

void Widget::defaultPreUpdate (Model::IModel *model, Util::IShell *shell)
{
        GLContext *ctx = shell->getGLContext ();

        GLint projectionLocation =  ctx->getProjectionLocation ();
        glUniformMatrix4fv (projectionLocation, 1, GL_FALSE, ctx->getProjectionMatrix ().data ().begin ());

        Geometry::AffineMatrix const &top = ctx->pushMatrix (model->getMatrix ());
        GLint modelViewLocation =  ctx->getModelViewLocation ();
        glUniformMatrix4fv (modelViewLocation, 1, GL_FALSE, top.data ().begin ());
}

/****************************************************************************/

void Widget::defaultPostUpdate (Model::IModel *model, Util::IShell *shell)
{
        shell->getGLContext ()->popMatrix ();
}

} /* namespace View */
