#include "uandf.h"


uandf::uandf(int n){
    UFind = (node **) malloc(n*sizeof(node *));   // construct array of nodes
    finalCheck = false;
    numSets = n;
    for(int i = 0; i <= n; i++) {
        this -> UFind[i] = new node;
        UFind[i]->parent = UFind[i];
        UFind[i]->rep = i;
        UFind[i]->rank = 0;
        UFind[i]->size = 1;
    }
}                       // constructs an union-find data type with n elements, 1,2, . . . , n.


void uandf::makeset(int i){ 
    if(finalCheck){
        return;
    }
    if(i>numSets){
        numSets+= 1;
        node **tmpSets = (node **) malloc(this -> numSets*sizeof(node *));
        memcpy(tmpSets, UFind, (numSets-1)*sizeof(node *));
        node * temp = new node;
        temp->parent = temp;
        temp->rank=0;
        temp->size=1;
        temp->rep=i;
        UFind[numSets] = temp;
        return;
    }else{
        node * set = new node;
        int rep = i;        // i
        set->parent = set;       // point tail to itself
        set->size= 1;    // size set to 1
        UFind[i] = set;
    }
} // creates a new set whose only member (and thus representative) is i.


void uandf::unionsets(int i, int j){
    if(finalCheck){
        return;
    }
    node * headI = findset(i);
    node * headJ = findset(j);
    if (headI->size > headJ->size){
        headJ->parent = headI;
        headI->size+=headJ->size;
    }else if (headJ->size > headI->size){
        headI->parent = headJ;
        headJ->size+=headI->size;
    }
} //unites the dynamic sets that contains i and j, respectively, into a newset that is the union of these two sets


node * uandf::findset(int i){
    node * temp = UFind[i]->parent;
    if(temp->rep!=i){
        temp = findset(temp->parent->rep);
    }
    return temp;

} // returns the representative of the set containing i.


int uandf::finalsets(){
    finalCheck = true;
    int * finalsets = new int[numSets];
    int reps = 0;
    for (int i = 0; i < numSets; i++)
    {
        /* code */
    }
    
} //returns the total number of current sets and finalizes the current sets:
    // makeset() and unionsets() will have no effect after this operation
