#include <string.h>
#include "matcher.h"

void
get_matches(Vector *offsets, Vector *matches, char *entry_buffer, char *input)
{
	for (size_t i = 0; i < offsets->size; i++) {
		size_t offset = VECTOR_GET(*offsets, i);
		if (strstr(entry_buffer + offset, input)) {
			vector_push_back(matches, offset);
		}
	}
}
