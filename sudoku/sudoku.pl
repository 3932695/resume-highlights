% Sudoku solver takes four lists. Each list represents a row. Each row has four numbers.
% Sample input: "solve(1, 2, 3, _], _, X, [2, 3, 4, Y])."

solution([A1, A2, A3, A4], [B1, B2, B3, B4], [C1, C2, C3, C4], [D1, D2, D3, D4]):-
    permutation([1, 2, 3, 4], [A1, A2, A3, A4]),
    permutation([1, 2, 3, 4], [B1, B2, B3, B4]),
    permutation([1, 2, 3, 4], [C1, C2, C3, C4]),
    permutation([1, 2, 3, 4], [D1, D2, D3, D4]),
    24 is A1*B1*A2*B2,
    24 is A3*A4*B3*B4,
    24 is C1*C2*D1*D2,
    24 is C3*C4*D3*D4,
    24 is A1*B1*C1*D1,
    24 is A2*B2*C2*D2,
    24 is A3*B3*C3*D3,
    24 is A4*B4*C4*D4.
solve(A, B, C, D):- solution(A, B, C, D), write(A), nl, write(B), nl, write(C), nl, write(D).
    
