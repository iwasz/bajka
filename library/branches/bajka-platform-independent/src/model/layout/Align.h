/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_LAYOUT_ALIGN_H_
#define BAJKA_LAYOUT_ALIGN_H_

namespace Model {

enum HAlign {
        HA_LEFT,
        HA_RIGHT,
        HA_CENTER
};

enum VAlign {
        VA_TOP,
        VA_BOTTOM,
        VA_CENTER,
};

enum HGravity {
        HG_LEFT,
        HG_RIGHT,
        HG_CENTER
};

enum VGravity {
        VG_TOP,
        VG_BOTTOM,
        VG_CENTER
};

} //namespace

#endif /* ALIGN_H_ */
