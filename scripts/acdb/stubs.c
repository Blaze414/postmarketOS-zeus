#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
unsigned int ar_log_lvl = 0x1;
void ar_log_init(void) {}
void ar_log_deinit(void) {}
void ar_log(uint32_t level, const char *tag, const char *file, const char *fn, int line, const char *fmt, ...) {
	va_list a; va_start(a, fmt); fprintf(stderr, "[acdb %s:%d] ", fn, line); vfprintf(stderr, fmt, a); fprintf(stderr, "\n"); va_end(a);
}
