/**
 ******************************************************************************
 * @file      pmru.h
 * @brief     Header for pmru.c file.
 ******************************************************************************
 */
#ifndef _PMRU_H
#define _PMRU_H

/* Assume Unicode to be an up to word size UTF-8 subset. */
#define unichar_t uint16_t

#define LCD_NEWCELL_NUM 8

/* Must be 8 or less. */
#define LCD_CELL_WIDTH 5

#define LCD_CELL_HEIGHT 8

struct pmru_nc
{
  unichar_t cells[LCD_NEWCELL_NUM]; /* Unicode characters to be represented in LCD CGRAM. */
  uint32_t len; /* The number of the characters collected. */
};

struct pmru_s
{
  uint8_t *c; /* Pointer to the current Unicode character (the tail of the string). */
  uint32_t width; /* Width of the current Unicode character (0 with the empty tail). */
};

unichar_t pmru_unichar_head(uint8_t *str);

/**
 * @brief   Iterator over a Unicode string represented as uint8_t*.
 */

void pmru_s_first(struct pmru_s *i, uint8_t *s);
void pmru_s_next(struct pmru_s *i);
/**
 * @brief   Done condition: i->width == 0.
 */

char pmru_s_toascii(struct pmru_s *uni);
uint32_t pmru_s_len(uint8_t *str);

/**
 * @brief   Collection (a set) of different Unicode (Russian)
 *          characters (size limited by LCD HD44780 device specs)
 *          to be uploaded to the LCD CGRAM.
 */

void pmru_nc_reset(struct pmru_nc *newcells);
void pmru_nc_add_char(struct pmru_nc *newcells, unichar_t ch);
void pmru_nc_add_str(struct pmru_nc *newcells, uint8_t *str);

uint8_t* pmru_get_cell(unichar_t ch);
uint32_t pmru_lcd_byte(uint8_t byte, uint8_t mask); // mask: 1: data, 0: command.

#endif // _PMRU_H
