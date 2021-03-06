#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <time.h>
#include <sys/time.h>

#include "log.h"

static char *buildFormat(char *severity, char *fmt) {
    time_t t;
    struct tm *tm;
    struct timeval tv;
    char *new_fmt;

    new_fmt = calloc(1, strlen(fmt) + 2048);
    t = time(NULL);
    tm = localtime(&t);
    gettimeofday(&tv, NULL);

    sprintf(new_fmt,
        "[%02d:%02d:%02d:%d %04d-%02d-%02d][%s] %s\n",
        tm->tm_hour,
        tm->tm_min,
        tm->tm_sec,
        tv.tv_usec / 1000,
        tm->tm_year + 1900,
        tm->tm_mon + 1,
        tm->tm_mday,
        severity,
        fmt
    );

    return new_fmt;
}

static void doLog(char *severity, char *fmt, ...) {
    time_t t;
    struct tm *tm;
    struct timeval tv;
    va_list ap;
    char *new_fmt = calloc(1, strlen(fmt) + 2048);
    
    t = time(NULL);
    tm = localtime(&t);
    gettimeofday(&tv, NULL);

    sprintf(new_fmt,
        "[%02d:%02d:%02d:%d %04d:%02d:%02d][%s] %s\n",
        tm->tm_hour,
        tm->tm_min,
        tm->tm_sec,
        tv.tv_usec / 1000,
        tm->tm_year + 1900,
        tm->tm_mon + 1,
        tm->tm_mday,
        severity,
        fmt
    );

    va_start(ap, fmt);
    vprintf(new_fmt, ap);
    va_end(ap);

    free(new_fmt);
}

void Log_Info(char *fmt, ...) {
    va_list ap;
    char *new_format;

    new_format = buildFormat("INFO", fmt);
    va_start(ap, fmt);
    vprintf(new_format, ap);
    va_end(ap);

    free(new_format);
}

void Log_Error(char *fmt, ...) {
    va_list ap;
    char *new_format;

    new_format = buildFormat("ERROR", fmt);
    va_start(ap, fmt);
    vprintf(new_format, ap);
    va_end(ap);

    free(new_format);
}
