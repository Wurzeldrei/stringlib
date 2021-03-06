/*
 * Copyright (c) 2015 Christoph Fuest
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
