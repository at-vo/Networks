#ifndef UANDF_H
#define UANDF_H

typedef struct{
    int rep;
    node * head;    // point to head (itself)
    node * parent;
    int size = 0;   // init size of list to 0
} node;

class uandf{
    public:
        uandf(int n); // constructs an union-find data type with n elements, 1,2, . . . , n.
        void unionsets(int i, int j); //unites the dynamic sets that contains i and j, respectively, into a newset that is the union of these two sets
    private:
        node * arr;   // union find array
        int findset(int i); // returns the representative of the set containing i.
        node makeset(int i); // creates a new set whose only member (and thus representative) is i.
        void finalsets(); //returns the total number of current sets and finalizes the current sets:
                        // makeset() and unionsets() will have no effect after this operation
};

#endif