/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SHELL_BAJKA_IIIDATASOURCESERVICE_H_
#define SHELL_BAJKA_IIIDATASOURCESERVICE_H_

struct android_app;

namespace Common {
class DataSource;
}

namespace Util {

/**
 * Fabryka właściwie.
 */
struct IDataSourceService {
public:
        virtual ~IDataSourceService () {}
        virtual Common::DataSource *newDataSource () = 0;
        virtual void deleteDataSource (Common::DataSource *ds) = 0;
};

} // namespace Util

#endif /* DATASOURCESERVICE_H_ */
