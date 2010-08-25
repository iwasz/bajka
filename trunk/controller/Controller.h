/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 21, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

/**
 * \defgroup Kontroler
 * Struktura kontrolerów.
 * \{
 * \defgroup Sequence
 * Sekwencje generujące wrtości. Są to klasy o prostym interfejsie służące do generowania wartości.
 * \defgroup Mapping
 * Mapuje obiekt typu Controller::ISequence na model Model::IModel. Ponieważ sekwencje zwracają kolejne
 * generowane przez siebie wartości różnych typów, potrzebna była abstrakcja, ktora te wartości przekaże
 * w jakiś konkretny sposób do modelu.
 * \}
 */

#include "IController.h"
#include "SimpleController.h"
#include "Table.h"

#	endif /* CONTROLLER_H_ */
