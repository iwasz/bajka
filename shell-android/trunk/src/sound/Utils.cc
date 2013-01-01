/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Utils.h"
#include <sound/SoundException.h>
#include <boost/lexical_cast.hpp>

#ifndef NDEBUG
std::string slResultToString (SLresult result)
{
        switch (result) {
        case SL_RESULT_SUCCESS:
                return "SL_RESULT_SUCCESS";
        case SL_RESULT_PRECONDITIONS_VIOLATED:
                return "SL_RESULT_PRECONDITIONS_VIOLATED";
        case SL_RESULT_PARAMETER_INVALID:
                return "SL_RESULT_PARAMETER_INVALID";
        case SL_RESULT_MEMORY_FAILURE:
                return "SL_RESULT_MEMORY_FAILURE";
        case SL_RESULT_RESOURCE_ERROR:
                return "SL_RESULT_RESOURCE_ERROR";
        case SL_RESULT_RESOURCE_LOST:
                return "SL_RESULT_RESOURCE_LOST";
        case SL_RESULT_IO_ERROR:
                return "SL_RESULT_IO_ERROR";
        case SL_RESULT_BUFFER_INSUFFICIENT:
                return "SL_RESULT_BUFFER_INSUFFICIENT";
        case SL_RESULT_CONTENT_CORRUPTED:
                return "SL_RESULT_CONTENT_CORRUPTED";
        case SL_RESULT_CONTENT_UNSUPPORTED:
                return "SL_RESULT_CONTENT_UNSUPPORTED";
        case SL_RESULT_CONTENT_NOT_FOUND:
                return "SL_RESULT_CONTENT_NOT_FOUND";
        case SL_RESULT_PERMISSION_DENIED:
                return "SL_RESULT_PERMISSION_DENIED";
        case SL_RESULT_FEATURE_UNSUPPORTED:
                return "SL_RESULT_FEATURE_UNSUPPORTED";
        case SL_RESULT_INTERNAL_ERROR:
                return "SL_RESULT_INTERNAL_ERROR";
        case SL_RESULT_UNKNOWN_ERROR:
                return "SL_RESULT_UNKNOWN_ERROR";
        case SL_RESULT_OPERATION_ABORTED:
                return "SL_RESULT_OPERATION_ABORTED";
        case SL_RESULT_CONTROL_LOST:
                return "SL_RESULT_CONTROL_LOST";
        }

        return "UNKNOWN result!";
}
#else
std::string slResultToString (SLresult result)
{
        return "";
}
#endif

/****************************************************************************/

void soundThrowImpl (const char *file, long line, const char *function, SLresult result, std::string const &msg)
{
        if (result != SL_RESULT_SUCCESS) {
                throw Sound::SoundException (std::string ("SoundException@ ") +
                                             std::string (file) + ":" +
                                             boost::lexical_cast <std::string> (line) + " " +
                                             std::string (function) + " " +
                                             msg + " " + slResultToString (result));
        }
}
