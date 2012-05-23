/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_CHIPMUNK
#ifndef BAJKA_MODEL_SHAPE_H_
#define BAJKA_MODEL_SHAPE_H_

#include <chipmunk.h>
#include "../../util/ReflectionMacros.h"
#include "../IModel.h"

namespace Model {

class ICPShape : public virtual Core::Object {
public:

        d__

        virtual ~ICPShape ();



        E_ (ICPShape)
};

} /* namespace Model */

#endif /* SHAPE_H_ */
#endif
