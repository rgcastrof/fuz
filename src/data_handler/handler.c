#include <stdio.h>
#include <string.h>

#include "handler.h"

void
load_entry(Vector *entry, char *line, size_t buffer_size, char *entrybuf)
{
	size_t pos = 0;
	while (getline(&line, &buffer_size, stdin) != -1) {
		line[strcspn(line, "\n")] = 0;
		size_t l = strlen(line);

		memcpy(entrybuf + pos, line, l + 1);

		char *ptr = entrybuf + pos;
		vector_push_back(entry, &ptr);

		pos += l + 1;
	}

	if (line)
		free(line);
}
