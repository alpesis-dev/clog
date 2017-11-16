##############################################################################
Clog
##############################################################################

==============================================================================
How it works
==============================================================================

Copying the ``clog.h`` and ``clog.c`` in the project.

==============================================================================
API
==============================================================================

::

    void test_logging_without_file()
    {
        // clog_set_logfile(NULL);
        clog_set_level (CLOG_DEBUG);
        clog_debug ("Console", "Logging without log file.\n");
        clog_error ("Console", "Logging without log file.\n");
    }
    
    
    void test_logging_with_file()
    {
        clog_set_logfile("_build/log.txt");
        clog_set_level(CLOG_DEBUG);
  
        int i;
        for (i = 0; i < 10; ++i)
        {
            clog_debug ("Main", "Logging to stdout and logfile %d\n", i);
            clog_info ("Main", "Logging to stdout and logfile %d\n", i);
            clog_warn ("Module", "Logging to stdout and logfile %d\n", i);
        }
    }
