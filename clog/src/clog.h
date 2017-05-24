#ifndef _CLOG_H_
#define _CLOG_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    CLOG_DEBUG,
    CLOG_INFO,
    CLOG_WARN,
    CLOG_ERROR,
    CLOG_CRITICAL,
    CLOG_MAX
} clog_level_e;


void clog_set_level(clog_level_e lvl);
clog_level_e clog_get_level();

void clog_set_logfile(const char *fn);

void cloginf(clog_level_e lvl, const char *mod, const char *fmt, ...);
void clog_debug(const char *mod, const char *fmt, ...);
void clog_info(const char *mod, const char *fmt, ...);
void clog_warn(const char *mod, const char *fmt, ...);
void clog_error(const char *mod, const char *fmt, ...);
void clog_critical(const char *mod, const char *fmt, ...);


#ifdef __cplusplus
}
#endif

#endif

