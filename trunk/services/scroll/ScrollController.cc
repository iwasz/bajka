/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ScrollController.h"
#include "geometry/Point.h"
#include "IModel.h"

namespace Service {
namespace G = Geometry;

void ScrollController::down (double speed)
{
        // std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << "ScrollController::down (" << speed << ")" << std::endl;
        currentMove.setY (10.0 * speed);
}

void ScrollController::up (double speed)
{
//        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << "ScrollController::up (" << speed << ")" << std::endl;
        currentMove.setY (-10.0 * speed);
}

void ScrollController::left (double speed)
{
//        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << "ScrollController::left (" << speed << ")" << std::endl;
        currentMove.setX (10.0 * speed);
}

void ScrollController::right (double speed)
{
//        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << "ScrollController::right (" << speed << ")" << std::endl;
        currentMove.setX (-10.0 * speed);
}

bool ScrollController::onTimer (Event::TimerEvent *e)
{
        getModel ()->setMove (currentMove);
//        std::cerr << currentMove << std::endl;
}

}
