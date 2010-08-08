/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 21, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTMAPPING_H_
#define ABSTRACTMAPPING_H_

#include "IMapping.h"
#include "sequence/ISequence.h"

namespace Controller {

/**
 * Mediator between ISequence of some type and some arbitrary object ModelType.
 * \ingroup Mapping
 */
template <typename ParameterType, typename ModelType>
class AbstractMapping : public IMapping {
public:

        virtual ~AbstractMapping () {}

        Ptr<ModelType> getModel () const { return model; }
        void setModel (Ptr<ModelType> model) { this->model = model; }

        /**
         * Zwraca sekwencję (obiekt typu ISequence) związany z tym obiektem IMapping.
         * @return Obiekt typu ISequence.
         */
        Ptr<ISequence<ParameterType> > getSequence () const { return sequence; }

        /**
         * Ustawia sekwencję (obiekt typu ISequence) związany z tym obiektem IMapping.
         * @param sequence Obiekt typu ISequence.
         */
        void setSequence (Ptr<ISequence<ParameterType> > sequence) { this->sequence = sequence; }

protected:

        AbstractMapping () {}

private:

        Ptr <ModelType> model;
        Ptr <ISequence <ParameterType> > sequence;
};

}

#	endif /* ABSTRACTMAPPING_H_ */
