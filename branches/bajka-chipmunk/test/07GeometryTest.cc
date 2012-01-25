#include <boost/test/unit_test.hpp>
#include <boost/geometry/geometry.hpp>
#include <sstream>
#include <Pointer.h>

#include "IModel.h"
#include "../model/Box.h"
#include "../geometry/Ring.h"

// Procentowy dopuszcalny błąd w porównaniach doubli.
#define CLOSE 0.0000001

using namespace boost;
using namespace boost::geometry;

using namespace Geometry;

namespace M = Model;
namespace C = Controller;

/****************************************************************************/

//void CHECK_POINT (Geometry::Point const &p, double x, double y)
#define CHECK_POINT(p,x,y)                                                \
{                                                                         \
        if ((x) != 0.0) {                                                 \
                BOOST_CHECK_CLOSE ((p).getX (), (x), CLOSE);              \
        }                                                                 \
        else {                                                            \
                BOOST_CHECK_CLOSE ((p).getX () + 1, (x) + 1, CLOSE);      \
        }                                                                 \
                                                                          \
        if ((y) != 0.0) {                                                 \
                BOOST_CHECK_CLOSE ((p).getY (), (y), CLOSE);              \
        }                                                                 \
        else {                                                            \
                BOOST_CHECK_CLOSE ((p).getY () + 1, (y) + 1, CLOSE);      \
        }                                                                 \
}

/****************************************************************************/

BOOST_AUTO_TEST_SUITE (GeometryTest);

/**
 *
 */
BOOST_AUTO_TEST_CASE (test1)
{
        Ring r;

        boost::range_iterator<Geometry::Ring>::type i = boost::begin (r);
}

BOOST_AUTO_TEST_SUITE_END ();
