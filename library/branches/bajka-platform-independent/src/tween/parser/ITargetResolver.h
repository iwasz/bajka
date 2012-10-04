/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ITARGETRESOLVER_H_
#define ITARGETRESOLVER_H_

namespace Tween {

/**
 *
 */
class ITargetResolver {
public:
        virtual ~ITargetResolver() {}
        virtual Core::Variant resolve (const char *input) = 0;
};

} /* namespace Tween */
#endif /* ITARGETRESOLVER_H_ */
