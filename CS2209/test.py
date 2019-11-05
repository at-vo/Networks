last(1,2).
last(2,3).
last(3,4).
last(4,5).

list(X,X).
list(X,Y) :- list(X,Z), last(Z,Y).
