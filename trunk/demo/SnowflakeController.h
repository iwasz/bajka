/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 26, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SNOWFLAKECONTROLLER_H_
#define SNOWFLAKECONTROLLER_H_

#include "SimpleController.h"
#include "mapping/IMapping.h"

/**
 *
 */
class SnowflakeController : public Controller::SimpleController {
public:

        __c (void)
        _b ("SimpleController")

        SnowflakeController (Ptr <View::IWidget> widget = Ptr <View::IWidget> (),
                          Ptr <Controller::IMapping> mapping = Ptr <Controller::IMapping> ()) : Controller::SimpleController (widget, mapping) {}

        virtual ~SnowflakeController () {}

        // TODO Do usunięcia, kiedy variant będzie zwracał dobre type_info
        _m (setModel2) void setModel2 (Ptr <Model::Image> m) { model = m; setModel (m); }
        _m (getModel2) Ptr <Model::Image> getModel2 () const { return model; }
        Ptr <Model::Image> model;

        virtual void update (const Events::IObservable <Events::TimerEvent> &observable, const Events::TimerEvent &event)
        {
                getMapping()->run ();
                movMap->run ();
        }

        Ptr <Controller::IMapping> movMap;

        _e (SnowflakeController)
};

#	endif /* SNOWFLAKECONTROLLER_H_ */
