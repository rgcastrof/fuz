#ifndef VECTOR_H
#define VECTOR_H

#define MAX(A, B) ((A) > (B) ? (A) : (B))
#define VECTOR_GET(v, index) ((v).items[(index)])

#include <stdlib.h>

typedef struct Vector {
	size_t *items;
	size_t size;
	size_t capacity;
} Vector;

void vector_init(Vector *v);
int vector_push_back(Vector *v, size_t value);

#endif
