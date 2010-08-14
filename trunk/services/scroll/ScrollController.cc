/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ScrollController.h"

namespace Service {


void ScrollController::down (double speed)
{
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << "ScrollController::down (" << speed << ")" << std::endl;
}

void ScrollController::up (double speed)
{
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << "ScrollController::up (" << speed << ")" << std::endl;

}

void ScrollController::left (double speed)
{
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << "ScrollController::left (" << speed << ")" << std::endl;

}

void ScrollController::right (double speed)
{
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << "ScrollController::right (" << speed << ")" << std::endl;

}
void ScrollController::stop ()
{
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << "SCROLL-STOP" << std::endl;
}

}
