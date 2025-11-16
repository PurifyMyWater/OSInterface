#include "OSInterface.h"

const char* OSInterfaceLogLevelToString(const OSInterfaceLogLevel level)
{
    switch (level)
    {
        case OSInterface_LOG_NONE:
            return "NONE";
        case OSInterface_LOG_ERROR:
            return "ERROR";
        case OSInterface_LOG_WARN:
            return "WARN";
        case OSInterface_LOG_INFO:
            return "INFO";
        case OSInterface_LOG_DEBUG:
            return "DEBUG";
        case OSInterface_LOG_VERBOSE:
            return "VERBOSE";
        case OSInterface_LOG_MAX:
            return "MAX";
        default:
            return "UNKNOWN";
    }
}
