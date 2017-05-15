#ifndef CLOG_H_
#define CLOG_H_


/* 
 * Logging Flags
 * - none: 0
 * - info: 1
 * - warn: 2
 * - debug: 3
 * - error: 4
 * - fatal: 5 
 */


/*
 *
 */
typedef struct {
  int year;
  int month;
  int day;
  int hour;
  int min;
  int sec;
  int usec;
} DATETIME;


/*
 * 
 */
const char* version ();


/*
 */
void CLOG_INFO (char module[], char message[]);


#endif // CLOG_H_

