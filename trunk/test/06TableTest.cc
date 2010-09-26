#include <boost/test/unit_test.hpp>
#include <boost/geometry/geometry.hpp>
#include <sstream>
#include <Pointer.h>


#include "geometry/Geometry.h"
#include "IModel.h"
#include "../controller/SimpleController.h"
#include "../model/layout/Table.h"
#include "../view/EmptyWidget.h"

using namespace boost;
using namespace boost::geometry;

using namespace Geometry;
using namespace Model;
using namespace Controller;
using namespace View;

BOOST_AUTO_TEST_SUITE (TableTest);

/**
 *
 */
BOOST_AUTO_TEST_CASE (testPoint)
{
        // Tworzymy tabelę (widget) z modelem
        EmptyWidget table;
        Ptr <Table> model = Ptr <Table> (new Table (3, 3));
        model->setAlwaysUpdate (true);
        table.setModel (model);

        // Dodajemy do tabeli pudełka o różnych rozmiarach.
        {
                Ptr <IWidget> w = Ptr <IWidget> (new EmptyWidget);
                w->setModel (Ptr <IModel> (new Model::Box (0, 0, 3, 3)));
                table.addChild (w);
        }
        {
                Ptr <IWidget> w = Ptr <IWidget> (new EmptyWidget);
                w->setModel (Ptr <IModel> (new Model::Box (0, 0, 2, 2)));
                table.addChild (w);
        }
        {
                Ptr <IWidget> w = Ptr <IWidget> (new EmptyWidget);
                w->setModel (Ptr <IModel> (new Model::Box (0, 0, 1, 1)));
                table.addChild (w);
        }
        {
                Ptr <IWidget> w = Ptr <IWidget> (new EmptyWidget);
                w->setModel (Ptr <IModel> (new Model::Box (0, 0, 1, 1)));
                table.addChild (w);
        }
        {
                Ptr <IWidget> w = Ptr <IWidget> (new EmptyWidget);
                w->setModel (Ptr <IModel> (new Model::Box (0, 0, 2, 2)));
                table.addChild (w);
        }
        {
                Ptr <IWidget> w = Ptr <IWidget> (new EmptyWidget);
                w->setModel (Ptr <IModel> (new Model::Box (0, 0, 3, 3)));
                table.addChild (w);
        }
        {
                Ptr <IWidget> w = Ptr <IWidget> (new EmptyWidget);
                w->setModel (Ptr <IModel> (new Model::Box (0, 0, 2, 2)));
                table.addChild (w);
        }
        {
                Ptr <IWidget> w = Ptr <IWidget> (new EmptyWidget);
                w->setModel (Ptr <IModel> (new Model::Box (0, 0, 2, 2)));
                table.addChild (w);
        }
        {
                Ptr <IWidget> w = Ptr <IWidget> (new EmptyWidget);
                w->setModel (Ptr <IModel> (new Model::Box (0, 0, 2, 2)));
                table.addChild (w);
        }

        // Ustawienia domyślne.
        model->setHAlign (LEFT);
        model->setVAlign (BOTTOM);


        model->setWidth (0);
        model->setHeight (0);
        model->setRowHeight (HIGHEST_CELL_IN_ROW);
        model->setColWidth (NONE);
        model->update ();
        BOOST_CHECK_EQUAL (model->getWidth (), 6);
        BOOST_CHECK_EQUAL (model->getHeight (), 8);

        model->setWidth (0);
        model->setHeight (0);
        model->setRowHeight (HIGHEST_CELL_IN_TABLE);
        model->setColWidth (NONE);
        model->update ();
        BOOST_CHECK_EQUAL (model->getWidth (), 6);
        BOOST_CHECK_EQUAL (model->getHeight (), 9);

        model->setWidth (0);
        model->setHeight (0);
        model->setRowHeight (EXPAND_ROW);
        model->setColWidth (NONE);
        model->update ();
        BOOST_CHECK_EQUAL (model->getWidth (), 6);
        BOOST_CHECK_EQUAL (model->getHeight (), 9);

        /*--------------------------------------------------------------------------*/

        model->setWidth (0);
        model->setHeight (0);
        model->setRowHeight (HIGHEST_CELL_IN_ROW);
        model->setColWidth (WIDEST_CELL_IN_COL);
        model->update ();
        BOOST_CHECK_EQUAL (model->getWidth (), 8);
        BOOST_CHECK_EQUAL (model->getHeight (), 8);

        model->setWidth (0);
        model->setHeight (0);
        model->setRowHeight (HIGHEST_CELL_IN_TABLE);
        model->setColWidth (WIDEST_CELL_IN_COL);
        model->update ();
        BOOST_CHECK_EQUAL (model->getWidth (), 8);
        BOOST_CHECK_EQUAL (model->getHeight (), 9);

        model->setWidth (0);
        model->setHeight (0);
        model->setRowHeight (EXPAND_ROW);
        model->setColWidth (WIDEST_CELL_IN_COL);
        model->update ();
        BOOST_CHECK_EQUAL (model->getWidth (), 8);
        BOOST_CHECK_EQUAL (model->getHeight (), 9);
}

BOOST_AUTO_TEST_SUITE_END ();
