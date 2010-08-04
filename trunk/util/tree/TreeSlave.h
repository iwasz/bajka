/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TREESLAVE_H_
#define TREESLAVE_H_

#include "TreeSlaveIterator.h"

namespace Util {

/**
 * Slave dla struktury drzewiastej.
 */
template <typename T, typename TreeMasterType, typename Extractor>
class TreeSlave {
public:

        typedef T Element;
        typedef typename std::list <T> ElementList;
        typedef TreeSlaveIterator <T, TreeMasterType, Extractor> Iterator;
        typedef TreeMasterType * TreeMasterPtr;

        TreeSlave () : treeMaster (NULL) {}
        virtual ~TreeSlave () {}

        TreeMasterPtr getTreeMaster () { return treeMaster; }
        void setTreeMaster (TreeMasterPtr t) { treeMaster = t; }

        Element getParent () { return extractor (treeMaster->getParent ()); }

        const ElementList &getChildren () const;

        Iterator begin () { return Iterator (treeMaster->begin ()); }
        Iterator end () { return Iterator (treeMaster->end ()); }

private:

        Extractor extractor;
        TreeMasterPtr treeMaster;
};

template <typename T, typename TreeMasterType, typename Extractor>
typename TreeSlave<T, TreeMasterType, Extractor>::ElementList const &
TreeSlave <T, TreeMasterType, Extractor>::getChildren () const
{
        ElementList ret;
        std::for_each (begin (), end (), std::mem_fun (&ElementList::push_back));
        return ret;
}

} // namespace Util

#       endif /* TREESLAVEITERATOR_H_ */
