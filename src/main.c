#include "data_handler/handler.h"
#include "tui/tui.h"
#include "vector/vector.h"

int
main(int argc, char *argv[])
{
	Term term;
	size_t buffer_cap = INITIAL_ENTRYBUF_SIZE;
	char *entry_buffer = malloc(buffer_cap);
	Vector offsets;
	vector_init(&offsets);

	load_entry(&offsets, &entry_buffer, &buffer_cap);
	setup(&term);
	size_t selected_offset = run(&term, &offsets, entry_buffer);
	printf("%s\n", entry_buffer + selected_offset);
	free(entry_buffer);
	free(offsets.items);

	return 0;
}
