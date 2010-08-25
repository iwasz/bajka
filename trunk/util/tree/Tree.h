/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TREE_H_
#define TREE_H_

/**
 * \defgroup Tree
 * \ingroup Util
 * Uogólnienie struktury drzewiastej. W tym module znajdują się klasy implementujące ogólną strukturę
 * drzewiastą. Pomysł polega na tym, że dziedzicząc z klasy Util::TreeMaster definiujemy główną hierarchię
 * drzewaistą, a dziedzicząc z Util::TreeSlave poboczną. Obiekty należące do głownej hierarchii można w
 * sobie zagnieżdżać (tworzyć z nich drzewo - czyli ustawiać relację rodzic-potomek), i ta struktura
 * automatycznie znajduje odzwierciedlenie w strukturze obiektow slave.
 */

#include "Extractors.h"
#include "TreeMaster.h"
#include "TreeSlave.h"
#include "TreeSlaveIterator.h"

#	endif /* TREE_H_ */
