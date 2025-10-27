#ifndef VECTOR_H
#define VECTOR_H

#define MAX(A, B) ((A) > (B) ? (A) : (B))

#include <stdlib.h>

typedef struct Vector {
	char **data;
	int size;
	int capacity;
} Vector;

Vector *create_vector();
void destroy_vector(Vector *v);

int vector_push_back(Vector *v, const char *item);
int vector_resize(Vector *v, size_t new_capacity);

#endif
