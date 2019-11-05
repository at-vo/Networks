%Dat Vo 250983323
%ground case for empty Board
nQueens([],_).

%nQueens function call
nQueens(Board,N):-
    numlist(1, N, List),
    permutation(List, Board),
    checkDiagonals(Board).

%getHead function
getHead([H|_],H).

%removeHead function
removeHead([]).
removeHead([_|T],T).


%ground case for empty Board
checkDiagonals([]).

%checkDiagonals function call
checkDiagonals(Board):-
    getHead(Board,Head), %get Head of Board
    removeHead(Board,Rest), %remove Head of Board and return Rest of Board
    checkDiagonals(Rest),%recursive call for next Board element
    checkBoard(Head,Rest,1). %begin with Index = 1

%ground case for empty checkBoard, disregard Head and Index
checkBoard(_,[], _).

%checkBoard looks at current head then 
%compares it to the head of the rest of the Board then 
%removes head and checks next element in board list
checkBoard(Head, [Check|Board], Index):-
Head + Index =\= Check, %check down diagonal
Head - Index =\= Check, %check up diagonal

%recursive call for next board element and increment index
checkBoard(Head, Board, Index + 1). 