/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ANDROID
#include "view/openGl/OpenGl.h"
#include "LoopImage.h"
#include "model/IModel.h"
#include "model/IBox.h"
#include "util/Exceptions.h"

namespace View {

void LoopImage::drawTile (double x, double y)
{
        glBegin (GL_QUADS);
                glTexCoord2i (0, 1); glVertex2i (x, y);
                glTexCoord2i (0, 0); glVertex2i (x, texHeight + y);
                glTexCoord2i (1, 0); glVertex2i (texWidth + x, texHeight + y);
                glTexCoord2i (1, 1); glVertex2i (texWidth + x, y);
        glEnd();
}

/****************************************************************************/

void LoopImage::update (Model::IModel *model, Event::UpdateEvent *, View::GLContext *ctx)
{
        assertThrow (model->isBox (), "LoopImage::update : only box models are supported here.");

        if (!initialized) {
                init (model);
        }

        glEnable (GL_TEXTURE_2D);
        glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture (GL_TEXTURE_2D, texName);

        Model::IBox *b = dynamic_cast <Model::IBox *> (model);

        int bW = int (b->getWidth ());
        int bH = int (b->getHeight ());
        int oModW = offsetX % imgWidth;
        int oModH = offsetY % imgHeight;
        int oW = (oModW) ? (oModW - imgWidth) : (0);
        int oH = (oModH) ? (oModH - imgHeight) : (0);
        int countHoriz = bW / imgWidth + ((bW % imgWidth) != 0) + (oW != 0);
        int countVert = bH / imgHeight + ((bH % imgHeight) != 0) + (oH != 0);

        for (int i = 0; i < countHoriz; ++i) {
                for (int j = 0; j < countVert; ++j) {
                        drawTile (i * imgWidth + oW, j * imgHeight + oH);
                }
        }

        glDisable (GL_TEXTURE_2D);
}

} /* namespace View */
#endif
