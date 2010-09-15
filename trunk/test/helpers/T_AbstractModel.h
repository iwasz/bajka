/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTMODEL_H_
#define ABSTRACTMODEL_H_

#include "TreeModel.h"

/**
 *
 */
class T_AbstractModel : public Base::TreeModel {
public:

        T_AbstractModel (std::string const &s) : name (s) {}
        virtual ~T_AbstractModel () {}

        std::string const &getName () const { return name; }

private:

        std::string name;

};

#	endif /* ABSTRACTMODEL_H_ */
