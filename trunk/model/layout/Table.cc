/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <algorithm>
#include <numeric>

#include "Table.h"
#include "geometry/Point.h"
#include "AbstractModel.h"

namespace Model {
using namespace Geometry;
using namespace std;

/****************************************************************************/

void Table::doUpdate ()
{
#if 0
        std::cerr << "Table=" << (unsigned long int)this << std::endl;
#endif

        if (!rowNo || !columnNo) {
                return;
        }

        // Największa szerokość widgeta spośród wszystkich w tabeli.
        double maxCellWidthPerTable = 0.0, maxCellHeightPerTable = 0.0;

        // Największa wysokośc widgeta per wiersz.
        double maxCellHeightPerRow[rowNo];
        fill (maxCellHeightPerRow, maxCellHeightPerRow + rowNo, 0.0);

        // Najwięsza szerokość widgeta per kolumna.
        double maxCellWidthPerCol[columnNo];
        fill (maxCellWidthPerCol, maxCellWidthPerCol + columnNo, 0.0);

        // Szerokość i wysokość tabeli jeśli kolumny mają być ściśnięte (nie są w jednej linii).
        double tableWShrinked = 0.0, tableHShrinked = 0.0;
        // Szerokość i wysokość całej tabeli jeśli kolumny mają być rozciągnięte (tak, że faktycznie towrzą kolumny w jednej linii).
        double expRowW = 0.0, expColH = 0.0;

        // Aktualny wiersz i aktualna kolumna.
        int curR = 0;
        int curC = 0;

        int cnt = 0;
        int elems = columnNo * rowNo;
        double curRowW = 0;

        // Teraz ustalamy rożne warianty szerokości i wysokości tabeli rozciągnie się jeśli dzieci się nie mieszczą.
        // Dzieci moze być więcej niż kolumn * wierszy. Nadmiarowych nie bierzemy pod uwagę.
        for (iterator i = begin (); i != end () && cnt < elems; ++i, ++cnt) {

                double bbh = (*i)->getBoundingBox ().getHeight ();
                double bbw = (*i)->getBoundingBox ().getWidth ();

#if 0
                std::cerr << "Child bbh=" << bbh << ", bbw=" << bbw << std::endl;
#endif

                // Ogólnie największa szerokość/wysokość
                maxCellWidthPerTable = max (bbw, maxCellWidthPerTable);
                maxCellHeightPerTable = max (bbh, maxCellHeightPerTable);

                // Największa szerokośc/wysokoś per wiersz/kolumna.
                maxCellHeightPerRow[curR] = max (bbh, maxCellHeightPerRow[curR]);
                maxCellWidthPerCol[curC] = max (bbw, maxCellWidthPerCol[curC]);

                curRowW += bbw;

                // Zwiększ aktualny indeks wiersza i kolumny. Idź wierszami.
                if (++curC >= columnNo) {

                        // Przejście do następnego wiersza.
                        curC = 0;
                        tableWShrinked = max (curRowW, tableWShrinked);
                        curRowW = 0;
                        tableHShrinked += maxCellHeightPerRow[curR];
                        expRowW += maxCellWidthPerTable;

                        if (++curR >= rowNo) {
                                break;
                        }
                }
        }

        expColH = tableHShrinked;

        double tableH;
        double tableW;

        if (colWidth == NONE) {
                tableW = max (getWidth (), tableWShrinked);
        }
        else if (colWidth == WIDEST_CELL_IN_COL) {
                tableW = max (getWidth (), accumulate (maxCellWidthPerCol, maxCellWidthPerCol + columnNo, 0.0));
        }
        else if (colWidth == WIDEST_CELL_IN_TABLE || colWidth == EXPAND_COL) {
                tableW = max (getWidth (), maxCellWidthPerTable * columnNo);
        }

        if (rowHeight == HIGHEST_CELL_IN_ROW) {
                tableH = max (getHeight (), tableHShrinked);
        }
        else if (rowHeight == HIGHEST_CELL_IN_TABLE || rowHeight == EXPAND_ROW) {
                tableH = max (getHeight (), maxCellHeightPerTable * rowNo);
        }

        setWidth (tableW);
        setHeight (tableH);

#if 0
        std::cerr << "Table dimensions : " << tableW << ", " << tableH << std::endl;
#endif

        // Szerokość i wysokośc kolumn gdy robimy expand.
        double expRowH = tableH / rowNo;
        double expColW = tableW / columnNo;

        // W tym miejscu mamy już obliczoną wysokość/szerokość tabeli na 3 rózne sposoby. Wiemy z którego miejsca zacząć rysować.

        curC = curR = 0;
        double cellH = getCellH (maxCellHeightPerRow[curR], maxCellHeightPerTable, expRowH);
        double cellW = 0;

        // Początkowe x, y ustawione na górny lewy róg
        double x = 0.0;
        double y = tableH - cellH;

/*--------------------------------------------------------------------------*/

        for (iterator i = begin (); i != end (); ++i) {

                Geometry::Box bb = (*i)->getBoundingBox ();
                double bbh = bb.getHeight ();
                double bbw = bb.getWidth ();

                cellW = getCellW (bbw, maxCellWidthPerCol[curC], maxCellWidthPerTable, expColW);

                Point p;

                if (hAlign == LEFT /*|| hAlign == HSTRETCH*/) {
                        p.setX (x);
                }
                else if (hAlign == RIGHT) {
                        p.setX (x + (cellW - bbw));
                }
                else { // CENTER
                        p.setX (x + (cellW - bbw) / 2.0);
                }

                if (vAlign == BOTTOM /*|| vAlign == VSTRETCH*/) {
                        p.setY (y);
                }
                else if (vAlign == TOP) {
                        p.setY (y + (cellH - bbh));
                }
                else { // CENTER
                        p.setY (y + (cellH - bbh) / 2.0);
                }

                // TODO Powinno być bezwzględnie, ale w stosunku do BBox.
                (*i)->setMove (p - bb.getLL ());

                x += cellW;

                // Zwiększ aktualny indeks wiersza i kolumny. Idź wierszami.
                if (++curC >= columnNo) {
                        curC = 0;

                        if (++curR >= rowNo) {
                                break;
                        }

                        cellH = getCellH (maxCellHeightPerRow[curR], maxCellHeightPerTable, expRowH);
                        x = 0;
                        y -= cellH;
                }
        }

}

/****************************************************************************/

// Oblicz wysokość aktualnej komórki.
double Table::getCellH (double highestInRow, double highestInTable, double expand)
{
        if (rowHeight == HIGHEST_CELL_IN_ROW) {
                return highestInRow;
        }
        else if (rowHeight == HIGHEST_CELL_IN_TABLE) {
                return highestInTable;
        }
        else { // EXPAND
                return expand;
        }
}

/****************************************************************************/

// Oblicz szerokośc aktualnej komórki.
double Table::getCellW (double widgetWidth, double widestInCol, double widestInTable, double expand)
{
        if (colWidth == NONE) {
                return widgetWidth;
        }
        else if (colWidth == WIDEST_CELL_IN_COL) {
                return widestInCol;
        }
        else if (colWidth == WIDEST_CELL_IN_TABLE) {
                return widestInTable;
        }
        else { // EXPAND
                return expand;
        }
}

} // namespace
