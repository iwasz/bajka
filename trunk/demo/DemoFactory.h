/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 23, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DEMOFACTORY_H_
#define DEMOFACTORY_H_

#include "SnowflakeController.h"

struct DemoFactory {

        static Ptr <Controller::SimpleController> createFluid ();
        static Ptr <SnowflakeController> createSniezynka (const Core::String &path);


};

#	endif /* DEMOFACTORY_H_ */
