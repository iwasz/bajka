/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 23, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <Foreach.h>

#include "Table.h"
#include "geometry/Point.h"
#include "AbstractModel.h"

namespace Controller {
using namespace Geometry;

Table::Table (int cols, int rows)
{
        table.resize (rows);
        columnNo = cols;
        rowNo = rows;
        curCol = 0;
        curRow = 0;

        for (int i = 0; i < rows; i++) {
                table[i].resize (cols);
        }
}

/****************************************************************************/

void Table::init ()
{
        if (!rowNo || !columnNo) {
                return;
        }

        double x = 0.0;
        double y = 0.0;

        // Oblicz początkową wysokość.
        if (rowNo > 1) {
                for (int r = 1; r < rowNo; r++) {
                        y += table[r][0]->getHeight ();
                }
        }
        std::cerr << "-----" << std::endl;

        // Ustawiaj widgety.
        for (int r = 0; r < rowNo; r++) {

                if (r > 0) {
                        y -= table[r][0]->getHeight ();
                }

                for (int c = 0; c < columnNo; c++) {
                        Ptr <Model::AbstractModel> it = table[r][c];
                        it->setMove (Geometry::Point (x, y));
                        std::cerr << Geometry::Point (x, y) << std::endl;
                        x += it->getWidth ();

                        if (c == columnNo - 1) {
                                x = 0.0;
                        }
                }
        }
}

/****************************************************************************/

//void Table::setChildren (const ControllerList &list)
//{
//        SimpleController::setChildren (ControllerList ());
//
//        addChildren (list);
//}
//
///****************************************************************************/
//
//void Table::addChildren (const ControllerList &list)
//{
//        foreach (Ptr <IController> child, list) {
//                addChild (child);
//        }
//}

/****************************************************************************/

void Table::addChild (Ptr <IController> widget)
{
        SimpleController::addChild (widget);

        Ptr <Model::IModel> mod = widget->getModel ();
        Ptr <Model::AbstractModel> item = dynamic_pointer_cast <Model::AbstractModel> (mod);

        assert (item);

        if (curRow < rowNo && curCol < columnNo) {
                table[curRow][curCol] = item;
        }

        if (curCol + 1 >= columnNo) {
                curCol = 0;
                 curRow++;
        }
        else {
                curCol++;
        }
}

}
