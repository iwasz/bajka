/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTMODEL_H_
#define ABSTRACTMODEL_H_

#include <string>
#include "IModel.h"
#include "tree/TreeSlave.h"
#include "Pointer.h"

/**
 *
 */
class AbstractModel :
        public IModel,
        public Util::TreeSlave <IModel> {
public:

        AbstractModel (std::string const &s) : name (s) {}
        virtual ~AbstractModel () {}

        std::string const &getName () const { return name; }

private:

        std::string name;

};

#	endif /* ABSTRACTMODEL_H_ */
