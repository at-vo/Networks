#ifndef UANDF_H
#define UANDF_H

#include <stdlib.h>
#include <cstring>

typedef struct{
    int rep;
    node * parent;
    int size;   // init size of list to 0
    int rank;
} node;

class uandf{
    public:
        uandf(int n); // constructs an union-find data type with n elements, 1,2, . . . , n.
        void unionsets(int i, int j); //unites the dynamic sets that contains i and j, respectively, into a newset that is the union of these two sets
        node ** getSets();
        int finalsets(); //returns the total number of current sets and finalizes the current sets:
                        // makeset() and unionsets() will have no effect after this operation
        void makeset(int i); // creates a new set whose only member (and thus representative) is i.
        node * findset(int i); // returns the representative of the set containing i.
    private:
        node ** UFind;   // union find array
        bool finalCheck;
        int numSets;

};

#endif