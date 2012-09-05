/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IRESOURCEMANAGER_H_
#define IRESOURCEMANAGER_H_

#include <string>
#include <Pointer.h>

namespace View {

/**
 *
 */
//struct Buffer {
//
//        Buffer () : data (NULL), length (0) {}
//
//        void const *data;
//        unsigned int length;
//};

/**
 *
 */
class IResourceManager {
public:
        virtual ~IResourceManager () {}

        Ptr <std::string> getText (std::string const &id) const;

};

} /* namespace View */

#	endif /* IRESOURCEMANAGER_H_ */
