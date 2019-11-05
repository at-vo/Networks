eightQueens(Board) :- 
permutation([1,2,3,4],Board), 
checkDiagonals(Board).

getHead([H|_],H).

removeHead([]).
removeHead([_|T],T).

checkDiagonals([Last],Last).
checkDiagonals(Board,Last) :- getHead(Board,X), removeHead(Board,Y), compareDn(X,Y), compareUp(X,Y), checkDiagonals(Y).

%Down Diag
compareDn(Head,[]).
compareDn(Head,List):- numCompDn(Head, List, A), removeHead(List,Y), compare(Head,Y).

numCompDn(N1,[_],_).
numCompDn(N1,List,Unify):- inc(H1,I), getHead(List,B), check(I,Bigger,Check), removeHead(List,Next), numCompDn(I,Next,Unify).


%Up Diag
compareUp(Head,[]).
compareUp(Head,List,N):- numCompUp(Head, List,N, A), removeHead(List,Y), compare(Head,Y).

numCompUp(N1,[X],X).
numCompUp(N1,List,Unify):- inc(H1,I), getHead(List,B), check(I,Bigger,Check), removeHead(List,Next), numCompUp(I,Next,Unify).


Check(N1,N2,Return):- Return is N1=/=N2.


inc(Num,Return) :- Return is Num+1.
dec(Num,Return) :- Return is Num-1.