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
	start_color();
	init_pair(2, COLOR_BLACK, COLOR_YELLOW);
}

size_t
run(Term *t, Vector *entry, char *entry_buffer)
{
	char input[100] = "";
	size_t len;
	int ch, selected = 0;
	Vector matches;
	vector_init(&matches);
	size_t chosen_offset = 0;

	while (true) {
		getmaxyx(stdscr, t->rows, t->cols);
		clear();

		matches.size = 0;
		get_matches(entry, &matches, entry_buffer, input);

		if (selected >= t->rows - 3) selected = 0;
		if (selected < 0) selected = t->rows - 4;

		for (int i = 0; i < matches.size; i++) {
			size_t offset = VECTOR_GET(matches, i);
			if (i == selected) {
				attron(COLOR_PAIR(2));
				mvprintw(t->rows - i - 4, 0, "%s", entry_buffer + offset);
				attroff(COLOR_PAIR(2));
			} else {
				mvprintw(t->rows - i - 4, 0, "%s", entry_buffer + offset);
			}
		}
		mvprintw(t->rows - 2, 0, "%zu", matches.size);
		mvprintw(t->rows - 1, 0, "> %s", input);
		move(t->rows - 1, 2 + strlen(input));
		refresh();

		ch = getch();
		if (ch == '\n') {
			chosen_offset = VECTOR_GET(matches, selected);
			break;
		}

		if (ch == KEY_UP) selected++;
		if (ch == KEY_DOWN) selected--;
		refresh();

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
	cleanup(t, matches.items);
	return chosen_offset;
}

void
cleanup(Term *t, void *items)
{
	free(items);
	endwin();
	delscreen(t->main_scr);
	fclose(t->tty_in);
	fclose(t->tty_out);
}
