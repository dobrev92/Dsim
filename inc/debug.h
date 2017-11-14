#ifndef __DEBUG_H__
#define __DEBIG_H__

#define __DEBUG__

#ifdef __DEBUG__

int dbg_text(const char* format, ...);

#define dbg_info(...) dbg_text("%s, %d: %s: ", __FILE__, __LINE__, __PRETTY_FUNCTION__); \
			 dbg_text(__VA_ARGS__);

#else
#define dbg_info(format)
#endif // __DEBUG__
#endif // __DEBUG_H__

