/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IMODEL_H_
#define IMODEL_H_

#include "ITreeModel.h"

/**
 *
 */
struct T_IModel : public Base::ITreeModel {
        virtual ~T_IModel () {}
        virtual std::string const &getName () const = 0;
};

#	endif /* IMODEL_H_ */
