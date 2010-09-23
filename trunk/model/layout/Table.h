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
 * Klasa layoutowa tabela. Rozmieszcza swoje dzieci w szeregach, tak, że
 * mamy tabelkę. Dzieci są ustawiane wierszami, czyli najpier jest ustawione
 * columnNo dzieci w wierszu, a potem przechodzimy do następnego i tak rowNo
 * razy.
 * \ingroup Layout
 */
class Table : public AbstractLayout {
public:
        __c (void)
        _b ("AbstractLayout")

        Table (int c = 1, int r = 1) : columnNo (c), rowNo (r) {}
        virtual ~Table () {}

        virtual void doUpdate ();

/*--------------------------------------------------------------------------*/
        /// \name Settery/gettery
        //\{

                         int getColumnNo () const { return columnNo; }
        _m (setColumnNo) void setColumnNo (int i) { columnNo = i; }

                         int getRowNo () const { return rowNo; }
        _m (setRowNo)    void setRowNo (int i) { rowNo = i; }

        //\}

private:

        int columnNo, rowNo;

        _e (Table)
};

}

#	endif /* TABLE_H_ */
