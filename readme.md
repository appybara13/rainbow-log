# Rainbow Log

Simple, coloured logging with levels.

## Build

Add as a git submodule and link with the `rlog` target.

## Use

Logging prints to stdout, with an interface similar to printf:

```c
#include "rlog.h"

RLOG_LEVEL_INFO("Hello %s", "world!");
```

There are 6 levels:

```c
typedef enum
{
    RLOG_LEVEL_CRITICAL = 0,
    RLOG_LEVEL_ERROR = 1,
    RLOG_LEVEL_WARNING = 2,
    RLOG_LEVEL_INFO = 3,
    RLOG_LEVEL_VERBOSE = 4,
    RLOG_LEVEL_DEBUG = 5,
} RLogLevel;
```

## Filtering

Level filtering is done in two ways:

A run-time global variable which defaults to `LOG_LEVEL_INFO` and is changed like so:

```c
void
set_rlog_level(RLOG_LEVEL_WARNING);
```

A compile-time definition `RLOG_MAX_LEVEL`. Levels above this value *should* be optimized away by the compiler. If not defined, this defaults to `LOG_LEVEL_VERBOSE` for release builds and `LOG_LEVEL_DEBUG` for debug builds.

```c
#ifndef RLOG_MAX_LEVEL
#ifdef DEBUG
#define RLOG_MAX_LEVEL LOG_LEVEL_DEBUG
#else
#define RLOG_MAX_LEVEL LOG_LEVEL_VERBOSE
#endif
#endif
```

This could be used to enable different log levels output per-file.

