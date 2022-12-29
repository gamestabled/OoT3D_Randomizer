#include "lib/types.h"
#include <stdint.h>

size_t strlen(const char* str) {
    const char* s;
    for (s = str; *s; ++s)
        ;
    return (s - str);
}

void* memset(void* ptr, int value, size_t num) {
    char* s = ptr;
    while (num--)
        *s++ = value;
    return ptr;
}

void* memcpy(void* dst, const void* src, size_t len) {
    size_t i;
    if ((uintptr_t)dst % sizeof(long) == 0 && (uintptr_t)src % sizeof(long) == 0 && len % sizeof(long) == 0) {

        long* d       = dst;
        const long* s = src;

        for (i = 0; i < len / sizeof(long); i++) {
            d[i] = s[i];
        }
    } else {
        char* d       = dst;
        const char* s = src;

        for (i = 0; i < len; i++) {
            d[i] = s[i];
        }
    }
    return dst;
}

size_t strnlen(const char* s, size_t max_len) {
    size_t i = 0;
    for (; (i < max_len) && s[i]; ++i)
        ;
    return i;
}

char* strncpy(char* dst, const char* src, size_t num) {
    char* b  = dst;
    size_t i = 0;
    while (i++ != num && (*dst++ = *src++))
        ;
    return b;
}