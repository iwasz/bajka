/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_MODEL_LINEAR_GROUP_PROPS_H_
#define BAJKA_MODEL_LINEAR_GROUP_PROPS_H_

#include "geometry/Point.h"
#include "util/ReflectionMacros.h"
#include "IGroupProperties.h"
#include "Padding.h"
#include "Align.h"

namespace Model {
struct IModel;

/**
 *
 */
struct LinearGroupProperties : public IGroupProperties {

        C__ (void)
        LinearGroupProperties () :
                hAlign (HA_CENTER),
                vAlign (VA_CENTER) {}

        virtual ~LinearGroupProperties () {}

        HAlign pe_ (hAlign);
        VAlign pe_ (vAlign);

        E_ (LinearGroupProperties)
};

} /* namespace Model */

#	endif /* LAYOUT_H_ */
