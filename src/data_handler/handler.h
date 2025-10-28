#ifndef HANDLER_H
#define HANDLER_H

#define INITIAL_ENTRYBUF_SIZE (1024 * 1024)

#include "../vector/vector.h"

void load_entry(Vector *entry, char **entry_buffer, size_t *buffer_cap);

#endif
