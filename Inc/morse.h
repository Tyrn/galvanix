/*
 * morse.h
 *
 *  Created on: Mar 1, 2018
 *      Author: alexey
 */

#ifndef MORSE_H_
#define MORSE_H_

#define DOT_DURATION 300
#define DASH_DURATION (DOT_DURATION * 3)

void squeak(uint32_t Duration);
void dot(void);
void dash(void);

void nc(void);
void nw(void);

void a(void);
void b(void);
void c(void);
void d(void);
void e(void);
void ea(void);
void f(void);
void g(void);
void h(void);

void i(void);
void j(void);
void k(void);
void l(void);
void m(void);
void n(void);
void o(void);
void p(void);
void q(void);

void r(void);
void s(void);
void t(void);
void u(void);
void v(void);
void w(void);
void x(void);
void y(void);
void z(void);

void cq(void);
void fox_pangram(void);

#endif /* MORSE_H_ */
