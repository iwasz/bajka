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

namespace Tween {

struct ParserImpl {
        Tween::AtomicTween *parseTo (json_t *data);

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
                s << "tweenParse () : error on line " << error.line << ", message : " << error.text;
                throw TweenParserException (s.str ());
        }

        if (!json_is_object (root)) {
                throw TweenParserException ("tweenParse () : root is not an object");
        }

        // Type musi być
        json_t *type = json_object_get (root, "type");

        if (!type || !json_is_string (type)) {
                throw TweenParserException ("tweenParse () : type is not a string");
        }

        const char *typeStr = json_string_value (type);

        if (strcmp (typeStr, "to") == 0) {
                return impl->parseTo (root);
        }
        else if (strcmp (typeStr, "from") == 0) {

        }
        else if (strcmp (typeStr, "timeline") == 0) {

        }
        else if (strcmp (typeStr, "multi") == 0) {

        }

        json_decref (root);
        return NULL;
}

/****************************************************************************/

Tween::AtomicTween *ParserImpl::parseTo (json_t *data)
{
        AtomicTween *tween = Manager::getMain ()->newAtomicTween ();
        tween->type = AtomicTween::TO;

        json_t *field = json_object_get (data, "obj");
        const char *fieldStr = NULL;

        // Opcjonalny;
        if (field && json_is_string (field)) {
                fieldStr = json_string_value (field);
                assert (resolver);
                Core::Variant obj = resolver->resolve (fieldStr);
                tween->object = vcast <void *> (obj);
        }

        // Wymagany
        field = json_object_get (data, "t");
        fieldStr = NULL;

        if (!field || !json_is_integer (field)) {
                throw TweenParserException ("tweenParseTo () : t (tween duration) is not a int, or is empty");
        }

        tween->durationMs = json_integer_value (field);

//        LINEAR_INOUT
        tween->equation = Manager::getMain ()->getEase (LINEAR_INOUT);


        field = json_object_get (data, "targets");
        if (!field || !json_is_array (field)) {
                throw TweenParserException ("tweenParseTo () : targets are not an array instance, or are empty");
        }


        for (size_t i = 0; i < json_array_size (field); ++i) {

                json_t *target = json_array_get (field, i);

                if (!json_is_object(target)) {
                        throw TweenParserException ("tweenParseTo () : target is not an object");
                }

//                const char *key;
                json_t *value;

                void *iter = json_object_iter (target);
                while (iter) {
//                    key = json_object_iter_key (iter);
                    value = json_object_iter_value (iter);

                    tween->abs(Y, json_integer_value (value));


                    iter = json_object_iter_next (target, iter);
                }
        }

        return tween;
}

} // namespace
