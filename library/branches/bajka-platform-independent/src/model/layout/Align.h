/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_LAYOUT_ALIGN_H_
#define BAJKA_LAYOUT_ALIGN_H_

#include <core/variant/Variant.h>

namespace Model {

/**
 * HAlign
 */
enum HAlign {
        HA_LEFT,
        HA_RIGHT,
        HA_CENTER
};

/**
 * Do konwersji na wariant, użyteczne dla kontenera.
 */
extern Core::Variant stringToHAlign (std::string const &p);

/**
 * VAlign
 */
enum VAlign {
        VA_TOP,
        VA_BOTTOM,
        VA_CENTER,
};

/**
 * Do konwersji na wariant, użyteczne dla kontenera.
 */
extern Core::Variant stringToVAlign (std::string const &p);

/**
 * HGravity
 */
enum HGravity {
        HG_LEFT,
        HG_RIGHT,
        HG_CENTER
};

/**
 * Do konwersji na wariant, użyteczne dla kontenera.
 */
extern Core::Variant stringToHGravity (std::string const &p);

/**
 * VGravity
 */
enum VGravity {
        VG_TOP,
        VG_BOTTOM,
        VG_CENTER
};

/**
 * Do konwersji na wariant, użyteczne dla kontenera.
 */
extern Core::Variant stringToVGravity (std::string const &p);

} //namespace

#endif /* ALIGN_H_ */
