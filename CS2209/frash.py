%Author Fraser Brown 250950435

nQueens(_,[]).
nQueens(N, Board):-
    %permutation([1,2,3,4,5,6,7,8], Board),
    numlist(1, N, All),
    permutation(All, Board),
    checkSafe(Board).

%Takes one board off the list of boards
checkSafe([]).
checkSafe([X|Board]):-
    checkSafe(X),
    checkSafe(Board).

%Takes one number of board
checkSafe([]).
checkSafe([X|Board]):-
    checkSafe(X, Board, 1),
    checkSafe(Board).


%Checks Board
checkSafe(_,[], _).
checkSafe(X, [Y|Board], I):-
   
    %Check Row
    X =\= Y,

    %Check Diagonal
    X + I =\= Y,
    X - I =\= Y,
    
    %Checks rest of the Board for diagonals.
    checkSafe(X, Board, I + 1).