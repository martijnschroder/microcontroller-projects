#ifndef FONT_ICON_H
#define FONT_ICON_H

#include <avr/io.h>
#include <avr/pgmspace.h>

#include <font/font.h>

// Workaround for http://gcc.gnu.org/bugzilla/show_bug.cgi?id=34734
#ifdef PROGMEM
#undef PROGMEM
#define PROGMEM __attribute__((section(".progmem.data")))
#endif

extern font_t font_icon;

#endif
