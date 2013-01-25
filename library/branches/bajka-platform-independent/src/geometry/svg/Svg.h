/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_GEOM_SVG_H_
#define BAJKA_GEOM_SVG_H_

#include <string>
#include <core/Typedefs.h>

namespace Common {
class DataSource;
}

namespace Geometry {

class Svg {
public:
        static Core::VariantMap parseFile (Common::DataSource *ds, std::string const &path);
        static Core::VariantMap parseFile (std::string const &path);

#ifndef NDEBUG
        void test ();
#endif
};

} /* namespace Geometry */
#endif /* SVG_H_ */
