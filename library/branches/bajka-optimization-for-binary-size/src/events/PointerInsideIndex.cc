/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "PointerInsideIndex.h"
#include "../model/IModel.h"
#include "../model/IGroup.h"

namespace Event {

void PointerInsideIndex::remove (Model::IModel *m)
{
        if (m->isGroup ()) {
                Model::IGroup *g = dynamic_cast <Model::IGroup *> (m);

                for (Model::ModelVector::const_iterator i = g->getChildren ().begin ();
                         i != g->getChildren ().end ();
                         ++i) {

                                remove (*i);
                }
        }

        index.erase (m);
}

} /* namespace Event */
