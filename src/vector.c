#include "vector.h"
#include <stdlib.h>

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
