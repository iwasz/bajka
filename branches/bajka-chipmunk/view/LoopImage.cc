/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "LoopImage.h"

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

void LoopImage::update (Model::IModel *model)
{
        assertThrow (model->isBox (), "LoopImage::update : only box models are supported here.");

        if (!initialized) {
                init (model, false);
        }

        Model::IBox *b = dynamic_cast <Model::IBox *> (model);

        int countHoriz = int (b->getWidth () + 0.5) / texWidth + 1;
        int countVert = int (b->getHeight () + 0.5) / texHeight + 1

        glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBindTexture (GL_TEXTURE_2D, texName);

        for (int i = 0; i < countHoriz; ++i) {
                for (int j = 0; j < countVert; ++j) {
                        drawTile (i * offset.x, j * offset.y);
                }
        }

        if (offset.x > 0.0) {
                for (int j = 0; j < countVert; ++j) {
                        drawTile (offset.x, j * offset.y);
                }
        }

}

} /* namespace View */
