/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TILIAEMODELMANAGER_H_
#define TILIAEMODELMANAGER_H_

#include <Container.h>
#include "../util/ModelManager.h"
#include "../util/ReflectionMacros.h"

namespace Util {

/**
 * Ładuje modele z kontenera IoC. Ta klasa ma referencję do głownego konteera i do jednego child-kontenera
 * i z nich próibuje załadować model o podanej nazwie. Jeśli nie znajdziem, to szuka w mapowaniu mapping
 * w jakim pliku jest szukany model i ładuje ten plik jednocześnie wyrzucajac z pamięci poprzedni.
 */
class TiliaeModelManager : public Util::ModelManager {
public:
        C__ (void)
        b_ ("ModelManager")

        virtual ~TiliaeModelManager () {}

        void play (std::string const &name);
        void cut (std::string const &name);

        void setMainContainer (Ptr <Container::BeanFactoryContainer> mc) { mainContainer = mc; }

        Core::StringMap const &getMapping () const { return mapping; }

        /// Nazwa modelu -> plik.
        m_ (setMapping) void setMapping (Core::StringMap const &m) { mapping = m; }

private:

        void load (std::string const &name, bool cut = false);

private:

        // TODO żeby IoC umiał sam to ustawiać.
        Ptr <Container::BeanFactoryContainer> mainContainer;
        Ptr <Container::BeanFactoryContainer> childContainer;
        Core::StringMap mapping;
        std::string currentFile;

        E_ (TiliaeModelManager)
};

} /* namespace Util */

#	endif /* TILIAEMODELMANAGER_H_ */
