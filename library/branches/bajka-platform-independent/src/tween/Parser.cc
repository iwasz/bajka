/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cstring>
#include <jansson.h>
#include "core/Exception.h"
#include <sstream>
#include "AtomicTween.h"
#include "Parser.h"
#include "Manager.h"
#include "core/variant/Cast.h"

namespace Tween {

Tween::ITween *Parser::parse (const char *input)
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
                return parseTo (root);
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

Tween::AtomicTween *Parser::parseTo (json_t *data)
{
        AtomicTween *tween = Manager::getMain ()->newAtomicTween ();
        tween->type = AtomicTween::TO;

        json_t *field = json_object_get (data, "obj");
        const char *fieldStr = NULL;

        // Opcjonalny;
        if (field && json_is_string (field)) {
                fieldStr = json_string_value (field);
                Core::Variant obj = resolveObject (fieldStr);
                tween->object = vcast <void *> (obj);
        }

        // Wymagany
        field = json_object_get (data, "t");
        fieldStr = NULL;

        if (!field || !json_is_integer (field)) {
                throw TweenParserException ("tweenParseTo () : t (tween duration) is not a int, or is empty");
        }

        tween->durationMs = json_integer_value (field);

        return tween;
}

/****************************************************************************/

Core::Variant Parser::resolveObject (const char *input)
{
        return Core::Variant ();
}

} // namespace
