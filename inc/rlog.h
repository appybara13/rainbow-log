#pragma once

#define RLOG_ARGS                                                              \
    (RLogArgs)                                                                 \
    {                                                                          \
        .filename = __FILE_NAME__, .lineno = __LINE__,                         \
    }

#ifndef RLOG_MAX_LEVEL
#ifdef DEBUG
#define RLOG_MAX_LEVEL RLOG_LEVEL_DEBUG
#else
#define RLOG_MAX_LEVEL RLOG_LEVEL_VERBOSE
#endif
#endif

#define RLOG(LEVEL, ...)                                                       \
    if (LEVEL <= RLOG_MAX_LEVEL)                                               \
    rlog_printf(LEVEL, RLOG_ARGS, __VA_ARGS__)

#define RLOG_CRITICAL(...) RLOG(RLOG_LEVEL_CRITICAL, __VA_ARGS__)
#define RLOG_ERROR(...) RLOG(RLOG_LEVEL_ERROR, __VA_ARGS__)
#define RLOG_WARNING(...) RLOG(RLOG_LEVEL_WARNING, __VA_ARGS__)
#define RLOG_INFO(...) RLOG(RLOG_LEVEL_INFO, __VA_ARGS__)
#define RLOG_VERBOSE(...) RLOG(RLOG_LEVEL_VERBOSE, __VA_ARGS__)
#define RLOG_DEBUG(...) RLOG(RLOG_LEVEL_DEBUG, __VA_ARGS__)

typedef enum
{
    RLOG_LEVEL_CRITICAL = 0,
    RLOG_LEVEL_ERROR = 1,
    RLOG_LEVEL_WARNING = 2,
    RLOG_LEVEL_INFO = 3,
    RLOG_LEVEL_VERBOSE = 4,
    RLOG_LEVEL_DEBUG = 5,
} RLogLevel;

typedef struct
{
    const char* filename;
    int lineno;
} RLogArgs;

void
set_rlog_level(RLogLevel level);

void
rlog_printf(RLogLevel level, RLogArgs args, const char* format, ...);