#include "uandf.h"


uandf(int n){
    arr = node[n+1];   // construct array of nodes
}                       // constructs an union-find data type with n elements, 1,2, . . . , n.


node makeset(int i){
    node set = new node;
    int rep = i;        // i
    set.head = set;       // head   points to itself
    set.parent = set;       // point tail to itself
    set.size++;    // size set to 1

    return set;
} // creates a new set whose only member (and thus representative) is i.


void unionsets(int i, int j){
    headI = findset(i);
    headJ = findset(j);
    if (headI.size > headJ.size){
        headJ.parent = headI.head;
        headI.size+=headJ.size;
    }else{
        headI.parent = headJ.head;
        headJ.size+=headI.size;
    }
} //unites the dynamic sets that contains i and j, respectively, into a newset that is the union of these two sets


int findset(i){
    node * temp = uandf[i].parent;
    if(temp.rep!=i){
        temp = find(temp.parent.rep);
    }
    return temp.rep;

} // returns the representative of the set containing i.


void finalsets(){
    
} //returns the total number of current sets and finalizes the current sets:
    // makeset() and unionsets() will have no effect after this operation
