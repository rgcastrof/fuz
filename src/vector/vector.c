#include <stdlib.h>
#include <string.h>

#include "vector.h"

Vector
*create_vector()
{
	Vector *v = malloc(sizeof(Vector));
	v->size = 0;
	v->capacity = 1;
	v->data = malloc(sizeof(char*) * v->capacity);
	return v;
}

void
destroy_vector(Vector *v)
{
	for (int i = 0; i < v->size; i++) {
		free(v->data[i]);
	}
	free(v->data);
	free(v);
}

int
vector_resize(Vector *v, size_t new_capacity)
{
	char **new_data = realloc(v->data, new_capacity * sizeof(char*));
	if (!new_data)
		return 0;

	v->data = new_data;
	v->capacity = new_capacity;
	return 1;
}

int
vector_push_back(Vector *v, const char *item)
{
	if (v->size == v->capacity) {
		if (!vector_resize(v, MAX(1, 2*v->capacity)))
			return 0;
	}

	v->data[v->size] = strdup(item);
	v->size++;
	return 1;
}
