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
