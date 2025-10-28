#include <stdio.h>
#include <string.h>

#include "handler.h"

static int
buffer_realloc(size_t pos, size_t len, char **entry_buffer, size_t *buffer_cap)
{
	size_t new_cap = *buffer_cap ? (*buffer_cap) * 2 : INITIAL_ENTRYBUF_SIZE;

	while (new_cap < pos + len + 1)
		new_cap *= 2;

	char *tmp = realloc(*entry_buffer, new_cap);

	if (!tmp) {
		perror("Error: failed to realloc buffer");
		return 0;
	}

	*entry_buffer = tmp;
	*buffer_cap = new_cap;

	return 1;
}

void
load_entry(
		Vector *offsets,
		char **entry_buffer,
		size_t *buffer_cap
	)
{
	char *line = NULL;
	size_t getline_buffer_size = 0;
	size_t pos = 0;
	while (getline(&line, &getline_buffer_size, stdin) != -1) {
		line[strcspn(line, "\n")] = 0;
		size_t l = strlen(line);

		if (pos + l + 1 > *buffer_cap)
			buffer_realloc(pos, l, entry_buffer, buffer_cap);

		memcpy(*entry_buffer + pos, line, l + 1);
		vector_push_back(offsets, pos);

		pos += l + 1;
	}

	if (line)
		free(line);
}
