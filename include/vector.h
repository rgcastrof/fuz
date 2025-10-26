#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector {
	char **data;
	int size;
	int capacity;
} Vector;

Vector *create_vector();
void destroy_vector(Vector *v);

#endif
