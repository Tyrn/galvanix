#ifndef _PMRU_H
#define _PMRU_H

// Assume Unicode to be an up to word size UTF-8 subset.
#define unichar_t uint16_t

#define LCD_NEWCELL_NUM 8
#define LCD_CELL_HEIGHT 8

struct pmru_nc
{
  unichar_t  cells[LCD_NEWCELL_NUM];
  uint32_t   notch;
  uint32_t   i;
};

struct pmru_s
{
  uint8_t    *c;
  uint32_t   width;
};


unichar_t pmru_unichar_head(uint8_t *str);

// > > Walking the Unicode string.

void pmru_s_first(struct pmru_s *i, uint8_t *s);
void pmru_s_next(struct pmru_s *i);
// Done: i->width == 0
char pmru_s_toascii(struct pmru_s *uni);

uint32_t pmru_s_len(uint8_t *str);

// > > Walking the cell array. notch is the index of the
//     free cell available, equal to the amount of the cells stored.
//
//     Cell array is a collection of different Russian characters
//     (up to 8) to be uploaded to the LCD CGRAM.

// notch r/o
void pmru_nc_init(struct pmru_nc *newcells);
int pmru_nc_next(struct pmru_nc *newcells);
// Done: newcells->i >= newcells->notch

// > > Creating the cell array.

// notch r/w
void pmru_nc_reset(struct pmru_nc *newcells);
void pmru_nc_add_char(struct pmru_nc *newcells, unichar_t ch);
void pmru_nc_add_str(struct pmru_nc *newcells, uint8_t *str);

// > > Addressing the LCD.

uint32_t pmru_lcd_byte(uint8_t byte, uint8_t mask);  // mask: 1: data, 0: command.


#endif // _PMRU_H
