#ifndef _PMRU_H
#define _PMRU_H

#include <wchar.h>

#define LCD_NEWCELL_NUM 8
#define LCD_CELL_HEIGHT 8

struct pmru_nc
{
  uint8_t  *cells[LCD_NEWCELL_NUM];
  uint32_t notch;
  uint32_t i;
};

struct pmru_s
{
  uint8_t  *c;
  uint32_t width;  // Done when width == 0.
};


wchar_t pmru_wchar_head(uint8_t *str);

// > > Walking the Unicode string.

void pmru_s_first(struct pmru_s *i, uint8_t *s);
void pmru_s_next(struct pmru_s *i);
// Done: i->width == 0
char pmru_s_current_toascii(struct pmru_s *uni);

uint32_t pmru_s_len(uint8_t *str);

// > > Walking the cell array. notch is the index of the
//     free cell available, equal to the amount of the cells stored.

// notch r/o
void pmru_nc_init(struct pmru_nc *newcells);
uint8_t *pmru_nc_next(struct pmru_nc *newcells);
// Done: newcells->i >= newcells->notch

// > > Creating the cell array.

// notch r/w
void pmru_nc_reset(struct pmru_nc *newcells);
void pmru_nc_add_char(struct pmru_nc *newcells, wchar_t ch);
void pmru_nc_add_str(struct pmru_nc *newcells, uint8_t *str);


#endif // _PMRU_H
