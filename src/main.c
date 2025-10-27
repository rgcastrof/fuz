#include "tui/tui.h"
#include "vector/vector.h"

void
load_entry(Vector *entry, char *line, size_t buffer_size, ssize_t readed_chars)
{
	while ((readed_chars = getline(&line, &buffer_size, stdin)) != -1) {
		vector_push_back(entry, line);
	}

	if (line)
		free(line);
}

int
main(int argc, char *argv[])
{
	Term term;
	Vector *entry = create_vector();
	char *line = NULL;
	size_t buffer_size = 0;
	ssize_t readed_chars;

	load_entry(entry, line, buffer_size, readed_chars);
	load_curses(&term, entry);
	cleanup(&term, entry);

	return 0;
}
