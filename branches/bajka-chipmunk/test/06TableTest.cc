#include <boost/test/unit_test.hpp>
#include <boost/geometry/geometry.hpp>
#include <sstream>
#include <Pointer.h>
#include <limits>


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
using namespace std;

BOOST_AUTO_TEST_SUITE (TableTest);

/**
 * Sprawdza, czy tabela rozciąga się do odpowiednich rozmiarów.
 */
BOOST_AUTO_TEST_CASE (testTableExpansion)
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
        BOOST_CHECK_EQUAL (model->getX1 (), 0);
        BOOST_CHECK_EQUAL (model->getY1 (), 0);
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

/*--------------------------------------------------------------------------*/

        model->setWidth (0);
        model->setHeight (0);
        model->setRowHeight (HIGHEST_CELL_IN_ROW);
        model->setColWidth (WIDEST_CELL_IN_TABLE);
        model->update ();
        BOOST_CHECK_EQUAL (model->getWidth (), 9);
        BOOST_CHECK_EQUAL (model->getHeight (), 8);

        model->setWidth (0);
        model->setHeight (0);
        model->setRowHeight (HIGHEST_CELL_IN_TABLE);
        model->setColWidth (WIDEST_CELL_IN_TABLE);
        model->update ();
        BOOST_CHECK_EQUAL (model->getWidth (), 9);
        BOOST_CHECK_EQUAL (model->getHeight (), 9);

        model->setWidth (0);
        model->setHeight (0);
        model->setRowHeight (EXPAND_ROW);
        model->setColWidth (WIDEST_CELL_IN_TABLE);
        model->update ();
        BOOST_CHECK_EQUAL (model->getWidth (), 9);
        BOOST_CHECK_EQUAL (model->getHeight (), 9);

/*--------------------------------------------------------------------------*/

        model->setWidth (0);
        model->setHeight (0);
        model->setRowHeight (HIGHEST_CELL_IN_ROW);
        model->setColWidth (EXPAND_COL);
        model->update ();
        BOOST_CHECK_EQUAL (model->getWidth (), 9);
        BOOST_CHECK_EQUAL (model->getHeight (), 8);

        model->setWidth (0);
        model->setHeight (0);
        model->setRowHeight (HIGHEST_CELL_IN_TABLE);
        model->setColWidth (WIDEST_CELL_IN_TABLE);
        model->update ();
        BOOST_CHECK_EQUAL (model->getWidth (), 9);
        BOOST_CHECK_EQUAL (model->getHeight (), 9);

        model->setWidth (0);
        model->setHeight (0);
        model->setRowHeight (EXPAND_ROW);
        model->setColWidth (WIDEST_CELL_IN_TABLE);
        model->update ();
        BOOST_CHECK_EQUAL (model->getWidth (), 9);
        BOOST_CHECK_EQUAL (model->getHeight (), 9);

// A jeśli tabela ma ustawiony już większy rozmiar, to powinien on już zostać.

        model->setWidth (10);
        model->setHeight (10);
        model->setRowHeight (HIGHEST_CELL_IN_ROW);
        model->setColWidth (NONE);
        model->update ();
        BOOST_CHECK_EQUAL (model->getWidth (), 10);
        BOOST_CHECK_EQUAL (model->getHeight (), 10);
}

/**
 * Sprawdza layout.
 */
BOOST_AUTO_TEST_CASE (testTableLayout)
{
        // Tworzymy tabelę (widget) z modelem
        EmptyWidget table;
        Ptr <Table> model = Ptr <Table> (new Table (2, 2));
        model->setAlwaysUpdate (true);
        table.setModel (model);

        // Dodajemy do tabeli pudełka o różnych rozmiarach.
        Ptr <IWidget> w1 = Ptr <IWidget> (new EmptyWidget);
        Ptr <Model::Box> m1 = Ptr <Model::Box> (new Model::Box (0, 0, 2, 2));
        w1->setModel (m1);
        table.addChild (w1);

        Ptr <IWidget> w2 = Ptr <IWidget> (new EmptyWidget);
        Ptr <Model::Box> m2 = Ptr <Model::Box> (new Model::Box (0, 0, 3, 3));
        w2->setModel (m2);
        table.addChild (w2);

        Ptr <IWidget> w3 = Ptr <IWidget> (new EmptyWidget);
        Ptr <Model::Box> m3 = Ptr <Model::Box> (new Model::Box (0, 0, 4, 4));
        w3->setModel (m3);
        table.addChild (w3);

        Ptr <IWidget> w4 = Ptr <IWidget> (new EmptyWidget);
        Ptr <Model::Box> m4 = Ptr <Model::Box> (new Model::Box (0, 0, 5, 5));
        w4->setModel (m4);
        table.addChild (w4);


        model->setHAlign (LEFT);
        model->setVAlign (BOTTOM);
        model->setWidth (0);
        model->setHeight (0);
        model->setRowHeight (HIGHEST_CELL_IN_ROW);
        model->setColWidth (NONE);
        model->update ();
        BOOST_CHECK_EQUAL (m1->getMatrix ().getTransformed (m1->getLL ()), Point (0, 5));
        BOOST_CHECK_EQUAL (m1->getMatrix ().getTransformed (m1->getUR ()), Point (2, 7));
        BOOST_CHECK_EQUAL (m2->getMatrix ().getTransformed (m2->getLL ()), Point (2, 5));
        BOOST_CHECK_EQUAL (m2->getMatrix ().getTransformed (m2->getUR ()), Point (5, 8));
        BOOST_CHECK_EQUAL (m3->getMatrix ().getTransformed (m3->getLL ()), Point (0, 0));
        BOOST_CHECK_EQUAL (m3->getMatrix ().getTransformed (m3->getUR ()), Point (4, 4));
        BOOST_CHECK_EQUAL (m4->getMatrix ().getTransformed (m4->getLL ()), Point (4, 0));
        BOOST_CHECK_EQUAL (m4->getMatrix ().getTransformed (m4->getUR ()), Point (9, 5));
}

/**
 * Sprawdza layout.
 */
BOOST_AUTO_TEST_CASE (testTableLayout2)
{
        // Tworzymy tabelę (widget) z modelem
        EmptyWidget table;
        Ptr <Table> model = Ptr <Table> (new Table (2, 2));
        model->setAlwaysUpdate (true);
        table.setModel (model);

        // Dodajemy do tabeli pudełka o różnych rozmiarach.
        Ptr <IWidget> w1 = Ptr <IWidget> (new EmptyWidget);
        Ptr <Model::Box> m1 = Ptr <Model::Box> (new Model::Box (0, 0, 2, 2));
        w1->setModel (m1);
        table.addChild (w1);

        Ptr <IWidget> w2 = Ptr <IWidget> (new EmptyWidget);
        Ptr <Model::Box> m2 = Ptr <Model::Box> (new Model::Box (0, 0, 3, 3));
        w2->setModel (m2);
        table.addChild (w2);

        Ptr <IWidget> w3 = Ptr <IWidget> (new EmptyWidget);
        Ptr <Model::Box> m3 = Ptr <Model::Box> (new Model::Box (0, 0, 4, 4));
        w3->setModel (m3);
        table.addChild (w3);

        Ptr <IWidget> w4 = Ptr <IWidget> (new EmptyWidget);
        Ptr <Model::Box> m4 = Ptr <Model::Box> (new Model::Box (0, 0, 5, 5));
        w4->setModel (m4);
        table.addChild (w4);

        model->setHAlign (LEFT);
        model->setVAlign (TOP);
        model->setWidth (0);
        model->setHeight (0);
        model->setRowHeight (HIGHEST_CELL_IN_ROW);
        model->setColWidth (NONE);
        model->update ();
        BOOST_CHECK_EQUAL (m1->getMatrix ().getTransformed (m1->getLL ()), Point (0, 6));
        BOOST_CHECK_EQUAL (m1->getMatrix ().getTransformed (m1->getUR ()), Point (2, 8));
        BOOST_CHECK_EQUAL (m2->getMatrix ().getTransformed (m2->getLL ()), Point (2, 5));
        BOOST_CHECK_EQUAL (m2->getMatrix ().getTransformed (m2->getUR ()), Point (5, 8));
        BOOST_CHECK_EQUAL (m3->getMatrix ().getTransformed (m3->getLL ()), Point (0, 1));
        BOOST_CHECK_EQUAL (m3->getMatrix ().getTransformed (m3->getUR ()), Point (4, 5));
        BOOST_CHECK_EQUAL (m4->getMatrix ().getTransformed (m4->getLL ()), Point (4, 0));
        BOOST_CHECK_EQUAL (m4->getMatrix ().getTransformed (m4->getUR ()), Point (9, 5));
}

BOOST_AUTO_TEST_SUITE_END ();
