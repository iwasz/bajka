/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "DataSourceService.h"
#include <common/dataSource/DataSource.h>
#include <android_native_app_glue.h>

DataSourceService::DataSourceService (android_app *a) : app (a) {}

/****************************************************************************/

Common::DataSource *DataSourceService::newDataSource ()
{
        return new Common::DataSource (app->activity->assetManager);
}

/****************************************************************************/

void DataSourceService::deleteDataSource (Common::DataSource *ds)
{
        delete ds;
}
