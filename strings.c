#include <stdlib.h>

#undef EXTERN
#include "strings.h"

static bool is_string_end(char delimiter, char sample) {
	if (sample == EOS) return true;
	if (sample == delimiter) return true;
	if (sample == CR) return true;
	if (sample == LF) return true;
	return false;
}

bool read_string_to_buffer_ext(const char **source, char *buffer, size_t buffer_size, size_t *len_needed) {
	const char *read = *source;
	char delimiter;
	size_t buffer_used = 0;
	bool escaped = false;
	bool write_disabled = false;
	
	if (len_needed != NULL) *len_needed = 0;
	
	if (buffer_size == 0)
		write_disabled = true;
	
	if (*read == EOS) {
		buffer[0] = EOS;
		return true;
	} else {
		delimiter = *read;
	}
	
	if (delimiter != '"' && delimiter != '\'') {
		delimiter = ' ';
	} else {
		read++;
	}
	
	for (;;read++) {
		if (!escaped && is_string_end(delimiter, *read)) {
			if (!write_disabled) buffer[buffer_used] = EOS;
			if (len_needed != NULL) (*len_needed)++;
			if (delimiter != ' ') {
				if (*read == delimiter) {
					read++;
				} else {
					return false;
				}
			}
			if (write_disabled)
				return false;
			*source = read;
			return true;
		} else if (!escaped && *read == ESCAPE) {
			escaped = true;
			continue;
		} else {
			if (!write_disabled) buffer[buffer_used] = *read;
			if (len_needed != NULL) (*len_needed)++;
		}
		escaped = false;
		buffer_used++;
		if (buffer_used >= buffer_size) {
			write_disabled = true;
		}
	}
}

bool read_string_to_buffer(const char **source, char *buffer, size_t buffer_size) {
	return read_string_to_buffer_ext(source, buffer, buffer_size, NULL);
}

const char* read_string_to_static_buffer(const char **source) {
	static char *buffer = NULL;
	static size_t buffer_size = 0;
	size_t len_needed = 0;
	
	if (!read_string_to_buffer_ext(source, buffer, buffer_size, &len_needed)) {
		if (len_needed <= buffer_size) return NULL;
		if (buffer_size == 0)
			buffer = malloc(len_needed);
		else
			buffer = realloc(buffer, len_needed);
		buffer_size = len_needed;
		if (!read_string_to_buffer_ext(source, buffer, buffer_size, &len_needed)) {
			return NULL;
		}
	}
	return buffer;
}
