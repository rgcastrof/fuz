#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

void
vector_init(Vector *v)
{
	v->size = 0;
	v->capacity = 128;
	v->items = malloc(v->capacity * sizeof(size_t));
	if (!v->items) {
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
}

static int
vector_resize(Vector *v, size_t newcap)
{
	size_t *tmp = realloc(v->items, newcap * sizeof(size_t));
	if (!tmp)
		return 0;
	v->items = tmp;
	v->capacity = newcap;
	return 1;
}

int
vector_push_back(Vector *v, size_t value)
{
	if (v->size == v->capacity) {
		if (!vector_resize(v, v->capacity * 2)) {
			perror("Error: falied to realloc vector");
			return 0;
		}
	}
	v->items[v->size++] = value;
	return 1;
}
