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
 
#include <stdio.h>

#define EXTERN
#include "strings.h"
#undef EXTERN

int main(int argc, char *argv[]) {
	char buffer[100];
	size_t i;
	size_t len_needed;
	const char *source[] = {
		"\"Hallo \\\" Welt\" oing, nichts weiter",
		"Hallo Welt",
		"'Hallo Welt\\' string\"'",
		"'Ohne Ende",
		"OhneEnde'",
		"\"Mit \\\\ Backslash \\nur einer\""
	};
	bool success;
	
	for (i = 0; i < 6; i++) {
		const char *r = &(source[i][0]);
		const char *read;
		success = read_string_to_buffer_ext(&r, buffer, 10, &len_needed);
		if (success) {
			printf("%s: [%s] -- %s\n", source[i], buffer, r);
		} else {
			printf("%s: Fail -- %s (%zu)\n", source[i], r, len_needed);
		}
		
		r = &(source[i][0]);
		read = read_string_to_static_buffer(&r);
		if (read != NULL)
			printf("[[%s]] Rest [[%s]]\n", read, r);
		else
			printf("Fail: [[%s]]\n", r);
			
		printf("\n\n");
	}
	return 0;
}
