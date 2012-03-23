/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Instructions1Controller.h"
#include "../model/IModel.h"

namespace Demo {

bool Instructions1Controller::onManagerLoad (Event::ManagerEvent *e, Model::IModel *m, View::IView *v)
{
        std::cerr << "Instructions1Controller::onManagerLoad" << std::endl;
        return true;
}

/****************************************************************************/

bool Instructions1Controller::onManagerUnload (Event::ManagerEvent *e, Model::IModel *m, View::IView *v)
{
        std::cerr << "Instructions1Controller::onManagerUnload" << std::endl;
        return true;
}

} /* namespace Demo */
