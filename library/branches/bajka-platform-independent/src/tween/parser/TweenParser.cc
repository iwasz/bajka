/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cstring>
#include <jansson.h>
#include <sstream>
#include "tween/AtomicTween.h"
#include "tween/Manager.h"
#include "tween/accessor/AffineAccessor.h"
#include "TweenParser.h"
#include <core/variant/Cast.h>
#include <core/StrUtil.h>
#include <cstdlib>
#include <boost/pool/object_pool.hpp>
#include <cerrno>
#include "tween/Timeline.h"
#include "tween/MultiTween.h"

namespace Tween {

struct ParserImpl {
        Tween::ITween *parse (json_t *data);
        Tween::AtomicTween *parseAtomic (json_t *data, AtomicTween::Type type);
        Tween::Timeline *parseTimeline (json_t *data);
        Tween::MultiTween *parseMulti (json_t *data);

        void setEase (AtomicTween *tween, json_t *field);
        void setTargetObject (AtomicTween *tween, json_t *field);

        const char *getString (json_t *data, const char *key, bool required, const char *defaultValue = NULL);
        json_int_t getInteger (json_t *data, const char *key, bool required, json_int_t defaultValue = 0);
        bool getBoolean (json_t *data, const char *key, bool required, bool defaultValue = false);

        ITargetResolver *resolver;
};

/****************************************************************************/

TweenParser::TweenParser (ITargetResolver *resolver)
{
        impl = new ParserImpl;
        impl->resolver = resolver;
}

/****************************************************************************/

TweenParser::~TweenParser ()
{
        delete impl;
}

/****************************************************************************/

Tween::ITween *TweenParser::parse (const char *input)
{
        json_t *root = NULL;
        json_error_t error;

        root = json_loads (input, 0, &error);

        if (!root) {
                std::ostringstream s;
                s << "TweenParser::parse () : error on line " << error.line << ", message : " << error.text;
                throw TweenParserException (s.str ());
        }

        return impl->parse (root);
}
/****************************************************************************/

Tween::ITween *ParserImpl::parse (json_t *data)
{
        if (!json_is_object (data)) {
                throw TweenParserException ("tweenParse () : root is not an object");
        }

        // Type musi być
        json_t *type = json_object_get (data, "type");

        if (!type || !json_is_string (type)) {
                throw TweenParserException ("tweenParse () : type is not a string");
        }

        const char *typeStr = json_string_value (type);

        if (strcmp (typeStr, "to") == 0) {
                return parseAtomic (data, AtomicTween::TO);
        }
        else if (strcmp (typeStr, "from") == 0) {
                return parseAtomic (data, AtomicTween::FROM);
        }
        else if (strcmp (typeStr, "timeline") == 0) {
                return parseTimeline (data);
        }
        else if (strcmp (typeStr, "multi") == 0) {
                return parseMulti (data);
        }

        json_decref (data);
        return NULL;
}

/****************************************************************************/

Tween::AtomicTween *ParserImpl::parseAtomic (json_t *data, AtomicTween::Type type)
{
        AtomicTween *tween = Manager::getMain ()->newAtomicTween ();
        tween->type = type;

        setTargetObject (tween, data);
        tween->durationMs = getInteger (data, "t", true);
        setEase (tween, data);
        tween->delay (getInteger (data, "delay", false));
        tween->repeat (getInteger (data, "repeat", false, 0), getBoolean (data, "yoyo", false, false));

        json_t *field = json_object_get (data, "targets");
        if (!field || !json_is_array (field)) {
                throw TweenParserException ("tweenParseTo () : targets are not an array instance, or are empty");
        }

        for (size_t i = 0; i < json_array_size (field); ++i) {

                json_t *target = json_array_get (field, i);

                if (!json_is_object(target)) {
                        throw TweenParserException ("parseAtomic () : target is not an object");
                }

                const char *key;
                json_t *value;

                void *iter = json_object_iter (target);
                while (iter) {
                    key = json_object_iter_key (iter);
                    value = json_object_iter_value (iter);

                    if (json_is_integer (value)) {
                            tween->abs (key, json_integer_value (value));
                    }
                    else if (json_is_string (value)) {
                            const char *strValInt = json_string_value (value);
                            long int valInt = strtol (strValInt, NULL, 10);

                            if ((errno == ERANGE && (valInt == LONG_MAX || valInt == LONG_MIN)) || (errno != 0 && valInt == 0)) {
                                    throw TweenParserException ("parseAtomic () : relative value must be of an integer value.");
                            }

                            tween->rel (key, valInt);
                    }

                    iter = json_object_iter_next (target, iter);
                }
        }

        return tween;
}

/****************************************************************************/

Tween::Timeline *ParserImpl::parseTimeline (json_t *data)
{
        Tween::Timeline *timeline = Manager::getMain ()->newTimeline ();

        json_t *field = json_object_get (data, "tweens");

        if (!field || !json_is_array (field)) {
                throw TweenParserException ("parseTimeline () : tweens are not an array instance, or are empty");
        }

        for (size_t i = 0; i < json_array_size (field); ++i) {

                json_t *tween = json_array_get (field, i);

                if (!json_is_object (tween)) {
                        throw TweenParserException ("parseTimeline () : tween is not an object");
                }

                timeline->add (parse (tween));
        }

        return timeline;
}

/****************************************************************************/

Tween::MultiTween *ParserImpl::parseMulti (json_t *data)
{
        Tween::MultiTween *multi = Manager::getMain ()->newMultiTween ();

        json_t *field = json_object_get (data, "tweens");

        if (!field || !json_is_array (field)) {
                throw TweenParserException ("parseTimeline () : tweens are not an array instance, or are empty");
        }

        for (size_t i = 0; i < json_array_size (field); ++i) {

                json_t *tween = json_array_get (field, i);

                if (!json_is_object (tween)) {
                        throw TweenParserException ("parseMulti () : tween is not an object");
                }

                multi->add (parse (tween));
        }

        return multi;
}

/****************************************************************************/

const char *ParserImpl::getString (json_t *data, const char *key, bool required, const char *defaultValue)
{
        json_t *field = json_object_get (data, key);

        if (!field) {
                if (required) {
                        throw TweenParserException (std::string ("tweenParser : ") + key + "is null, but is required.");
                }

                return defaultValue;
        }

        if (!json_is_string (field)) {
                throw TweenParserException (std::string ("tweenParser : ") + key + "is not a string.");
        }

        return json_string_value (field);
}

/****************************************************************************/

json_int_t ParserImpl::getInteger (json_t *data, const char *key, bool required, json_int_t defaultValue)
{
        json_t *field = json_object_get (data, key);

        if (!field) {
                if (required) {
                        throw TweenParserException (std::string ("tweenParser : ") + key + "is null, but is required.");
                }

                return defaultValue;
        }

        if (!json_is_integer (field)) {
                throw TweenParserException (std::string ("tweenParser : ") + key + "is not an int.");
        }

        return json_integer_value (field);
}


/****************************************************************************/

bool ParserImpl::getBoolean (json_t *data, const char *key, bool required, bool defaultValue)
{
        json_t *field = json_object_get (data, key);

        if (!field) {
                if (required) {
                        throw TweenParserException (std::string ("tweenParser : ") + key + "is null, but is required.");
                }

                return defaultValue;
        }

        if (json_is_true (field)) {
                return true;
        }

        if (json_is_false (field)) {
                return false;
        }

        throw TweenParserException (std::string ("tweenParser : ") + key + "is not a boolean.");
}

/****************************************************************************/

void ParserImpl::setEase (AtomicTween *tween, json_t *field)
{
        const char *fieldStr = getString (field, "ease", false, "QUAD_INOUT");
        tween->equation = Manager::getMain ()->getEase (fieldStr);

        if (!tween->equation) {
                throw TweenParserException (std::string ("tweenParseTo () : ease is invalid : [") + json_string_value (field) + "]");
        }
}

/****************************************************************************/

void ParserImpl::setTargetObject (AtomicTween *tween, json_t *field)
{
        const char *fieldStr = getString (field, "obj", false);

        // Opcjonalny;
        if (fieldStr) {
                assert (resolver);
                Core::Variant obj = resolver->resolve (fieldStr);
                tween->object = vcast <void *> (obj);
        }
}

} // namespace
