#ifndef STRINGS_H
#define STRINGS_H

#include <stddef.h>

typedef short int16;
typedef int16 bool;

#ifdef EXTERN
	extern const bool true;
	extern const bool false;
	extern const char EOS;
	extern const char LF;
	extern const char CR;
	extern const char ESCAPE;
#else
	const bool true = 1;
	const bool false = 0;
	const char EOS = 0;
	const char LF = 0x0a;
	const char CR = 0x0c;
	const char ESCAPE = '\\';
#endif

bool read_string_to_buffer(const char **source, char *buffer, size_t buffer_size);
bool read_string_to_buffer_ext(const char **source, char *buffer, size_t buffer_size, size_t *len_needed);
const char* read_string_to_static_buffer(const char **source);

#endif
