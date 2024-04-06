#include "rlog.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/time.h>

#define ANSI_RESET_ALL "\x1b[0m"

#define ANSI_COLOR_BLACK "\x1b[30m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_WHITE "\x1b[37m"

#define ANSI_BACKGROUND_BLACK "\x1b[40m"
#define ANSI_BACKGROUND_RED "\x1b[41m"
#define ANSI_BACKGROUND_GREEN "\x1b[42m"
#define ANSI_BACKGROUND_YELLOW "\x1b[43m"
#define ANSI_BACKGROUND_BLUE "\x1b[44m"
#define ANSI_BACKGROUND_MAGENTA "\x1b[45m"
#define ANSI_BACKGROUND_CYAN "\x1b[46m"
#define ANSI_BACKGROUND_WHITE "\x1b[47m"

#define ANSI_STYLE_BOLD "\x1b[1m"
#define ANSI_STYLE_ITALIC "\x1b[3m"
#define ANSI_STYLE_UNDERLINE "\x1b[4m"

#define TIME_STR_LEN 40
#define FILE_STR_LEN 14
#define LINE_STR_LEN 5
#define LEVEL_STR_LEN 20

#define FILE_STR_PADDING "13"
#define LINE_STR_PADDING "4"
#define LEVEL_STR_PADDING "19"

RLogLevel current_max_log_level = RLOG_LEVEL_INFO;

void
set_rlog_level(RLogLevel level)
{
    current_max_log_level = level;
}

void
sprint_time_str(char* time_str);

void
sprint_file_str(char* file_str, const char* filename);

void
sprint_line_str(char* line_str, int lineno);

void
sprint_level_str(char* level_str, RLogLevel level);

void
rlog_printf(RLogLevel level, RLogArgs args, const char* format, ...)
{
    if (level > current_max_log_level)
        return;

    char time_str[TIME_STR_LEN] = {};
    sprint_time_str(time_str);

    char level_str[LEVEL_STR_LEN] = {};
    sprint_level_str(level_str, level);

    char file_str[FILE_STR_LEN] = {};
    sprint_file_str(file_str, args.filename);

    char line_str[LINE_STR_LEN] = {};
    sprint_line_str(line_str, args.lineno);

    va_list vargs;
    va_start(vargs, format);
    int len = vsnprintf(NULL, 0, format, vargs);
    char* content_str = calloc(len + 1, sizeof(char));
    vsnprintf(content_str, len + 1, format, vargs);

    char* line = strtok(content_str, "\n");
    while (line) {
        printf(
          "%s %s %s %s | %s\n", time_str, file_str, line_str, level_str, line);
        line = strtok(NULL, "\n");
    }

    free(content_str);
}

void
sprint_time_str(char* time_str)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    struct tm* now_tm = gmtime(&now.tv_sec);
    int date_time_str_len = strftime(time_str, TIME_STR_LEN, "%F %T", now_tm);
    time_str[date_time_str_len] = ' ';
    snprintf(time_str + date_time_str_len,
             TIME_STR_LEN - date_time_str_len,
             " %06lu",
             now.tv_usec);
}

void
sprint_file_str(char* file_str, const char* filename)
{
    int filename_len = strlen(filename);

    if (filename_len >= FILE_STR_LEN) {
        snprintf(file_str,
                 FILE_STR_LEN,
                 "...%s",
                 filename + filename_len - FILE_STR_LEN + 4);
    } else {
        snprintf(file_str, FILE_STR_LEN, "%" FILE_STR_PADDING "s", filename);
    }
}

void
sprint_line_str(char* line_str, int lineno)
{
    snprintf(line_str, LINE_STR_LEN, "%0" LINE_STR_PADDING "d", lineno);
}

void
sprint_level_str(char* level_str, RLogLevel level)
{
    const char* str;

    switch (level) {
        case RLOG_LEVEL_CRITICAL:
            str = ANSI_COLOR_MAGENTA "CRITICAL" ANSI_RESET_ALL;
            break;
        case RLOG_LEVEL_ERROR:
            str = ANSI_COLOR_RED "ERROR" ANSI_RESET_ALL;
            break;
        case RLOG_LEVEL_WARNING:
            str = ANSI_COLOR_YELLOW "WARNING" ANSI_RESET_ALL;
            break;
        case RLOG_LEVEL_INFO:
            str = ANSI_COLOR_GREEN "INFO" ANSI_RESET_ALL;
            break;
        case RLOG_LEVEL_VERBOSE:
            str = ANSI_COLOR_WHITE "VERBOSE" ANSI_RESET_ALL;
            break;
        case RLOG_LEVEL_DEBUG:
            str = ANSI_COLOR_BLUE "DEBUG" ANSI_RESET_ALL;
            break;
    }

    snprintf(level_str, LEVEL_STR_LEN, "%" LEVEL_STR_PADDING "s", str);
}
