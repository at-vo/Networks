#include <iostream>
#include <string.h>
#include "uandf.h"


int main() {
    char prevLine[100] = {0};
    char nextLine[100] = {0};
    int line = 0;

    uandf * arr = new uandf(71*71);

    fgets(prevLine, 100, stdin);
    int len = (int) strlen(prevLine) - 1;

    for(int i = 0; i < len; i++) {
        if(prevLine[i] == '+') arr -> make(i + 1);
        if(i >= 1 && arr -> find_set(i) != -1) arr -> union_sets(i, i+1);
    }
    printf("%s", prevLine);

    while(fgets(nextLine, 100, stdin) != NULL) {
        line+=1;
        len = strlen(nextLine) - 1;
        printf("%s", nextLine);

        for(int k = 0; k < len; k++) {
            if(nextLine[k] == '+') {
                uandf -> make_set(k + 1 + line*71);

                if(k >= 1) {
                    if(nextLine[k - 1] == '+') 
                        uandf -> union_sets(k + line*71, k + 1 + line*71);
                }
                if(prevLine[k] == '+') uandf -> union_sets(k + 1 + (line - 1)*71, k + 1 + line*71);

            
            }

        }
        strcpy(prevLine, nextLine);

    }

    int reps = arr -> finalsets();

    printf("The total number of components is: %d\n", reps);
    node ** sets = arr->getSets();

    for(int j = 0; j < reps; j++) {
        printf("Component %c: \n\tIndex %d | Size %d | Rank %d\n", 65+j, sets[j] ->getMember(), sets[j] -> getSize(), sets[j] -> getRank());
    }

    return 0;
}