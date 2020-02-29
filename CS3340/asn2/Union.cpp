#include "Union.h"

Union::Union(int n) {
    this -> total_sets = n;
    this -> sets = (Node **) malloc(n*sizeof(Node *));
    this -> finalized = false;

    for(int i = 1; i <= n; i++) {
        this -> sets[i - 1] = new Node(-1);
    }
}

void Union::make_set(int i) {
    if(finalized || this -> sets[i - 1] -> getMember() != -1) return;
    if(i > this -> total_sets) {
        this -> total_sets += 1;
        Node **tmpSets = (Node **) malloc(this -> total_sets*sizeof(Node *));
        memcpy(tmpSets, this -> sets, (this->total_sets - 1)*sizeof(Node *));
        this -> sets[this -> total_sets - 1] = new Node(i);
        return;
    }
    else {
        this -> sets[i - 1] = new Node(i);
    }
    
}

void Union::union_sets(int i, int j) {
    if(finalized) return;
    return Link(find_set(i), find_set(j));
}

int Union::find_set(int i) {
    if(this -> sets[i - 1] -> getMember() == -1) 
        return -1;
    if(this -> sets[i - 1] -> getParent() == i) 
        return i;
    else {
        int parent = find_set(this->sets[i-1] -> getParent());
        this -> sets[i - 1] -> setParent(parent);
        return parent;
    }

}

int Union::final_sets() {
    this -> finalized = true;
    int *final_sets = new int[this -> total_sets];

    int representatives = 0;

    for(int i = 0; i < this -> total_sets; i++) {
        if(this -> sets[i] -> getParent() == (i + 1)) {
            final_sets[representatives] = i+1;
            representatives += 1;
        }
    }
    Node ** newSet = (Node **) malloc(representatives*sizeof(Node *));

    for(int j = 0; j < representatives; j++) {
        newSet[j] = this -> sets[final_sets[j] - 1];
        newSet[j] -> setParent(j);
        // printf("REPRESENTATIVE: %d SET ID: %d\n", j + 1, final_sets[j]);
    }

    this -> total_sets = representatives;
    this -> sets = newSet;

    return representatives;
}


void Union::Link(int x, int y) {
    if(x < 0 ||y < 0 || x == y) return;
    printf("in Union::Link x: %d, y: %d\t", x, y);
    Node *xNode = this -> sets[x - 1];
    Node *yNode = this -> sets[y - 1];

    int newSize = yNode -> getSize() + xNode -> getSize();
    printf("\tX Size: %d Y Size: %d NEW SIZE: %d\n", xNode -> getSize(), yNode -> getSize(), newSize);

    if(xNode -> getRank() > yNode -> getRank()) {
        yNode -> setParent(x);
        xNode -> setSize(newSize);
    }
    else if(yNode -> getRank() > xNode -> getRank()) {  
        xNode -> setParent(y);
        yNode -> setSize(newSize);
    }
    else if(x != y) {
        yNode -> setParent(x);
        xNode -> setRank(xNode -> getRank() + 1);
        xNode -> setSize(newSize);
    }
}

Node **Union::getSet() {
    return this -> sets;
}

int Union::getSize() {
    return this -> total_sets;
}