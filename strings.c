#include <stdlib.h>

#undef EXTERN
#include "strings.h"

/**
 * \brief   Checks for string end
 *
 *          Checks sample to indicate a string end.
 *
 * \param   delimiter The used delimiter
 * \param	sample    The char to be checked
 * \return	          true, if sampele indicates a string end.
 *
 */
static bool is_string_end(char delimiter, char sample) {
	if (sample == EOS) return true;
	if (sample == delimiter) return true;
	if (sample == CR) return true;
	if (sample == LF) return true;
	return false;
}

/**
 * \brief   Reads a string to a outer buffer
 * 
 *          Reads a string in *source and outputs it to buffer.
 *          If *source starts with ' or " the function will read to the
 *          corresponding quote. A backslash can be used as an escape
 *          sequence for quotes and backslashes. Backslashes in front
 *          of other caracters are ignored and not copied into the result.
 * 
 * \param   source      Source string, on success the pointer is set to the
 *                      string-following char.
 * \param   buffer      The destination buffer.
 * \param   buffer_size The size of the destination buffer.
 * \param   len_needed  Returns the buffer size needed to hold the complete
 *                      string. May be NULL if value is not needed.
 * \return  true in success, false on failure (buffer too small, no closing quote)
 */
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

/**
 * \brief   Reads a string to a outer buffer
 * 
 *          Reads a string in *source and outputs it to buffer.
 *          If *source starts with ' or " the function will read to the
 *          corresponding quote. A backslash can be used as an escape
 *          sequence for quotes and backslashes. Backslashes in front
 *          of other caracters are ignored and not copied into the result.
 * 
 * \param   source      Source string, on success the pointer is set to the
 *                      string-following char.
 * \param   buffer      The destination buffer.
 * \param   buffer_size The size of the destination buffer.
 * \return  true in success, false on failure (buffer too small, no closing quote)
 */
bool read_string_to_buffer(const char **source, char *buffer, size_t buffer_size) {
	return read_string_to_buffer_ext(source, buffer, buffer_size, NULL);
}

/**
 * \brief   Reads a string to a inner buffer
 * 
 *          Reads a string in *source and outputs it to a internal buffer.
 *          If *source starts with ' or " the function will read to the
 *          corresponding quote. A backslash can be used as an escape
 *          sequence for quotes and backslashes. Backslashes in front
 *          of other caracters are ignored and not copied into the result.
 * 
 * \param   source      Source string, on success the pointer is set to the
 *                      string-following char.
 * \return  pointer to result string (static memory) on success,
 *          NULL on failure (buffer too small, no closing quote)
 */
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
