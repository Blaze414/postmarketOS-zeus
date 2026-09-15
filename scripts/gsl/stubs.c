/* ar_osal_log.c needs Android's cutils (log/log.h). These three symbols are
 * everything the rest of the tree actually uses, so provide them instead.
 *
 * AR_LOG_LVL selects verbosity as the bitmask from ar_osal_log.h:
 *   1 critical, 2 error, 4 debug, 8 info, 0x10 verbose. Default: critical|error.
 */
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

unsigned int ar_log_lvl = 0x3;

void ar_log_init(void)
{
	const char *e = getenv("AR_LOG_LVL");

	if (e)
		ar_log_lvl = (unsigned int)strtoul(e, NULL, 0);
}

void ar_log_deinit(void) {}

void ar_log(uint32_t level, const char *tag, const char *file, const char *fn,
	    int line, const char *fmt, ...)
{
	va_list a;

	va_start(a, fmt);
	fprintf(stderr, "[%s %s:%d] ", tag ? tag : "ar", fn, line);
	vfprintf(stderr, fmt, a);
	fprintf(stderr, "\n");
	va_end(a);
}
