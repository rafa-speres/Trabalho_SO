#include <stdio.h>

#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#define debug_printf(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define debug_printf(fmt, ...) ((void)0)
#endif

#endif 
