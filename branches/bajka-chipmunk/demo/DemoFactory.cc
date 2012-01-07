/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 23, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "DemoFactory.h"
#include "SimpleController.h"
#include "Model.h"
#include "PointSet.h"
#include "Image.h"

namespace M = Model;
namespace V = View;
namespace C = Controller;

Ptr <Controller::SimpleController> DemoFactory::createFluid ()
{
        Ptr <C::SimpleController> simple (new C::SimpleController);
//        Ptr <M::PointSet> m (new M::PointSet);
//        Ptr <V::PointSet> v (new V::PointSet);
//        v->init (m);
//        simple->setModel (m);
//        simple->setWidget (v);
        return simple;
}

Ptr <SnowflakeController> DemoFactory::createSniezynka (const Core::String &path)
{
        Ptr <SnowflakeController> simple (new SnowflakeController);
        Ptr <M::Image> mImage (new M::Image ());
        mImage->setPath (path);
        Ptr <V::Image> vImage (new V::Image ());
        vImage->setModel (mImage);
//        vImage->init ();
        simple->setModel (mImage);
        simple->setWidget (vImage);
        return simple;
}
