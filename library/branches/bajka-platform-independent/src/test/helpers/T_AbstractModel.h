/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef T_ABSTRACTMODEL_H_
#define T_ABSTRACTMODEL_H_

#include "model/Box.h"

/**
 *
 */
class T_AbstractModel : public Model::Box {
public:

        T_AbstractModel (std::string const &s) : name (s) {}
        virtual ~T_AbstractModel () {}

        std::string const &getName () const { return name; }

private:

        std::string name;

};

#	endif /* ABSTRACTMODEL_H_ */
