#include "types.h"
#include "prom.h"

char mili_head[] = { 200, 'o', ' ', 'o', 188, '\n', 0};
char mili_body[] = { 200, 205, '(', 219, 219, 219, ')', 205, 188, '\n', 0};

void draw_spaces(u64_t sp)
{
  for (; sp; sp--)
    prom_putstr(" ");
}

void main(void)
{
  u64_t val;
  u64_t sp;
  u64_t i;

  prom_init();
  prom_putstr("\f     ");
  prom_putstr(mili_head);
  for (val = -1, sp = 3, i = 0; i < 25; i++, sp += val)
  {
    if (sp == -1)
    {
      val = 1;
      sp = 1;
    }
    if (sp == 5)
    {
      val = -1;
      sp = 4;
    }
    draw_spaces(sp);
    prom_putstr(mili_body);
  }
  prom_exit();
  while(1);
}
