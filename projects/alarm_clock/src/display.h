#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <time.h>

#include <dcutil/delay.h>
#include <font/font.h>
#include <SPIStreamAVR.h>
#include <max7219.h>

#include "Buffer.h"
#include "light.h"
#include "state.h"
#include "font/f_3x5.h"
#include "font/f_5x8.h"
#include "font/f_icon.h"

void display_init();

void display_update();

#endif
