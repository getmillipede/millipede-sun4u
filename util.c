#include "types.h"
#include "util.h"

u64_t strlen(char *s)
{
  u64_t i;

  for (i = 0; s[i]; i++)
    ;

  return (i);
}
