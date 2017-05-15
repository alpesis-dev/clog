#include <string.h>

#include "clog/src/clog.h"


int main ()
{
  char module[] = "test";
  char message[] = "test";
  CLOG_INFO (module, message);
}
