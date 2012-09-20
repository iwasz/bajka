/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IGROUPPROPERTIES_H_
#define IGROUPPROPERTIES_H_

#include <core/Object.h>

namespace Model {
//struct Padding;

/**
 * Klasa bazowa dla własciwości grup (własciwości layoutowych).
 */
class IGroupProperties : public Core::Object {
public:
        virtual ~IGroupProperties() {}

//        /**
//         * Zmniejsz ten obiekt do rozmiarów jaki zajmują jego dzieci. Ma to sens chyba tylko dla
//         * grup.
//         */
//        virtual bool getWrapContentsW () const = 0;
//
//        /**
//         * Zmniejsz ten obiekt do rozmiarów jaki zajmują jego dzieci. Ma to sens chyba tylko dla
//         * grup.
//         */
//        virtual bool getWrapContentsH () const = 0;
//
//        /**
//         * Padding.
//         */
//        virtual Padding const *getPadding () const = 0;

};

} /* namespace View */
#endif /* IGROUPPROPERTIES_H_ */
