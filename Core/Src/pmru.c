/**
 ******************************************************************************
 * @file      pmru.c
 * @brief     Cyrillic characters emulation for LCD HD44780.
 ******************************************************************************
 */
#include "stm32f1xx_hal.h"
#include "pmru.h"

static uint8_t lcd_cells[23][LCD_CELL_HEIGHT] =
{
{ 0x00, 0x0A, 0x1F, 0x1F, 0x1F, 0x0E, 0x04, 0x00 },
{ 0x1E, 0x10, 0x10, 0x1E, 0x11, 0x11, 0x1E, 0x00 },
{ 0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00 },
{ 0x06, 0x0A, 0x0A, 0x0A, 0x0A, 0x1F, 0x11, 0x00 },
{ 0x0A, 0x1F, 0x10, 0x1E, 0x10, 0x10, 0x1F, 0x00 },
{ 0x04, 0x15, 0x15, 0x0E, 0x15, 0x15, 0x04, 0x00 },
{ 0x0E, 0x11, 0x01, 0x06, 0x01, 0x11, 0x0E, 0x00 },
{ 0x11, 0x11, 0x13, 0x15, 0x19, 0x11, 0x11, 0x00 },
{ 0x0E, 0x15, 0x11, 0x13, 0x15, 0x19, 0x11, 0x00 },
{ 0x07, 0x09, 0x09, 0x09, 0x09, 0x09, 0x11, 0x00 },
{ 0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x00 },
{ 0x11, 0x11, 0x11, 0x0F, 0x01, 0x01, 0x0E, 0x00 },
{ 0x0E, 0x15, 0x15, 0x15, 0x0E, 0x04, 0x04, 0x00 },
{ 0x12, 0x12, 0x12, 0x12, 0x12, 0x1F, 0x01, 0x00 },
{ 0x11, 0x11, 0x11, 0x0F, 0x01, 0x01, 0x01, 0x00 },
{ 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x1F, 0x00 },
{ 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x1F, 0x01 },
{ 0x18, 0x08, 0x08, 0x0E, 0x09, 0x09, 0x0E, 0x00 },
{ 0x11, 0x11, 0x19, 0x15, 0x15, 0x15, 0x19, 0x00 },
{ 0x10, 0x10, 0x10, 0x1C, 0x12, 0x12, 0x1C, 0x00 },
{ 0x0E, 0x11, 0x01, 0x0F, 0x01, 0x11, 0x0E, 0x00 },
{ 0x12, 0x15, 0x15, 0x1D, 0x15, 0x15, 0x12, 0x00 },
{ 0x0F, 0x11, 0x11, 0x0F, 0x05, 0x09, 0x11, 0x00 } };

/**
 * @brief Checks the size of a Unicode character.
 *
 * @param[in] s Pointer to the first byte of a Unicode character.
 *
 * @return Size of the Unicode character in bytes.
 */
uint32_t pmru_s_char_width(uint8_t *s)
{
  if (*s == 0)
    return 0;
#if 0                         // Our Unicode is up to word size.
  if (*s >= 0xFC)
    return 6;
  if (*s >= 0xF8)
    return 5;
  if (*s >= 0xF0)
    return 4;
  if (*s >= 0xE0)
    return 3;
#endif
  if (*s >= 0xC0)
    return 2;    // Mind the little-endian.
  return 1;
}

/**
 * @brief Initializes an iterator over a Unicode string.
 *
 * @param[out] i The iterator.
 * @param[in]  s The Unicode string to iterate over.
 */
void pmru_s_first(struct pmru_s *i, uint8_t *s)
{
  i->c = s;
  i->width = pmru_s_char_width(s);
}

/**
 * @brief Next step over a Unicode string.
 *
 * @param[out] i The iterator (initialized before).
 */
void pmru_s_next(struct pmru_s *i)
{
  i->c += i->width;
  i->width = pmru_s_char_width(i->c);
}

/**
 * @brief Checks the length of a Unicode string.
 *
 * @param[in] str Pointer to a Unicode string.
 *
 * @return Length of the Unicode string in characters.
 */
uint32_t pmru_s_len(uint8_t *str)
{
  uint32_t cnt = 0;
  struct pmru_s uni;
  for (pmru_s_first(&uni, str); uni.width; pmru_s_next(&uni))
  {
    cnt++;
  }
  return cnt;
}

char pmru_s_toascii(struct pmru_s *uni)
{
  if (uni->width == 2)
  {
    switch ((unichar_t) *uni->c)
    {
    case L'А':
      return 'A';
    case L'В':
      return 'B';
    case L'Е':
      return 'E';
    case L'К':
      return 'K';
    case L'М':
      return 'M';
    case L'Н':
      return 'H';
    case L'О':
      return 'O';
    case L'Р':
      return 'P';
    case L'С':
      return 'C';
    case L'Т':
      return 'T';
    case L'Х':
      return 'X';
    }
  }
  if (uni->width == 1)
    return *uni->c;
  return 0;
}

uint32_t pmru_get_index(unichar_t ch)
{
  switch (ch)
  {
  case L'Б':
    return 1;
  case L'Г':
    return 2;
  case L'Д':
    return 3;
  case L'Ё':
    return 4;
  case L'Ж':
    return 5;
  case L'З':
    return 6;
  case L'И':
    return 7;
  case L'Й':
    return 8;
  case L'Л':
    return 9;
  case L'П':
    return 10;
  case L'У':
    return 11;
  case L'Ф':
    return 12;
  case L'Ц':
    return 13;
  case L'Ч':
    return 14;
  case L'Ш':
    return 15;
  case L'Щ':
    return 16;
  case L'Ъ':
    return 17;
  case L'Ы':
    return 18;
  case L'Ь':
    return 19;
  case L'Э':
    return 20;
  case L'Ю':
    return 21;
  case L'Я':
    return 22;
  default:
    return 0;
  }
}

uint8_t* pmru_get_cell(unichar_t ch)
{
  return lcd_cells[pmru_get_index(ch)];
}

unichar_t pmru_unichar_head(uint8_t *str)
{
  uint16_t uw = *(uint16_t*) str;        // Assume 2-byte Unicode character.
  uint16_t u = (uw >> 8) | (uw << 8);   // Mind the little-endian.

  return ((u >> 2) & 0x07C0) | (u & 0x003F);
}

uint32_t pmru_lcd_byte(uint8_t byte, uint8_t mask) // mask: 1: data, 0: command.
{
  uint32_t chunk;
  uint8_t *buf = (uint8_t*) &chunk;
  uint8_t msn, lsn;

  msn = byte & 0xF0;
  lsn = (byte << 4) & 0xF0;
  buf[0] = msn | mask | 0x04;
  buf[1] = msn | mask;
  buf[2] = lsn | mask | 0x04;
  buf[3] = lsn | mask;
  return chunk;
}

int pmru_nc_find_cell(struct pmru_nc *newcells, unichar_t cell)
{
  uint32_t n;

  for (n = 0; n < newcells->len; n++)
    if (cell == newcells->cells[n])
      return n;
  return -1;
}

void pmru_nc_reset(struct pmru_nc *newcells)
{
  newcells->len = 0;
}

void pmru_nc_add_char(struct pmru_nc *newcells, unichar_t ch)
{
  if (pmru_nc_find_cell(newcells, ch) >= 0)
    return;
  if (newcells->len < LCD_NEWCELL_NUM)
  {
//    uint8_t *cell = pmru_get_cell(ch);
    // TODO: Write cell to CGRAM[notch]
    newcells->cells[newcells->len++] = ch;
  }
}

void pmru_nc_add_str(struct pmru_nc *newcells, uint8_t *str)
{
  struct pmru_s uni;

  pmru_nc_reset(newcells);
  for (pmru_s_first(&uni, str); uni.width; pmru_s_next(&uni))
  {
    if (uni.width == 2)
    {
      pmru_nc_add_char(newcells, pmru_unichar_head(uni.c));
    }
  }
}

void pmru_lcd_puts(uint8_t *str)
{
  struct pmru_nc nc;
  struct pmru_s uni;

  pmru_nc_add_str(&nc, str);
  for (pmru_s_first(&uni, str); uni.width; pmru_s_next(&uni))
  {
    if (uni.width == 2)
    {
      int i = pmru_nc_find_cell(&nc, pmru_unichar_head(uni.c));
      if (i >= 0)
      {
        // TODO: Transmit CGRAM[i]
      }
    }
    else
    {
      // TODO: Transmit *uni.c
    }
  }
}
