#include "stm32f1xx_hal.h"
#include "stub_cmsis_os.h"
#include "morse.h"

static
void morse_delay(uint32_t Duration)
{
  HAL_Delay(Duration);
//  osDelay(Duration);
}

void squeak(uint32_t Duration)
{
/*
  HAL_GPIO_WritePin(MY_PIN_13_GPIO_Port, MY_PIN_13_Pin, GPIO_PIN_RESET);
  morse_delay(Duration);
  HAL_GPIO_WritePin(MY_PIN_13_GPIO_Port, MY_PIN_13_Pin, GPIO_PIN_SET);
*/
}

void dot(void)
{
  squeak(DOT_DURATION);
  morse_delay(DOT_DURATION);
}

void dash(void)
{
  squeak(DASH_DURATION);
  morse_delay(DOT_DURATION);
}

#define SLH() nc()
#define SLT()

void nc(void)
{
  morse_delay(DASH_DURATION);
}

void nw(void)
{
  morse_delay(DASH_DURATION * 2);
}

void a(void)
{
  SLH(); dot(); dash(); SLT();
}

void b(void)
{
  SLH(); dash(); dot(); dot(); dot(); SLT();
}

void c(void)
{
  SLH(); dash(); dot(); dash(); dot(); SLT();
}

void d(void)
{
  SLH(); dash(); dot(); dot(); SLT();
}

void e(void)
{
  SLH(); dot(); SLT();
}

void ea(void)
{
  SLH(); dot(); dot(); dash(); dot(); dot(); SLT();
}

void f(void)
{
  SLH(); dot(); dot(); dash(); dot(); SLT();
}

void g(void)
{
  SLH(); dash(); dash(); dot(); SLT();
}

void h(void)
{
  SLH(); dot(); dot(); dot(); dot(); SLT();
}

void i(void)
{
  SLH(); dot(); dot(); SLT();
}

void j(void)
{
  SLH(); dot(); dash(); dash(); dash(); SLT();
}

void k(void)
{
  SLH(); dash(); dot(); dash(); SLT();
}

void l(void)
{
  SLH(); dot(); dash(); dot(); dot(); SLT();
}

void m(void)
{
  SLH(); dash(); dash(); SLT();
}

void n(void)
{
  SLH(); dash(); dot(); SLT();
}

void o(void)
{
  SLH(); dash(); dash(); dash(); SLT();
}

void p(void)
{
  SLH(); dot(); dash(); dash(); dot(); SLT();
}

void q(void)
{
  SLH(); dash(); dash(); dot(); dash(); SLT();
}


void r(void)
{
  SLH(); dot(); dash(); dot(); SLT();
}

void s(void)
{
  SLH(); dot(); dot(); dot(); SLT();
}

void t(void)
{
  SLH(); dash(); SLT();
}

void u(void)
{
  SLH(); dot(); dot(); dash(); SLT();
}

void v(void)
{
  SLH(); dot(); dot(); dot(); dash(); SLT();
}

void w(void)
{
  SLH(); dot(); dash(); dash(); SLT();
}

void x(void)
{
  SLH(); dash(); dot(); dot(); dash(); SLT();
}

void y(void)
{
  SLH(); dash(); dot(); dash(); dash(); SLT();
}

void z(void)
{
  SLH(); dash(); dash(); dot(); dot(); SLT();
}

void cq(void)
{
  c(); q();
}
void fox_pangram(void)
{
  t(); h(); e(); nw();
  q(); u(); i(); c(); k(); nw();
  b(); r(); o(); w(); n(); nw();
  f(); o(); x(); nw();
  j(); u(); m(); p(); s(); nw();
  o(); v(); e(); r(); nw();
  t(); h(); e(); nw();
  l(); a(); z(); y(); nw();
  d(); o(); g();
}
