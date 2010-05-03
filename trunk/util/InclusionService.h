/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 19, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef INCLUSIONSERVICE_H_
#define INCLUSIONSERVICE_H_

namespace Model {

struct Rectangle;
struct Point;

}

namespace Util {

struct InclusionService {

        static bool include (const Model::Rectangle &rect, const Model::Point &point);

};

}

#	endif /* INCLUSIONSERVICE_H_ */
