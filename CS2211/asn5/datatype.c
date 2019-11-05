#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"

//Duplicate string pointed to by str with dynamic memory allocation.
char *string_dup(char *str)
{
    char *toReturn;
    toReturn = (char *)malloc(sizeof(*str));
    strcpy(toReturn, str);
    return toReturn;
}

//Generate a key with dynamic memory allocation.
Key key_gen(char *skey1, char *skey2)
{
    Key toReturn;
    char * k1 = string_dup(skey1);
    char * k2 = string_dup(skey2);
    toReturn = (Key) malloc(sizeof(Key_struct));
    toReturn->skey1 = k1;
    toReturn->skey2 = k2;

    return toReturn;
}

//Use strcmp( ) to do comparison. If key1->skey1 and key2->skey1 are different, then
//they determine the comparison result. If key1->skey1 and key2->skey1 are the same,
//then key1->skey2 and key2->skey2 determine the comparison result.
int key_comp(Key key1, Key key2)
{
    int comp1 = strcmp(key1->skey1, key2->skey1); // compare skey1
	if (comp1 < 0){return -1;}  //if return value < 0, then key1 < key2
	else if (comp1 == 0) { // if key1.name = key2.name, then compare key1.id with key2.id
        int comp2 = strcmp(key1->skey2, key2->skey2); // compare skey2
		if (comp2 < 0){return -1;} 
		else if (comp2 == 0){return 0;} // if return value = 0, then key1 = key2,
        else {return 1;}
	}
	else {return 1;} // if return value > 0, then key1 > key2,
}

// Print a key.
void key_print(Key key)
{
    printf("key1: %s key2: %s \n", key->skey1, key->skey2);
}

// Free memory allocated for key.
void key_free(Key key)
{
    free(key->skey1);
    free(key->skey2);
    free(key);
}

// Generate a data with dynamic memory allocation.
Data data_gen(int idata)
{
    Data toReturn;
    toReturn = (int *) malloc(sizeof(int));
    *toReturn = idata;
    return toReturn;
}

// Assign data with idata.
void data_set(Data data, int idata)
{
    *data = idata;
}

// Print a data.
void data_print(Data data)
{
    printf("data: %d \n", *data);
}

// Free memory allocated for data.
void data_free(Data data)
{
    free(data);
}
