/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ITREEMASTERSLAVE_H_
#define ITREEMASTERSLAVE_H_

#include "ITreeMaster.h"
#include "ITreeSlave.h"

namespace Util {

/**
 * Interfejs zbiorczy zawierający w sobie ITreeMaster i ITreeSlave.
 * \ingroup Tree
 */
// Zbiera typedefy do kupy, zeby nie było ambiguity w pod-klasie.
template <typename Element>
struct ITreeMasterSlave :
        public ITreeMaster <Element>,
        public ITreeSlave <Element> {

        // Odpowiadające typy z ITreeMaster są takie same.
        typedef typename ITreeSlave <Element>::ChildBaseType ChildBaseType;
        typedef typename ITreeSlave <Element>::ParentBaseType ParentBaseType;
        typedef typename ITreeSlave <Element>::ChildType ChildType;
        typedef typename ITreeSlave <Element>::ChildConstType ChildConstType;
        typedef typename ITreeSlave <Element>::ParentType ParentType;
        typedef typename ITreeSlave <Element>::ParentConstType ParentConstType;
        typedef typename ITreeSlave <Element>::iterator iterator;
        typedef typename ITreeSlave <Element>::const_iterator const_iterator;
        typedef typename ITreeSlave <Element>::ChildList ChildList;

        virtual ~ITreeMasterSlave () {}
};

}

#	endif /* ITREEMASTERSLAVE_H_ */
