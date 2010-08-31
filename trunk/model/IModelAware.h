/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IMODELAWARE_H_
#define IMODELAWARE_H_

#include <Pointer.h>

namespace Model {
class IModel;

/**
 * Interfejs marker - symbolizuje klasy, które mają referencję do
 * klasy IModel.
 * \ingroup Model
 */
struct IModelAware {

        virtual ~IModelAware () {}

        virtual Ptr<IModel> getModel () const = 0;
        virtual void setModel (Ptr<IModel> model) = 0;

};

} //name

#	endif /* IMODELAWARE_H_ */
