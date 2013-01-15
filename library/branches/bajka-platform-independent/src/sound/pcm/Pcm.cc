/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Pcm.h"
#include <cassert>
#include "Platform.h"
#include <common/dataSource/DataSource.h>
#include <cstdio>
#include "util/Exceptions.h"
#include <cstdlib>

namespace Sound {

void load (const char *path, void **data, size_t *bytesLen)
{
        assert (data);
        assert (bytesLen);
        Common::DataSource *ds = newDataSource ();

        try {
                ds->open (path, Common::DataSource::MODE_UNKNOWN);
                *bytesLen = ds->getLength ();
                unsigned char *tmpData = (unsigned char *)malloc (*bytesLen);

                size_t bytesRead = 0;
                size_t offset = 0;

                while ((bytesRead = ds->read (tmpData + offset, BUFSIZ))) {

                        if (bytesRead < 0) {
                                throw Util::InitException ("Sound::load : could not read from resource.");
                        }

                        offset += bytesRead;
                }

                *data = tmpData;
        }
        catch (std::exception const &) {
                deleteDataSource (ds);
                throw;
        }

        deleteDataSource (ds);
}

} /* namespace Sound */
