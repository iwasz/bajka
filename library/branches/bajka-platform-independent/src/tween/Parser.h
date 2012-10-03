/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TWEENPARSER_H_
#define TWEENPARSER_H_

#include "core/variant/Variant.h"

namespace Container {
class BeanFactoryContainer;
}

namespace Tween {
class AtomicTween;
class ITween;
class ParserImpl;

/**
 * Fabryka tweenów z reprezentacji JSON.
 */
class Parser {
public:

        Parser (Container::BeanFactoryContainer *c = NULL) : container (c) {}
        Tween::ITween *parse (const char *input);

private:

        Tween::AtomicTween *parseTo (json_t *data);
        Core::Variant resolveObject (const char *input);

private:

        Container::BeanFactoryContainer *container;
};

/**
 *
 */
struct TweenParserException : public Core::Exception {
        TweenParserException (std::string const &s = "") : Core::Exception (s) {}
        virtual ~TweenParserException () throw () {}
};

} //

#endif /* TWEENPARSER_H_ */
