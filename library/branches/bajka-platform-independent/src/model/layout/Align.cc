/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Align.h"
#include "util/Exceptions.h"

namespace Model {

Core::Variant stringToHAlign (std::string const &p)
{
        if (p == "left") {
                return Core::Variant (static_cast <unsigned int> (HA_LEFT));
        }
        else if (p == "right") {
                return Core::Variant (static_cast <unsigned int> (HA_RIGHT));
        }
        else if (p == "center") {
                return Core::Variant (static_cast <unsigned int> (HA_CENTER));
        }

        throw Util::InitException ("stringToHAlign () : worng string literal for HAlign : [" + p + "]");
}

/****************************************************************************/

Core::Variant stringToVAlign (std::string const &p)
{
        if (p == "top") {
                return Core::Variant (static_cast <unsigned int> (VA_TOP));
        }
        else if (p == "bottom") {
                return Core::Variant (static_cast <unsigned int> (VA_BOTTOM));
        }
        else if (p == "center") {
                return Core::Variant (static_cast <unsigned int> (VA_CENTER));
        }

        throw Util::InitException ("stringToVAlign () : worng string literal for VAlign : [" + p + "]");
}

/****************************************************************************/

Core::Variant stringToHGravity (std::string const &p)
{
        if (p == "left") {
                return Core::Variant (static_cast <unsigned int> (HG_LEFT));
        }
        else if (p == "right") {
                return Core::Variant (static_cast <unsigned int> (HG_RIGHT));
        }
        else if (p == "center") {
                return Core::Variant (static_cast <unsigned int> (HG_CENTER));
        }

        throw Util::InitException ("stringToHGravity () : worng string literal for HGravity : [" + p + "]");
}

/****************************************************************************/

Core::Variant stringToVGravity (std::string const &p)
{
        if (p == "top") {
                return Core::Variant (static_cast <unsigned int> (VG_TOP));
        }
        else if (p == "bottom") {
                return Core::Variant (static_cast <unsigned int> (VG_BOTTOM));
        }
        else if (p == "center") {
                return Core::Variant (static_cast <unsigned int> (VG_CENTER));
        }

        throw Util::InitException ("stringToVGravity () : worng string literal for VGravity : [" + p + "]");
}

} //namespace
