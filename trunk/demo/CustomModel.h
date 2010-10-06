/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CUSTOMMODEL_H_
#define CUSTOMMODEL_H_

#include "../model/Box.h"

/**
 * Model do celów testowych. W metodzie init wykonuje jakieś dodatkowe
 * czary.
 */
class CustomModel : public Model::Box {
public:
        __c (void)
        _b ("Model::Box")

        virtual ~CustomModel () {}
        _m (init) void init ();

        _e (CustomModel)
};

#	endif /* CUSTOMMODEL_H_ */
