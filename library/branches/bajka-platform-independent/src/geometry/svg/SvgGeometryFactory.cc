/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "SvgGeometryFactory.h"
#include <container/beanFactory/BeanFactoryContainer.h>
#include "Svg.h"

namespace Geometry {

SvgGeometryFactory::~SvgGeometryFactory ()
{
//        Svg::deleteGeometries (&loadedObjects);
}

/****************************************************************************/

void SvgGeometryFactory::setFile (std::string const &s)
{
        loadedObjects = Svg::parseFile (s);

        for (Core::VariantMap::const_iterator i = loadedObjects.begin (); i != loadedObjects.end (); ++i) {
                cont->addSingleton (i->first.c_str (), i->second);
        }
}

} /* namespace Geometry */
