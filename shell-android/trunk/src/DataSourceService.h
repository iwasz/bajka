/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SHELL_BAJKAAAAA_DATASOURCESERVICE_H_
#define SHELL_BAJKAAAAA_DATASOURCESERVICE_H_

struct android_app;

namespace Common {
class DataSource;
}

/**
 * Fabryka właściwie.
 */
class DataSourceService {
public:

        DataSourceService (android_app *app);

        Common::DataSource *newDataSource ();
        void deleteDataSource (Common::DataSource *ds);

private:

        android_app *app;
};

#endif /* DATASOURCESERVICE_H_ */
