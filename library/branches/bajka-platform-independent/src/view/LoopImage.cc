/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "view/openGl/OpenGl.h"
#include "LoopImage.h"
#include "model/IModel.h"
#include "model/IBox.h"
#include "util/Exceptions.h"

namespace View {

void LoopImage::update (Model::IModel *model, Event::UpdateEvent *, View::GLContext *ctx)
{
        assertThrow (model->isBox (), "LoopImage::update : only box models are supported here.");
        Model::IBox *b = dynamic_cast <Model::IBox *> (model);
        check ();

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
                        drawTile (i * imgWidth + oW, j * imgHeight + oH, ctx);
                }
        }
}

} /* namespace View */
