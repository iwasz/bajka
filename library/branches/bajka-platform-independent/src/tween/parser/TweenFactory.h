/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TWEENFACTORY_CONTAINER_H_
#define TWEENFACTORY_CONTAINER_H_

#include "util/ReflectionMacros.h"
#include "ITweenFactory.h"
#include <container/beanFactory/BeanFactoryContainer.h>
#include "TweenParser.h"
#include <string>

namespace Tween {

class TweenFactory : public ITweenFactory {
public:
        C__ (void)

        TweenFactory () : container (NULL), parser (this) {}
        virtual ~TweenFactory() {}

        Tween::ITween *create ();
        Core::Variant resolve (const char *input);

private:

        Container::BeanFactoryContainer *p_ (container);
        TweenParser parser;
        std::string P_ (source);

        E_ (TweenFactory)
};

} /* namespace Tween */
#endif /* TWEENFACTORY_H_ */
