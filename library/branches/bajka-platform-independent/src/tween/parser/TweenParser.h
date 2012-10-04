/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TWEENPARSER_H_
#define TWEENPARSER_H_

#include <core/variant/Variant.h>
#include <core/Object.h>
#include <core/Exception.h>
#include "ITargetResolver.h"

namespace Tween {
class ParserImpl;
class ITween;

/**
 * Fabryka tweenów z reprezentacji JSON.
 */
class TweenParser {
public:

        TweenParser (ITargetResolver *resolver);
        virtual ~TweenParser ();

        Tween::ITween *parse (const char *input);

private:

        ParserImpl *impl;
};

/**
 *
 */
struct TweenParserException : public Core::Exception {
        TweenParserException (std::string const &s = "") : Core::Exception (s) {}
        virtual ~TweenParserException () throw () {}
};

} // nam

#endif /* TWEENPARSER_H_ */
