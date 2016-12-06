insert_sort([], []).
insert_sort([H | T], R) :- insert_sort(T, Rs), insert(H, Rs, R).

insert(H, [Rh | Rt], [H, Rh | Rt]) :- H =< Rh.
insert(H, [Rh | Rt], [Rh | R]) :- H > Rh, insert(H, Rt, R). 
insert(I, [], [I]).
