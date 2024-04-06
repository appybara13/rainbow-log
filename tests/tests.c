#include "rlog.h"

#include <string.h>

int
main(int argc, char** argv)
{
    RLogLevel level = RLOG_LEVEL_INFO;

    for (int a = 0; a < argc; a++) {
        if (!strcmp(argv[a], "--debug") || !strcmp(argv[a], "-d")) {
            level = RLOG_LEVEL_DEBUG;
        } else if (!strcmp(argv[a], "--verbose") || !strcmp(argv[a], "-v")) {
            level = RLOG_LEVEL_VERBOSE;
        } else if (!strcmp(argv[a], "--info") || !strcmp(argv[a], "-i")) {
            level = RLOG_LEVEL_INFO;
        } else if (!strcmp(argv[a], "--warning") || !strcmp(argv[a], "-w")) {
            level = RLOG_LEVEL_WARNING;
        } else if (!strcmp(argv[a], "--error") || !strcmp(argv[a], "-e")) {
            level = RLOG_LEVEL_ERROR;
        } else if (!strcmp(argv[a], "--critical") || !strcmp(argv[a], "-c")) {
            level = RLOG_LEVEL_CRITICAL;
        }
    }

    set_rlog_level(level);

    RLOG_DEBUG("This is a debug log message.");
    RLOG_VERBOSE("This is a verbose log message.");
    RLOG_INFO("This is an info log message.");
    RLOG_WARNING("This is a warning log message.");
    RLOG_ERROR("This is an error log message.");
    RLOG_CRITICAL("This is a critical log message.");

    RLOG_INFO("This is an multiline message:\n /-\\\n | |\n \\_/");
}