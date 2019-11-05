#include <stdio.h>
#include <stdlib.h>

void *Vector(int num_elements, int type_size);

int main()
{
	void *p;
	int n = 3;
	p = (void *) Vector (n, sizeof(void));
	return 0;
}

void *Vector(int num_elements, int type_size)
{
	void *p;
	p = (unsigned *) calloc(num_elements + 1, sizeof(type_size));
	return p;
} 

