/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ScrollService.h"

namespace Service {


void ScrollService::down (/*double speed*/)
{
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << "ScrollService::down (" /*<< speed*/ << ")" << std::endl;
}

void ScrollService::up (double speed)
{
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << "ScrollService::up (" << speed << ")" << std::endl;

}

void ScrollService::left (double speed)
{
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << "ScrollService::left (" << speed << ")" << std::endl;

}

void ScrollService::right (double speed)
{
        std::cerr << "--> " << __FILE__ << "," << __FUNCTION__ << " @ " << __LINE__ << " : " << "ScrollService::right (" << speed << ")" << std::endl;

}

}
