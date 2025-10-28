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
void run(Term *t, Vector *entry);
void load_curses(Term *t, Vector *entry);
void cleanup(Term *t, Vector *entry);

#endif
