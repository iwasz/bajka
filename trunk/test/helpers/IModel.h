/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IMODEL_H_
#define IMODEL_H_

#include "tree/ITreeSlave.h"

/**
 *
 */
struct IModel : public virtual Util::ITreeSlave <IModel> {
        virtual ~IModel () {}
        virtual std::string const &getName () const = 0;
};

#	endif /* IMODEL_H_ */
