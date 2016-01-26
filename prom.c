#include "types.h"
#include "prom.h"
#include "util.h"

static u32_t pr_stdin;
static u32_t pr_stdout;

u64_t (*prom_entry)(void *param);

//
// exit back to prom
//
void prom_exit(void)
{
  prom_args_t a;

  a.name = (u64_t) "exit";
  a.ac = 0;
  a.rc = 0;
  prom_entry(&a);
}

//
// find a device and return its handle
//
u64_t prom_dev_find(char *dev)
{
  prom_args_t a;
  u64_t ret;

  a.name = (u64_t) "finddevice";
  a.ac = 1;
  a.rc = 1;
  a.c0 = (u64_t) dev;
  
  ret = prom_entry(&a);
  if (ret != -1)
    ret = a.c1;

  return ret;
}

//
// get a device property
//
u64_t prom_dev_get_prop(u32_t hdl, char *prop, void *p, u32_t psz)
{
  prom_args_t a;
  u64_t ret;

  a.name = (u64_t) "getprop";
  a.ac = 4;
  a.rc = 1;
  a.c0 = hdl;
  a.c1 = (u64_t) prop;
  a.c2 = (u64_t) p;
  a.c3 = (u64_t) psz;

  ret = prom_entry(&a);
  if (ret != -1)
    ret = a.c4;

  return ret;
}

//
// write to a device
//
u64_t prom_dev_write(u32_t hdl, void *p, u32_t psz)
{
  prom_args_t a;
  u64_t ret;

  a.name = (u64_t) "write";
  a.ac = 3;
  a.rc = 1;
  a.c0 = (u64_t) hdl;
  a.c1 = (u64_t) p;
  a.c2 = (u64_t) psz;

  ret = prom_entry(&a);
  if (ret != -1)
    ret = a.c3;

  return ret;
}

//
// putstr
//
void prom_putstr(char *s)
{
  u64_t len;
  u64_t i;

  len = strlen(s);
  for (; *s; len -= i, s += i)
    if ((i = prom_dev_write(pr_stdout, s, len)) == -1)
      return;
}

//
// initialize the prom code
//
void prom_init(void)
{
  u32_t ch;
  
  ch = prom_dev_find("/chosen");
  if (ch == -1)
    prom_exit();

  if (prom_dev_get_prop(ch, "stdin", &pr_stdin, sizeof(pr_stdin)) !=
      sizeof(pr_stdin))
    prom_exit();
  if (prom_dev_get_prop(ch, "stdout", &pr_stdout, sizeof(pr_stdout)) !=
      sizeof(pr_stdout))
    prom_exit();
}
