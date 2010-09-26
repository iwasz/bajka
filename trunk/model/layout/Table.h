/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TABLE_MODEL_H_
#define TABLE_MODEL_H_

#include "AbstractLayout.h"

namespace Model {

/**
 * Opcje ustawienia widgetów w komórkach tabeli.
 */
enum HAlign {
        LEFT, /// Jeśli widget jest węższy niż komórka tabeli, przesuń go do lewej krawędzi komórki.
        HCENTER, /// Jeśli widget jest węższy niż komórka tabeli, przesuń go na środek komórki.
        RIGHT, /// Jeśli widget jest węższy niż komórka tabeli, przesuń go do prawej krawędzi komórki.
        HSTRETCH /// Jeśli widget jest węższy niż komórka tabeli, rozciągnij go na szerokość do szerokości komórki.
};

/**
 * Opcje ustawienia widgetów w komórkach tabeli.
 */
enum VAlign {
        TOP, /// Jeśli widget jest niższy niż komórka tabeli, przesuń go do górnej krawędzi komórki.
        VCENTER, /// Jeśli widget jest niższy niż komórka tabeli, przesuń go do środka komórki.
        BOTTOM, /// Jeśli widget jest niższy niż komórka tabeli, przesuń go do dolnej krawędzi komórki.
        VSTRETCH /// Jeśli widget jest niższy niż komórka tabeli, rozciągnij go na wysokość do wysokości komórki.
};

/**
 * Jak tabela ma dobierać wysokości wierszy.
 */
enum RowHeight {
        HIGHEST_CELL_IN_ROW, /// Każdy wiersz ma wysokość sojej najwyższej komórki.
        HIGHEST_CELL_IN_TABLE, /// Kazdy wiersz ma tą samą wysokość : wysokośc najwyższego widgeta w całej tabeli.
        EXPAND_ROW /// Każdy wersz ma tą samą wysokość : wysokośc tabeli / liczbę wierszy.
};

/**
 * Jak tabela ma dobierać szerokość kolumn.
 */
enum ColWidth {
        NONE, /// Brak kolumn jako takich : następny widget zaczyna się tam, gdzie akurat wypadł koniec poprzedniego w wiersza.
        WIDEST_CELL_IN_COL, /// Są kolumny o jednakowej szerokości równej szerokości najszerszej celi w kolumnie.
        WIDEST_CELL_IN_TABLE, /// Są kolumny i mają równe szerokości równe najszerszej celi w całej tabeli.
        EXPAND_COL /// Są kolumny i mają równe szerokości równe szerokośc tabeli / columnNo.
};

/**
 * Klasa layoutowa tabela. Rozmieszcza swoje dzieci w szeregach, tak, że
 * mamy tabelkę. Dzieci są ustawiane wierszami, czyli najpier jest ustawione
 * columnNo dzieci w wierszu, a potem przechodzimy do następnego i tak rowNo
 * razy.
 *
 * Wiersze zawsze są w jednej linii, ale kolumny już nie muszą (mogą).
 *
 * Jeśli ustawiony rozmiar tabeli jest mniejszy niż obliczony w pierwszym punkcie, to zostanie ona rozepchnięta.
 * Jeśli ustawiony rozmiar tabeli jest większy niż obliczony w pierwszym punkcie, to zachowanie jest zależne od ustawień.
 * \ingroup Layout
 */
class Table : public AbstractLayout {
public:
        __c (void)
        _b ("AbstractLayout")

        Table (int c = 1, int r = 1) : columnNo (c), rowNo (r),
                hAlign (LEFT), vAlign (BOTTOM),
                rowHeight (HIGHEST_CELL_IN_ROW), colWidth (NONE) {}

        virtual ~Table () {}

        virtual void doUpdate ();

/*--------------------------------------------------------------------------*/
        /// \name Settery/gettery
        //\{

                         int getColumnNo () const { return columnNo; }
        _m (setColumnNo) void setColumnNo (int i) { columnNo = i; }

                         int getRowNo () const { return rowNo; }
        _m (setRowNo)    void setRowNo (int i) { rowNo = i; }

                         HAlign getHAlign () const { return hAlign; }
        _m (setHAlign)   void setHAlign (int i) { hAlign = (HAlign)i; } // Zmienić kiedyś z int na enum.

                         VAlign getVAlign () const { return vAlign; }
        _m (setVAlign)   void setVAlign (int i) { vAlign = (VAlign)i; }

                          RowHeight getRowHeight () const { return rowHeight; }
        _m (setRowHeight) void setRowHeight (int i) { rowHeight = (RowHeight)i; }

                          ColWidth getColWidth () const { return colWidth; }
        _m (setColWidth)  void setColWidth (int i) { colWidth = (ColWidth)i; }

        //\}

private:

        double getCellH (double highestInRow, double highestInTable, double expand);
        double getCellW (double widgetWidth, double widestInCol, double widestInTable, double expand);

private:

        int columnNo, rowNo;
        HAlign hAlign;
        VAlign vAlign;
        RowHeight rowHeight;
        ColWidth colWidth;

        _e (Table)
};

}

#	endif /* TABLE_H_ */
