/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TABLEGROUPPROPERTIES_H_
#define TABLEGROUPPROPERTIES_H_

#include "LinearGroupProperties.h"

namespace Model {

class TableGroupProperties : public LinearGroupProperties {
public:
        C__ (void)
        b_ ("LinearGroupProperties")

        virtual ~TableGroupProperties () {}

        E_ (TableGroupProperties)

};

} /* namespace Model */
#endif /* TABLEGROUPPROPERTIES_H_ */
