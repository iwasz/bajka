/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 23, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TABLE_H_
#define TABLE_H_

#include <vector>
#include "SimpleController.h"

namespace Controller {

/**
 * Layout thing.
 */
class Table : public Controller::SimpleController {
public:
        __c (int, int)
        _b ("SimpleController")

        typedef std::vector <Ptr <Model::AbstractModel> > RowType;
        typedef std::vector <RowType> TableType;

        Table (int columnNo, int rowNo);
        virtual ~Table () {}

        void init ();

        virtual void setChildren (const ControllerList &list);
        virtual void addChildren (const ControllerList &list);
        virtual void addChild (Ptr <IController> widget);

private:

        TableType table;
        int columnNo, rowNo;
        int curCol, curRow;

        _e (Table)
};

}

#	endif /* TABLE_H_ */
