/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IMAGE_MODEL_H_
#define IMAGE_MODEL_H_

#include <string>
#include <Reflection.h>
#include "Box.h"

namespace Model {

/**
 * TODO To powinno dziedziczyć z shape
 */
class Image : public Model::Box {
public:
        __c (void)
        _b ("Model::Box")

        virtual ~Image () {}

        virtual Core::String getPath() const { return path; }
        _m (setPath) virtual void setPath (Core::String const &path) { this->path = path; }

private:

        Core::String path;
        _e (Model::Image);
};

}

#	endif /* IMAGE_H_ */
