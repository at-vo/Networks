% Dat Vo 250983323
last([X],X). % grounding case for last element
last([_|Tail],X):-last(Tail,X). % recursive call for rest of list