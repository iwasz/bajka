/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_TREESLAVE_H_
#define BAJKA_TREESLAVE_H_

#include <Pointer.h>

#include "TreeSlaveIterator.h"
#include "TreeMaster.h"
#include "Extractors.h"

namespace Util {

/**
 * Slave dla struktury drzewiastej.
 * \ingroup Tree
 */
template <typename SlaveElement,
        typename MasterElement,
        Ptr <SlaveElement> (MasterElement::*ptrToMemberFunction)() const>

class TreeSlave {
public:

/*------typedefy------------------------------------------------------------*/

        typedef TreeMaster <MasterElement> TreeMasterType;
        typedef TreeMasterType *TreeMasterPtr;

        typedef MasterElement *MasterElementPtr;

        typedef SlaveElement ElementType;
        typedef Ptr <SlaveElement> ChildType;
        typedef Ptr <SlaveElement> ParentType;

        typedef ConstMemFunExtractor <SlaveElement,
                                MasterElement,
                                ptrToMemberFunction> Extractor;

        typedef typename std::list <ChildType> ElementList;
        typedef TreeSlaveIterator <ChildType, TreeMasterType, Extractor> iterator;

/*--------------------------------------------------------------------------*/

        TreeSlave () : treeMaster (NULL) {}
        virtual ~TreeSlave () {}

/*------gettery/settery-----------------------------------------------------*/

        TreeMasterPtr getTreeMaster () { return treeMaster; }
        void setTreeMaster (TreeMasterPtr t) { treeMaster = t; }

        ParentType getParent () const { return extractor (treeMaster->getParent ()); }

        const ElementList &getChildren () const;

        iterator begin () { return iterator (treeMaster->begin ()); }
        iterator end () { return iterator (treeMaster->end ()); }

private:

        Extractor extractor;
        TreeMasterPtr treeMaster;
};

template <typename SlaveElement,
        typename MasterElement,
        Ptr <SlaveElement> (MasterElement::*ptrToMemberFunction)() const>

typename TreeSlave <SlaveElement, MasterElement, ptrToMemberFunction>::ElementList const &

TreeSlave <SlaveElement, MasterElement, ptrToMemberFunction>::getChildren () const
{
        ElementList ret;
        std::for_each (begin (), end (), std::mem_fun (&ElementList::push_back));
        return ret;
}

} // namespace Util

#       endif /* TREESLAVEITERATOR_H_ */
