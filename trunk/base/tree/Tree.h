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

/**
 * \mainpage
 * \section Zawieranie
 * \subsection Ogólnie
 * Zawieranie, czyli implementacja wzoraca projektowego "composite" jest realizowane w Bajce na dwóch
 * płaszczyznach. Przede wszystkim kontrolery (instancje klasy SimpleController) mogą zawierać inne
 * kontyrolery (obiekty typu IController). Czyli '''kontrolery mogą tworzyć strukturę drzewistą'''. Każdy
 * kontroler może zawierać jeden model (obiekt typu IModel), oraz jeden widget (obiekt klasy IWidget). I tu
 * pojawia się druga płaszczyzna, bowiem widgety (czyli to V w MVC) też można zagnieżdżać. Instancje klasy
 * AbstractWidget mogą zawierać dowolnie dużo obiektów klasy IWidget i '''wówczas także tworzą strukturę
 * drzewisatą'''.
 *
 * Dziecko może mieć tylko jednego rodzica, co oznacza, że nie można dodać jednego kontrolera do dwóch
 * innych (da się, ale pierwszy się zamaże).
 *
 * Struktura drzewiasta kontrolerów tworzy niejawną, odpowiadającą strukturę drzewiastą widgetów i modeli.
 * Analogicznie jest z widgetami, które same w sonie można układac w drzewa i wówczas mamy też odpowiadające
 * drzewo modeli stworzone niejawnie. Efekt jest taki, że po zagnieżdżeniu kontrolerów ich '''modele mogą
 * iterować po modelach-potomkach, a wdgety mogą iterować po widgetach-potomkach'''. Analogicznie z
 * zagnieżdżaniem samych widgetów.
 *
 * \subsection Implementacja
 * Zawieranie jest zaimplementowane za pomocą dwóch głownych szablonów klas TreeMaster i TreeSlave (jest jeszcze
 * TreeMasterSlave, ale ona łączy funkcjonalność tych dwóch poprzednich). TreeMaster uaktualnia strukturę drzewiastą
 * swoich TreeSlave-ów, dzięki czemu użytkownik musi zarządzać tylko jedną strukturą drzewiastą. Interfejsy w Bajce
 * dziedziczą z interfejsów "drzewiastych":
 *
 * - Controller::IController : Util::ITreeMaster (master dla widgetów i modeli).
 * - Controller::IWidget : Util::ITreeMasterSlave (slave dla kontrolerów, master dla modeli).
 * - Model::IModel : Util::ITreeSlave (slave dla kontrolerów i widgetów).
 *
 * Jak widać kontroler jest masterem dla modeli i widgetów. Użytkownik tworzy swoje kontrolery, które zawierają
 * model i widget. następnie użytkownik tworzy strukturę drzewiastą z tych kontrolerów, co z kolei niejawnie
 * tworzy strukturę drzewiastą widgetów i modeli.
 *
 * \image html mvc-tree.png "Struktura drzewiasta MVC"
 *
 * Analogicznie jest z widgetami, ponieważ IWidget dziedziczy z ITreeMasterSlave. Użytkownik tworzy swoje
 * widgety (kazdy z nich ma swój unikalny model), a następnie układa widgety w strukturę drzewiastą. Niejawnie
 * jest wtedy tworzone drzewo modeli.
 *
 * \image html mv-tree.png "Struktura drzewiasta MV"
 *
 * Zatem ogólnie w Bajce struktura MVC może wyglądać takjak poniżej:
 *
 * \image html mvc-mv.png "Struktura MVC w bajce"
 *
 * \subsection API
 * TreeMaster zawiera metody do dodawania i pobierania potomków oraz do pobierania rodzica. Nie ma możliwości
 * ustawienia rodzica explicite. Rodzic ustawia się w momencie dodania dziecka i jest czyszczony w momencie
 * usuwania dziecka z rodzica.
 *
 * - Util::TreeMaster::addChild - głowna metoda dodająca dziecko - wszystkie inne dodające korzystają własnie z niej.
 *   Ta metoda ustawia referencję do rodzica w dziecku.
 * - Util::TreeMaster::addChildren - korzystając w pętli z addChild dodaje liste dzieci do już istniejących dzieci.
 * - Util::TreeMaster::setChildren - korzystając w pętli z addChild ustawia listę dzieci (dotychczasowe zostają
 *   usunięte, a ich referencja do rodzica ustawiona na NULL).
 * - Util::TreeMaster::removeChild - usuwa dziecko z rodzica. Dziecko od tej pory będzie miało wskaźnik do rodzica
 *   ustawioną na NULL.
 * - Util::TreeMaster::clearChildren - usuwa wszystkie dzieci i czyści im referencję do rodzica.
 * - Util::TreeMaster::getChildren - pobiera listę dzieci (kontener STL).
 * - Util::TreeMaster::begin - pobiera iterator do początku listy dzieci.
 * - Util::TreeMaster::end - pobiera iterator do elementu następnego za ostatnim na liście dzieci.
 * - Util::TreeMaster::getParent - zwraca wskaźnik do rodzica (może być NULL).
 *
 * \subsection IoC
 * W kontenerze dostępne są w zasadzie tylko metody setChildren, setModel, getModel i setWidget. getModel jest
 * dostępne, ponieważ model jest często współdzielony przez konreoler i widget. Przykładowy XML :
 *
 * <bean id="A" class="SimpleController">
 * model
 * widget
 * children
 * </bean>
 */

#include "Extractors.h"
#include "IController.h"
#include "IModel.h"
#include "IModelAware.h"
#include "ITreeController.h"
#include "ITreeModel.h"
#include "ITreeWidget.h"
#include "IWidget.h"
#include "Pointer.h"
#include "TreeSlaveIterator.h"
#include "Types.h"

#	endif /* TREE_H_ */
