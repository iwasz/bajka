/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "TweenFactory.h"
#include <cassert>
#include <core/StrUtil.h>

namespace Tween {

Tween::ITween *TweenFactory::create ()
{
        return parser.parse (source.c_str ());
}

/****************************************************************************/

Core::Variant TweenFactory::resolve (const char *input)
{
        assert (container);
        return container->getBean (toStr (input));
}

} /* namespace Tween */
