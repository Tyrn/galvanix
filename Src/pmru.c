#include "stm32f1xx_hal.h"
#include "pmru.h"
//#include <string.h>

#define XS (LCD_CELL_HEIGHT)

static uint8_t    rB[XS] = {0x1E, 0x10, 0x10, 0x1E, 0x11, 0x11, 0x1E, 0x00};
static uint8_t    rG[XS] = {0x1F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00};
static uint8_t    rD[XS] = {0x06, 0x0A, 0x0A, 0x0A, 0x0A, 0x1F, 0x11, 0x00};
static uint8_t   rYO[XS] = {0x0A, 0x1F, 0x10, 0x1E, 0x10, 0x10, 0x1F, 0x00};
static uint8_t   rZH[XS] = {0x04, 0x15, 0x15, 0x0E, 0x15, 0x15, 0x04, 0x00};
static uint8_t    rZ[XS] = {0x0E, 0x11, 0x01, 0x06, 0x01, 0x11, 0x0E, 0x00};
static uint8_t    rI[XS] = {0x11, 0x11, 0x13, 0x15, 0x19, 0x11, 0x11, 0x00};
static uint8_t    rJ[XS] = {0x0E, 0x15, 0x11, 0x13, 0x15, 0x19, 0x11, 0x00};
static uint8_t    rL[XS] = {0x07, 0x09, 0x09, 0x09, 0x09, 0x09, 0x11, 0x00};
static uint8_t    rP[XS] = {0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x00};
static uint8_t    rU[XS] = {0x11, 0x11, 0x11, 0x0F, 0x01, 0x01, 0x0E, 0x00};
static uint8_t    rF[XS] = {0x0E, 0x15, 0x15, 0x15, 0x0E, 0x04, 0x04, 0x00};
static uint8_t   rTS[XS] = {0x12, 0x12, 0x12, 0x12, 0x12, 0x1F, 0x01, 0x00};
static uint8_t   rCH[XS] = {0x11, 0x11, 0x11, 0x0F, 0x01, 0x01, 0x01, 0x00};
static uint8_t   rSH[XS] = {0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x1F, 0x00};
static uint8_t rSHCH[XS] = {0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x1F, 0x01};
static uint8_t   rIE[XS] = {0x18, 0x08, 0x08, 0x0E, 0x09, 0x09, 0x0E, 0x00};
static uint8_t    rY[XS] = {0x11, 0x11, 0x19, 0x15, 0x15, 0x15, 0x19, 0x00};
static uint8_t    rQ[XS] = {0x10, 0x10, 0x10, 0x1C, 0x12, 0x12, 0x1C, 0x00};
static uint8_t   rEH[XS] = {0x0E, 0x11, 0x01, 0x0F, 0x01, 0x11, 0x0E, 0x00};
static uint8_t   rYU[XS] = {0x12, 0x15, 0x15, 0x1D, 0x15, 0x15, 0x12, 0x00};
static uint8_t   rYA[XS] = {0x0F, 0x11, 0x11, 0x0F, 0x05, 0x09, 0x11, 0x00};
static uint8_t rSTUB[XS] = {0x00, 0x0A, 0x1F, 0x1F, 0x1F, 0x0E, 0x04, 0x00};

uint32_t pmru_s_char_width(uint8_t *s)
{
  if(*s == 0)    return 0;
  if(*s >= 0xFC) return 6;
  if(*s >= 0xF8) return 5;
  if(*s >= 0xF0) return 4;
  if(*s >= 0xE0) return 3;
  if(*s >= 0xC0) return 2;    // Mind the little-endian.
  return 1;
}

void pmru_s_first(struct pmru_s *i, uint8_t *s)
{
  i->c = s;
  i->width = pmru_s_char_width(s);
}

void pmru_s_next(struct pmru_s *i)
{
  i->c += i->width;
  i->width = pmru_s_char_width(i->c);
}

uint32_t pmru_s_len(uint8_t *str)
{
  uint32_t cnt = 0;
  struct pmru_s uni;
  for(pmru_s_first(&uni, str); uni.width; pmru_s_next(&uni))
  {
    cnt++;
  }
  return cnt;
}

char pmru_s_current_toascii(struct pmru_s *uni)
{
  if(uni->width == 2)
  {
    switch((wchar_t)*uni->c)
    {
      case L'А': return 'A';
      case L'В': return 'B';
      case L'Е': return 'E';
      case L'К': return 'K';
      case L'М': return 'M';
      case L'Н': return 'H';
      case L'О': return 'O';
      case L'Р': return 'P';
      case L'С': return 'C';
      case L'Т': return 'T';
      case L'Х': return 'X';
    }
  }
  if(uni->width == 1) return *uni->c;
  return 0;
}

uint8_t *pmru_get_cell(wchar_t ch)
{
  switch(ch)
  {
    case L'Б': return    rB;
    case L'Г': return    rG;
    case L'Д': return    rD;
    case L'Ё': return   rYO;
    case L'Ж': return   rZH;
    case L'З': return    rZ;
    case L'И': return    rI;
    case L'Й': return    rJ;
    case L'Л': return    rL;
    case L'П': return    rP;
    case L'У': return    rU;
    case L'Ф': return    rF;
    case L'Ц': return   rTS;
    case L'Ч': return   rCH;
    case L'Ш': return   rSH;
    case L'Щ': return rSHCH;
    case L'Ъ': return   rIE;
    case L'Ы': return    rY;
    case L'Ь': return    rQ;
    case L'Э': return   rEH;
    case L'Ю': return   rYU;
    case L'Я': return   rYA;
    default:   return rSTUB;
  }
}

// notch r/o

void pmru_nc_init(struct pmru_nc *newcells)
{
  newcells->i = 0;
}

uint8_t *pmru_nc_next(struct pmru_nc *newcells)
{
  if(newcells->i >= newcells->notch) return NULL;
  return newcells->cells[newcells->i++];
}

uint8_t *pmru_nc_find_cell(struct pmru_nc *newcells, uint8_t *cell)
{
  uint32_t n;

  for(n = 0; n < newcells->notch; n++) if(cell == newcells->cells[n]) return cell;
  return NULL;
}

// notch r/w

void pmru_nc_reset(struct pmru_nc *newcells)
{
  newcells->i = 0;
  newcells->notch = 0;
}

void pmru_nc_add_cell(struct pmru_nc *newcells, uint8_t *cell)
{
  if(pmru_nc_find_cell(newcells, cell)) return;
  if(newcells->notch < LCD_NEWCELL_NUM)
  {
    newcells->cells[newcells->notch++] = cell;
  }
}

void pmru_nc_add_char(struct pmru_nc *newcells, wchar_t ch)
{
  uint8_t *cell;

  cell = pmru_get_cell(ch);
  pmru_nc_add_cell(newcells, cell);
}

void pmru_nc_add_str(struct pmru_nc *newcells, uint8_t *str)
{
  struct pmru_s uni;

  pmru_nc_reset(newcells);
  for(pmru_s_first(&uni, str); uni.width; pmru_s_next(&uni))
  {
    if(uni.width == 2)
    {
      pmru_nc_add_char(newcells, pmru_wchar_head(uni.c));
    }
  }
}

wchar_t pmru_wchar_head(uint8_t* str)
{
  uint16_t uw = *(uint16_t*)str;        // Assume 2-byte Unicode character.
  uint16_t u = (uw >> 8) | (uw << 8);   // Mind the little-endian.

  return (uint32_t)(((u >> 2) & 0x07C0) | (u & 0x003F));
}

uint32_t pmru_lcd_byte(uint8_t byte, uint8_t mask)  // mask: 1: data, 0: command.
{
  uint32_t chunk;
  uint8_t *buf = (uint8_t*)&chunk;
  uint8_t msn, lsn;

  msn    = byte & 0xF0;
  lsn    = (byte << 4) & 0xF0;
  buf[0] = msn | mask | 0x04;
  buf[1] = msn | mask;
  buf[2] = lsn | mask | 0x04;
  buf[3] = lsn | mask;
  return chunk;
}
