#pragma once

#include "lib/types.h"
#include <stdint.h>

size_t strlen( const char * str );

void * memset( void * ptr, int value, size_t num );

void * memcpy( void * dst, const void * src, size_t len );

size_t strnlen( const char * s, size_t max_len );

char * strncpy( char * dst, const char * src, size_t num );