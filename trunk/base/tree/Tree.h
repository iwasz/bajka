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
 * \ingroup Base
 * Kod implementujący strukturę drzewiastą kontrolerów i widgetów w Bajce.
 */

/**
 * \mainpage
 * \section Zawieranie
 * \subsection Ogólnie
 * Zawieranie, czyli implementacja wzoraca projektowego "composite" jest realizowane w Bajce na dwóch
 * płaszczyznach.
 *
 * -# Kontrolery (instancje klasy Controller::SimpleController) mogą zawierać inne
 * kontyrolery (obiekty typu Controller::IController). Czyli <b>kontrolery mogą tworzyć strukturę drzewistą</b>. Każdy
 * kontroler może zawierać jeden model (obiekt typu Model::IModel), oraz jeden widget (obiekt klasy View::IWidget).
 * -# Widgety (czyli to V w MVC) też można zagnieżdżać. Instancje klasy
 * AbstractWidget mogą zawierać dowolnie dużo obiektów klasy IWidget i '''wówczas także tworzą strukturę
 * drzewisatą'''.
 *
 * Dziecko może mieć tylko jednego rodzica, co oznacza, że nie można dodać jednego kontrolera do dwóch
 * innych (da się, ale pierwszy się zamaże).
 *
 * Głównym sposobem zagnieżdżania (tym który był wcześniej) jest zagnieżdżanie kontrolerów. Kontrolery
 * udostępiają specjalne iteratory pozwalające iterować nie tylko po potomkach-kontrolerach, ale także
 * dwa dodatkowe iteratory, które iteraując po potomkach zwracają widget lub model takiego potomka. Dzięki
 * temu każdy model w takiej strukturze może iteraować po odpowadających mu modelach-potokach, a widget
 * po widgetach-potomkach. Zagnieżdżanie kontrolerów niesie ze sobą szereg konsekwencji jak :
 * - Przekazywanie eventów w górę drzewa (od korzenia do liści).
 * - Układy wspólrzędnych są relatywne dla każdego poziomu zagnieżdżenia.
 * - Kształt widgetów (enlose, boundingBox etc).
 *
 * Drugi sposób zagnieżdżania w bajce, to zagnieżdżanie widgetów. Dzięki temu można tworzyć bardziej
 * skomplikowane kontrolki/spritey, typu tabelki etc. Widgety znalogicznie o kontrolerów udostępniają
 * specjalny iterator pozwalający iterując po potomkach widgetu zwracać odpowiednie modele zawierane
 * przez te widgety.
 *
 * \subsection Uwaga
 * Model (konkretnie klasa Model::ITreeModel) zawiera prywatny wskaźnik do obiektu o nazwie <b>owner</b>.
 * Ownerem może być albo kontroler, albo widget.  W pierwszym przypadku mamy doczynienia z <i>pierwszym sposobem
 * zawierania</i>, a w drugim z tym <i>drugim</i>. Owner ustawia się, kiedy dodajemy ten model za pomocą
 * Controller::IController::setModel, albo View::IWidget::setModel, ale <b>tylko gdy model nie ma już ustawionego
 * ownera</b>. Czyli pierwszy ustawiony jest ownerem:
 *
 * <pre>
 * // A.
 * ctr.setModel (mdl);
 * wdg.setModel (mdl); // mdl.owner == ctr
 *
 * // B.
 * wdg.setModel (mdl);
 * ctr.setModel (mdl); // mdl.owner == wdg
 * </pre>
 *
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
 * Controller::TreeController zawiera metody do dodawania i pobierania potomków oraz do pobierania rodzica. Nie ma możliwości
 * ustawienia rodzica explicite. Rodzic ustawia się w momencie dodania dziecka i jest czyszczony w momencie
 * usuwania dziecka z rodzica. Analogicznie View::TreeWidget.
 *
 * - Controller::TreeController::addChild - głowna metoda dodająca dziecko - wszystkie inne dodające korzystają własnie z niej.
 *   Ta metoda ustawia referencję do rodzica w dziecku.
 * - Controller::TreeController::addChildren - korzystając w pętli z addChild dodaje liste dzieci do już istniejących dzieci.
 * - Controller::TreeController::setChildren - korzystając w pętli z addChild ustawia listę dzieci (dotychczasowe zostają
 *   usunięte, a ich referencja do rodzica ustawiona na NULL).
 * - Controller::TreeController::removeChild - usuwa dziecko z rodzica. Dziecko od tej pory będzie miało wskaźnik do rodzica
 *   ustawioną na NULL.
 * - Controller::TreeController::clearChildren - usuwa wszystkie dzieci i czyści im referencję do rodzica.
 * - Controller::TreeController::begin - pobiera iterator do początku listy dzieci.
 * - Controller::TreeController::end - pobiera iterator do elementu następnego za ostatnim na liście dzieci.
 * - Controller::TreeController::getParent - zwraca wskaźnik do rodzica (może być NULL).
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
 *
 * \section MVC_Interakcje
 *
 * \subsection Rysowanie
 * Co i jak się uruchamia kiedy rysujemy kontroler/widget (co się dzieje z dziećmi).
 *
 * \subsection Inicjowanie
 * Co i w jakiej kolejności inicjowac, a czego nie. W szczególności zakręcone jest to, że jak się model ustawi
 * widgetowi jako pierwszemu, a potem kontrolerowi, to tem model ma ownera jako ten widget (i getParent zwraca
 * NULL, nie ma też dzieci - mimo, że kontroler ma dzieci i rodzica). I na odwrot. Nie wiem - może to zmienić?
 * W końcu zawieranie przez kontrolery jest wazniejsze!
 *
 * \section Eventy
 * Section
 *
 * \section Układy_współrzędnych
 * Section
 *
 * \section Geometria
 * Section
 *
 * \section Transformacje
 * Section
 *
 * \section Rysowanie
 * Section
 *
 * \section Layout
 * Tree, VBox, HBox, Expander
 */

#include "Extractors.h"
#include "IModelAware.h"
#include "ITreeController.h"
#include "ITreeModel.h"
#include "ITreeWidget.h"
#include "Pointer.h"
#include "TreeSlaveIterator.h"
#include "Types.h"

#	endif /* TREE_H_ */
