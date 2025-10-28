#include <ctype.h>
#include <string.h>

#include "tui.h"
#include "../core/matcher/matcher.h"

int
init_term(Term *t)
{
	t->tty_in = fopen("/dev/tty", "r");
	if (!t->tty_in) {
		perror("Error: failed to open /dev/tty as input.\n");
		return 0;
	}
	t->tty_out = fopen("/dev/tty", "w");
	if (!t->tty_out) {
		perror("Error: failed to open /dev/tty as output.\n");
		return 0;
	}

	t->term_type = getenv("TERM");
	if (t->term_type == NULL)
		t->term_type = "unknown";  /* fallback */
	t->main_scr = newterm(t->term_type, t->tty_out, t->tty_in);
	if (!t->main_scr) {
		perror("Error: failed to initialize newterm");
		fclose(t->tty_in);
		return 0;
	}
	return 1;
}

void
setup(Term *t)
{
	if (!init_term(t)) {
		perror("Error: failed to initialize ncurses");
		exit(EXIT_FAILURE);
	}
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
}

void
run(Term *t, Vector *entry)
{
	Vector *matches = NULL;
	char input[100] = "";
	size_t len;
	int ch;

	while (true) {
		getmaxyx(stdscr, t->rows, t->cols);
		clear();

		matches = get_matches(entry, input);
		if (matches != NULL) {
			for (int i = 0; i < matches->size; i++) {
				if (matches->data[i] != NULL)
					mvprintw(t->rows - i - 3, 0, "%s", matches->data[i]);
			}
		}
		mvprintw(t->rows - 1, 0, "> %s", input);
		move(t->rows - 1, 2 + strlen(input));
		refresh();

		ch = getch();
		if (ch == '\n')
			break;

		len = strlen(input);
		if (ch == KEY_BACKSPACE || ch == 127 || ch == 8) {
			if (len > 0) {
				input[len - 1] = '\0';
			}
		} else if (isprint(ch)) {
			input[len] = ch;
			input[len + 1] = '\0';
		}
	}
}

void
load_curses(Term *t, Vector *entry)
{
	setup(t);
	run(t, entry);
}

void
cleanup(Term *t, Vector *entry)
{
	endwin();
	delscreen(t->main_scr);
	fclose(t->tty_in);
	destroy_vector(entry);
}
