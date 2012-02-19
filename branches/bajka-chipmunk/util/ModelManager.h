/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SCENEMANAGER_H_
#define BAJKA_SCENEMANAGER_H_

#include <string>

namespace Util {

/**
 * Przyporządkowuje nazwy modelom i ułatwia ich tworzenie i wyświetlanie.
 */
class ModelManager {
public:
        virtual ~ModelManager () {}

        void play (std::string const &parent, std::string const &name);
        void pause (std::string const &name);
        void stop (std::string const &name);
        void cut (std::string const &name);

private:


};

} /* namespace Util */

#	endif /* SCENEMANAGER_H_ */
