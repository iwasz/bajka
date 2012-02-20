/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ModelManager.h"
#include "BajkaApp.h"

namespace Util {
using namespace Model;

/****************************************************************************/

void ModelManager::play (/*std::string const &parent, */std::string const &name)
{
        IModel *m = models[name];
        assertThrow (m, "ModelManager::play : !m, name = [" + name + "]");
        app->setModel (m);
}

/****************************************************************************/

void ModelManager::pause (std::string const &name)
{

}

/****************************************************************************/

void ModelManager::stop (std::string const &name)
{

}

/****************************************************************************/

void ModelManager::cut (std::string const &name)
{

}

} /* namespace Util */
