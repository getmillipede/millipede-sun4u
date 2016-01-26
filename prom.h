#ifndef PROM_H
#define PROM_H

typedef struct
{
  u64_t name;
  u64_t ac;
  u64_t rc;
  u64_t c0;
  u64_t c1;
  u64_t c2;
  u64_t c3;
  u64_t c4;
} prom_args_t;

extern u64_t (*prom_entry)(void *param);
void prom_exit(void);
u64_t prom_dev_find(char *dev);
void prom_putstr(char *s);
void prom_init(void);

#endif
