#ifndef TUI_H
#define TUI_H
#include <ncurses.h>

#include "../vector/vector.h"

typedef struct Term {
	SCREEN *main_scr;
	FILE *tty_in;
	FILE *tty_out;
	char *term_type;
	int rows;
	int cols;
} Term;

void setup(Term *t);
size_t run(Term *t, Vector *entry, char *entry_buffer);
void cleanup(Term *t, void *items);

#endif
