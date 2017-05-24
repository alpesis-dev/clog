/*
 * Functions:
 *
 *   clog_debug()
 *   clog_info()
 *   clog_warn()
 *   clog_error()
 *   clog_critical()
 *        +
 *        + ---- clog_output()
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#include <sys/time.h>

#include "clog.h"


#define MAX_FILENAME_LEN 255


static clog_level_e log_level = CLOG_WARN;
static char filename[MAX_FILENAME_LEN+1];
static FILE *logfile = NULL;

static char *level_str[CLOG_MAX] = {
    "debug",
    "info",
    "warn",
    "error",
    "critical"
};
static const size_t OUTPUT_PREFIX_LEN = 5;
static const size_t OUTPUT_TIME_LEN = 30;
static const char SEPARATOR[] = " - ";


void clog_set_level(clog_level_e lvl)
{
    if(lvl < CLOG_DEBUG || lvl >= CLOG_MAX)
        return;
    log_level = lvl;
}

clog_level_e clog_get_level()
{
    return log_level;
}

void clog_set_logfile(const char *fn)
{
    if(fn && fn[0] != 0)
    {
        strncpy(filename, fn, sizeof(filename));
        if(filename[sizeof(filename)-1] != 0)
            filename[sizeof(filename)-1] = 0;

        if(logfile)
            fclose(logfile);
        logfile = fopen(filename, "w");
    }
    else
    {
        filename[0] = 0;
        if(logfile)
        {
            fclose(logfile);
            logfile = NULL;
        }
    }
}

inline static void clog_output(clog_level_e lvl, const char *mod, const char *fmt, va_list args)
{
    if(lvl < log_level || lvl >= CLOG_MAX)
        return;

    va_list args_copy;
    va_copy(args_copy, args);
    size_t buf_size = OUTPUT_PREFIX_LEN+OUTPUT_TIME_LEN+2*sizeof(SEPARATOR)+strlen(mod);
    buf_size += vsnprintf(NULL, 0, fmt, args_copy)+1;
    char buf[buf_size];

    size_t pos = snprintf(buf, buf_size, "(%s) - ", level_str[lvl]);

    struct timeval tv;
    gettimeofday(&tv, NULL);
    struct tm tms;
    char time_str[OUTPUT_TIME_LEN+1];
    if(localtime_r(&tv.tv_sec, &tms))
    {
        size_t tpos = strftime(time_str, sizeof(time_str), "%b %d %Y %T.", &tms);
        snprintf(time_str+tpos, sizeof(time_str)-tpos, "%03ld", tv.tv_usec/1000);
    }

    snprintf(buf+pos, buf_size-pos, "%s%s%s%s%s", time_str, SEPARATOR, mod, SEPARATOR, fmt);

    if(logfile)
    {
        va_copy(args_copy, args);
        vprintf(buf, args);
        vfprintf(logfile, buf, args_copy);
    }
    else
        vprintf(buf, args);
}

void cloginf(clog_level_e lvl, const char *mod, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    clog_output(lvl, mod, fmt, args);
    va_end(args);
}

void clog_debug(const char *mod, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    clog_output(CLOG_DEBUG, mod, fmt, args);
    va_end(args);
}

void clog_info(const char *mod, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    clog_output(CLOG_INFO, mod, fmt, args);
    va_end(args);
}

void clog_warn(const char *mod, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    clog_output(CLOG_WARN, mod, fmt, args);
    va_end(args);
}

void clog_error(const char *mod, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    clog_output(CLOG_ERROR, mod, fmt, args);
    va_end(args);
}

void clog_critical(const char *mod, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    clog_output(CLOG_CRITICAL, mod, fmt, args);
    va_end(args);
}


