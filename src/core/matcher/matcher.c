#include <string.h>
#include "matcher.h"

Vector *
get_matches(Vector *entry, char *input)
{
	Vector *matches = create_vector();
	for (int i = 0; i < entry->size; i++) {
		if (strstr(entry->data[i], input)) {
			vector_push_back(matches, entry->data[i]);
		}
	}
	return matches;
}
